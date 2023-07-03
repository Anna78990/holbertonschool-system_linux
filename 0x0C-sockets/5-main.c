#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

/**
 * print_queries - print queries
 * @queries: double pointer to query array
 */
void print_queries(char **queries)
{
	int i = 0;
	char *tok, *tok2;

	while (queries[i])
	{
		tok = strtok(queries[i], "=");
		tok2 = strtok(NULL, "\0");
		printf("Query: \"%s\" -> \"%s\"\n", tok, tok2);
		i++;
	}
}

/**
 * get_query - create array of query
 * @path: path to refer
 * Return: array of query
 */
char **get_query(char *path)
{
	char **query = NULL;
	char *path_dup, *token;
	int count = 0;

	if (path == NULL)
		return (NULL);
	path_dup = strdup(path);
	token = strtok(path_dup, "&");
	while (token)
	{
		query = realloc(query, sizeof(char *) * (count + 1));
		query[count] = strdup(token);
		count++;
		token = strtok(NULL, "&");
	}

	query = realloc(query, sizeof(char *) * (count + 1));
	query[count] = NULL;

	free(path_dup);
	return (query);
}

/**
 * get_path - find path
 * @path: chain of character to refer
 * Return: path
 */
char *get_path(const char *path)
{
	char *found, *dom = NULL;
	int i, diff;

	if (path[0] == '/')
	{
		found = strchr(path, '?');
		diff = found - path;
		dom = (char *)malloc(sizeof(char) * diff + 1);
		for (i = 0; i < diff; i++)
			dom[i] = path[i];
		dom[i] = '\0';
	}
	return (dom);
}

/**
 * handle_client - print the information of client socket
 * @client_socket: socket number to refer
 */
void handle_client(int client_socket)
{
	char buffer[BUFFER_SIZE], buf[BUFFER_SIZE];
	ssize_t bytes_received;
	char *path, *q_start, *q_end;
	char **queries;
	int i;
	const char *response;

	bytes_received = read(client_socket, buffer, BUFFER_SIZE - 1);
	if (bytes_received < 0)
	{
		perror("Error reading from socket");
		close(client_socket);
		return;
	}
	buffer[bytes_received] = '\0';
	printf("Raw request: \"%s\"\n", buffer);
	path = get_path(buffer + 4);
	q_start = strchr(buffer, '?');
	q_end = strstr(q_start, " HTTP");
	for (i = 0; i < q_end - q_start; i++)
	{
		if (i == 0 && q_start[i] != '?')
			break;
		else if (i > 0)
			buf[i - 1] = q_start[i];
	}
	buf[i] = '\0';
	queries = get_query(buf);
	if (path)
		printf("Path: %s\n", path);
	if (queries)
		print_queries(queries);
	free(path);
	free(queries);
	response = "HTTP/1.1 200 OK\r\n"
		"Content-Length: 0\r\n"
		"Connection: close\r\n\r\n";
	write(client_socket, response, strlen(response));
	close(client_socket);
}

/**
 * main - opens an IPv4/TCP socket, and listens to traffic on port 8080
 *
 * Return: exit status
 */
int main(void)
{
	int server_socket, client_socket;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len;
	char *client_ip;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0)
	{
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(8080);
	if (bind(server_socket, (struct sockaddr *)&server_addr,
				sizeof(server_addr)) < 0)
	{
		perror("Error binding");
		exit(EXIT_FAILURE);
	}
	if (listen(server_socket, 5) < 0)
		perror("Error listening"), exit(EXIT_FAILURE);
	printf("Server listening on port 8080\n");
	while (1)
	{
		client_len = sizeof(client_addr);
		client_socket = accept(server_socket,
				(struct sockaddr *)&client_addr, &client_len);
		if (client_socket < 0)
			perror("Error accepting connection"), exit(EXIT_FAILURE);
		client_ip = (char *)malloc(sizeof(char) * INET_ADDRSTRLEN);
		inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
		printf("Client connected: %s\n", client_ip);
		free(client_ip);
		handle_client(client_socket);
	}
	close(server_socket);
	return (0);
}
