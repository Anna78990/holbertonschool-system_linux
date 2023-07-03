#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>


/**
 * main - opens an IPv4/TCP socket, and listens to traffic on port 12345
 *
 * Return: always 0.
 */
int main(void)
{
	int sockfd, clientfd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len;
	char ip_address[INET_ADDRSTRLEN];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(12345);
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (listen(sockfd, 1) == -1)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port 12345\n");
	client_len = sizeof(client_addr);
	clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
	if (clientfd == -1)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	inet_ntop(AF_INET, &(client_addr.sin_addr), ip_address, INET_ADDRSTRLEN);
	printf("Client connected: %s\n", ip_address);
	close(clientfd);
	close(sockfd);
	return (0);
}
