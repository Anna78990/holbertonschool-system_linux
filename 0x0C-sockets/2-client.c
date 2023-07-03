#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

/**
 * main - opens an IPv4/TCP socket, and listens to traffic on port 12345
 * @argv: ip adress and port
 * Return: exit status
 */
int main(int argc, char *argv[])
{
	const char *host, *lh;
	unsigned short port;
	int sockfd;
	struct sockaddr_in server_addr;

	if (argc < 3)
	{
		printf("Usage: %s <host> <port>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	host = argv[1];
	port = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (strcmp(host, "localhost") == 0)
		lh = "127.0.0.1";
	else
		lh = host;
	if (sockfd < 0)
	{
		perror("Socket creation failed");
		return (EXIT_FAILURE);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, lh, &(server_addr.sin_addr)) <= 0)
	{
		perror("Invalid address or address not supported");
		close(sockfd);
		return (EXIT_FAILURE);
	}
	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Connection failed");
		close(sockfd);
		return (EXIT_FAILURE);
	}
	printf("Connected to %s:%d\n", host, port);
	close(sockfd);
	return (EXIT_SUCCESS);
}
