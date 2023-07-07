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
		tok = strtok(queries[i], ":");
		tok2 = strtok(NULL, "\r\n");
		printf("Header: \"%s\" -> \"%s\"\n", tok, tok2 + 1);
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
	token = strtok(path_dup, "\r\n");
	while (token)
	{
		query = realloc(query, sizeof(char *) * (count + 1));
		query[count] = strdup(token);
		count++;
		token = strtok(NULL, "\r\n");
	}

	query = realloc(query, sizeof(char *) * (count + 1));
	query[count] = NULL;

	free(path_dup);
	return (query);
}

/**
 * process_request - print request infos
 * @client_socket: socket to refer
 */
void process_request(int client_socket)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_received, bytes_sent;
	char **headers;
	char *h_start;
	const char *response;

	memset(buffer, 0, sizeof(buffer));
	bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
	if (bytes_received == -1)
	{
		perror("recv");
		exit(EXIT_FAILURE);
	}

	printf("Raw request: \"%s\"\n", buffer);
	h_start = strstr(buffer, "Host: ");
	headers = get_query(h_start);
	print_queries(headers);
	free(headers);
	response = "HTTP/1.1 200 OK\r\n\r\n";
	bytes_sent = send(client_socket, response, strlen(response), 0);
	if (bytes_sent == -1)
	{
		perror("send");
		exit(EXIT_FAILURE);
	}

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

	setbuf(stdout, NULL);
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
		perror("Error binding"), exit(EXIT_FAILURE);
	if (listen(server_socket, 5) < 0)
	{
		perror("Error listening");
		exit(EXIT_FAILURE);
	}
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
		process_request(client_socket);
	}
	close(server_socket);
	return (0);
}
