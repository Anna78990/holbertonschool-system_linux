#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 12345
#define BUFFER_SIZE 1024
/**
 * main - opens an IPv4/TCP socket, and listens to traffic on port 12345
 *
 * Return: Exit status
 */
int main(void)
{
	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len = sizeof(client_addr);
	char buffer[BUFFER_SIZE], *client_ip;
	ssize_t num_bytes;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
		perror("bind failed"), exit(EXIT_FAILURE);
	if (listen(server_fd, 1) < 0)
		perror("listen failed"), exit(EXIT_FAILURE);
	printf("Server listening on port %d\n", PORT);
	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
	if (client_fd < 0)
	{
		perror("accept failed");
		exit(EXIT_FAILURE);
	}
	client_ip = (char *)malloc(sizeof(char) * INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
	printf("Client connected: %s\n", client_ip);
	free(client_ip);
	num_bytes = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
	if (num_bytes < 0)
	{
		perror("receive failed");
		exit(EXIT_FAILURE);
	}
	buffer[num_bytes] = '\0';
	printf("Message received: \"%s\"\n", buffer);
	close(client_fd), close(server_fd);
	return (EXIT_SUCCESS);
}
