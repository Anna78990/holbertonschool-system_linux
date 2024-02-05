#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

/**
 * handle_client - print the information of client socket
 * @client_socket: socket number to refer
 */
void handle_client(int client_socket)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_received;
	char *path, *query, *key, *value, *next, *rest;
	const char *response;

	bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
	if (bytes_received < 0)
	{
		perror("Error reading from socket");
		close(client_socket);
		return;
	}
	buffer[bytes_received] = '\0';
	printf("Raw request: \"%s\"\n", buffer);
	strtok(buffer, " ");
	path = strtok(NULL, " ");
	path = strtok_r(path, "?", &next);
	printf("Path: %s\n", path);
	query = strtok_r(NULL, "&", &next);
	while (query)
	{
		key = strtok_r(query, "=", &rest);
		value = strtok_r(NULL, "=", &rest);
		printf("Query: \"%s\" -> \"%s\"\n", key, value);
		query = strtok_r(NULL, "&", &next);
	}
	response = "HTTP/1.1 200 OK\r\n\r\n";
	send(client_socket, response, strlen(response), 0);
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
	{
		perror("Error binding");
		exit(EXIT_FAILURE);
	}
	if (listen(server_socket, 10) < 0)
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
