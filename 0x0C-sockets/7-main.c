#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

/**
 * trim - trimming given string
 * @str: string to trim
 * Return: trimed string
 */
char *trim(char *str)
{
	size_t len = strlen(str);
	char *end;

	if (len == 0)
		return (str);

	end = str + len - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';

	while (*str && isspace((unsigned char)*str))
		str++;

	return (str);
}

/**
 * process_request - print request infos
 * @client_socket: socket to refer
 */
void process_request(int client_socket)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_received, bytes_sent, encode;
	char *path, *header, *response, *start, *ptr, *key, *value, *query, *body;
	char *start_lines;

	memset(buffer, 0, sizeof(buffer));
	bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
	if (bytes_received == -1)
		perror("recv"), exit(EXIT_FAILURE);
	printf("Raw request: \"%s\"\n", buffer), body = strstr(buffer, "\r\n\r\n");
	if (strlen(body) > 0)
		*body = 0, body += strlen("\r\n\r\n");
	start_lines = strtok_r(buffer, "\r\n", &start), strtok(start_lines, " ");
	path = strtok(NULL, " "), printf("Path: %s\n", path);
	header = strtok_r(NULL, "\r\n\r\n", &start);
	while (header)
	{
		key = trim(strtok_r(header, ":", &ptr));
		value = trim(strtok_r(NULL, "\r\n", &ptr));
		if (!strcasecmp(key, "Content-Type"))
			if (!strcasecmp(value, "application/x-www-form-urlencoded"))
				encode = 1;
		header = strtok_r(NULL, "\r\n", &start);
	}
	if (encode)
	{
		query = strtok_r(body, "&", &start);
		while (query)
		{
			key = strtok_r(query, "=", &ptr);
			value = strtok_r(NULL, "=", &ptr);
			printf("Body param: \"%s\" -> \"%s\"\n", key, value);
			query = strtok_r(NULL, "&", &start);
		}
	}
	response = "HTTP/1.1 200 OK\r\n\r\n";
	bytes_sent = send(client_socket, response, strlen(response), 0);
	if (bytes_sent == -1)
		perror("send"), exit(EXIT_FAILURE);
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
		process_request(client_socket);
		free(client_ip);
	}
	close(server_socket);
	return (0);
}
