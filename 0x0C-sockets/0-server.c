#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


/**
 * main - opens an IPv4/TCP socket, and listens to traffic on port 12345
 *
 * Return: always 0.
 */
int main(void)
{
	int sockfd;
	struct sockaddr_in server_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("Socket creation error");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(12345);

	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Socket binding error");
		exit(EXIT_FAILURE);
	}

	if (listen(sockfd, 0) < 0)
	{
		perror("Socket listening error");
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port 12345\n");

	while (1)
	{
		sleep(1);
	}
	close(sockfd);

	return (0);
}
