#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

/**
 * handle_rawrequest - return rawrequest in correct order
 * @buffer: buffer to convert
 * Return: array of string
 */
char **handle_rawrequest(char *buffer)
{
	char **rr = malloc(sizeof(char *) * 6);
	char *m, *p, *v, *h, *ua, *a, *needle;

	m = strtok(buffer, " ");
	rr[0] = strdup(m);
	p = strtok(NULL, " ");
	rr[1] = strdup(p);
	v = strtok(NULL, "\r\n");
	rr[2] = strdup(v);
	h = strtok(NULL, "\r\n");
	needle = strstr(h, "Host: ");
	if (needle)
		rr[3] = strdup(h + 6);
	needle = NULL;
	ua = strtok(NULL, "\r\n");
	needle = strstr(ua, "User-Agent: ");
	if (needle)
		rr[4] = strdup(ua + 12);
	needle = NULL;
	a = strtok(NULL, "\r\n");
	needle = strstr(a, "Accept: ");
	if (needle)
		rr[5] = strdup(a + 8);
	printf("Raw-request: \"%s %s %s\n", rr[0], rr[1], rr[2]);
	printf("User-Agent: %s\nHost: %s\nAccept: %s\n\n\"\n", rr[4], rr[3],
			rr[5]);
	return (rr);
}

/**
 * handle_request - handle request
 * @client_fd: socket that has been created with socket
 *
 */
void handle_request(int client_fd)
{
	char buffer[BUFFER_SIZE];
	ssize_t num_bytes;
	const char *response;
	char **rr;
	int i;

	num_bytes = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
	if (num_bytes > 0)
	{
		buffer[num_bytes] = '\0';
		rr = handle_rawrequest(buffer);
		printf("Method: %s\n", rr[0]);
		printf("Path: %s\n", rr[1]);
		printf("Version: %s\n", rr[2]);
		for (i = 5; i <= 0; i--)
			free(rr[i]);
		response = "HTTP/1.1 200 OK\r\n\r\n";
		write(client_fd, response, strlen(response));
	}
	else
	{
		perror("receive failed");
		exit(EXIT_FAILURE);
	}
	close(client_fd);
}

/**
 * main - opens an IPv4/TCP socket, and listens to traffic on port 8080
 *
 * Return: exit status
 */
int main(void)
{
	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len = sizeof(client_addr);
	char *client_ip;

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
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 1) < 0)
	{
		perror("listen failed");
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port %d\n", PORT);
	while (1)
	{
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
		if (client_fd < 0)
			perror("accept failed"), exit(EXIT_FAILURE);
		client_ip = (char *)malloc(sizeof(char) * INET_ADDRSTRLEN);
		inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
		printf("Client connected: %s\n", client_ip);
		free(client_ip);
		handle_request(client_fd);
	}
	close(server_fd);
	return (EXIT_SUCCESS);
}
