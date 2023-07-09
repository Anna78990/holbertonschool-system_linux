#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include "socket.h"

static int id;
static struct todo_t *root;

#define BUFFER_SIZE 1024

/**
 * root_check - check if root is NULL
 * @todo: todo to insert
 */
void root_check(struct todo_t *todo)
{
	struct todo_t *node;

	if (!root)
		root = todo;
	else
	{
		node = root;
		while (node->next)
			node = node->next;
		node->next = todo;
	}
}

char *handle_get(void)
{
	char buffer[BUFFER_SIZE], header[BUFFER_SIZE], *res;
	char *ok = "HTTP/1.1 200 OK\r\n", *length = "Content-Length: ";
	char *json = "Content-Type: application/json\r\n\r\n";
	char *id = "\"id\"", *t = "\"title\"", *desc = "\"description\"";
	size_t i;
	struct todo_t *todo = root;

	memset(buffer, 0, BUFFER_SIZE), memset(header, 0, BUFFER_SIZE);
	buffer[0] = '[';
	while (todo)
	{
		sprintf(buffer + strlen(buffer),
			"{%s:%d, %s:\"%s\",%s:\"%s\"}", id, todo->id, t,
			todo->title, desc, todo->description);
		if (todo->next)
			buffer[strlen(buffer)] = ',';
		todo = todo->next;
	}
	buffer[strlen(buffer)] = ']';
	sprintf(header, "%s%s%lu\r\n%s", ok, length, strlen(buffer), json);
	res = (char *)malloc(sizeof(char) * (strlen(header) + strlen(buffer)));
	for (i = 0; i < strlen(res) + strlen(buffer); i++)
	{
		if (i >= strlen(header))
			res[i] = buffer[i - strlen(header)];
		else
			res[i] = header[i];
	}
	res[i] = 0;
	return (res);
}

/**
 * handle_post - parses post request
 * @body: the body string
 * @content_length: length of body string
 * Return: 0 on success else 1
 */
char *handle_post(char *body, short content_length)
{
	char *query, *k, *v, *ptr, *kv, *title = NULL;
	char buffer[BUFFER_SIZE], res[BUFFER_SIZE];
	char *created = "HTTP/1.1 201 Created\r\n", *length = "Content-Length: ";
	char *json = "Content-Type: application/json\r\n\r\n";
	char *desc = NULL, *request;
	struct todo_t *todo;
	size_t i;

	memset(buffer, 0, BUFFER_SIZE), memset(res, 0, BUFFER_SIZE);
	body[content_length] = 0, query = strtok_r(body, "&", &ptr);
	while (query)
	{
		k = strtok_r(query, "=", &kv), v = strtok_r(NULL, "=", &kv);
		if (strcasecmp(k, "title") == 0)
			title = v;
		else if (strcasecmp(k, "description") == 0)
			desc = v;
		query = strtok_r(NULL, "&", &ptr);
	}
	if (!title || !desc)
		return ("HTTP/1.1 422 Unprocessable Entity\r\n\r\n");
	todo = calloc(1, sizeof(*todo)), todo->id = id;
	if (!todo)
		return ("HTTP/1.1 422 Unprocessable Entity\r\n\r\n");
	id++, todo->title = strdup(title);
	todo->description = strdup(desc), todo->next = NULL, root_check(todo);
	sprintf(res, "{\"id\":%d,\"title\":\"%s\",\"description\":\"%s\"}",
			todo->id, todo->title, todo->description);
	sprintf(buffer, "%s%s%lu\r\n%s", created, length, strlen(res), json);
	request = (char *)malloc(sizeof(char) * (strlen(res) + strlen(buffer)));
	for (i = 0; i < strlen(res) + strlen(buffer); i++)
	{
		if (i >= strlen(buffer))
			request[i] = res[i - strlen(buffer)];
		else
			request[i] = buffer[i];
	}
	request[i] = 0;
	return (request);
}

/**
 * process_request - print request infos
 * @client_socket: socket to refer
 */
void process_request(int client_socket)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_received, content_length = 0;
	char *path, *header, *response, *start, *ptr, *key, *value, *body;
	char *s, *method;

	memset(buffer, 0, sizeof(buffer));
	bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
	if (bytes_received == -1)
		perror("recv"), exit(EXIT_FAILURE);
	printf("body is %s\n", buffer);
	body = strstr(buffer, "\r\n\r\n");
	if (strlen(body) > 0)
		*body = 0, body += strlen("\r\n\r\n");
	s = strtok_r(buffer, "\r\n", &start), method = strtok(s, " ");
	printf("method is %s\n", method);
	path = strtok(NULL, " "), printf("%s %s", method, path);
	if (strcasecmp(path, "/todos") != 0)
		response = "HTTP/1.1 404 Not Found\r\n\r\n";
	else
	{
		header = strtok_r(NULL, "\r\n\r\n", &start);
		while (header)
		{
			key = trim(strtok_r(header, ":", &ptr));
			value = trim(strtok_r(NULL, "\r\n", &ptr));
			if (!strcasecmp(key, "Content-Length"))
				content_length = atoi(value);
			header = strtok_r(NULL, "\r\n", &start);
		}
		if (content_length == 0 && strcasecmp(method, "POST") == 0)
			response = "HTTP/1.1 411 Length Required\r\n\r\n";
		else
		{
			if (strcasecmp(method, "POST") == 0)
				response = handle_post(body, content_length);
			else if (strcasecmp(method, "GET") == 0)
				response = handle_get();
		}
	}
	send(client_socket, response, strlen(response), 0);
	res_check(response), close(client_socket);
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
		printf("%s ", client_ip);
		process_request(client_socket);
		free(client_ip);
	}
	close(server_socket);
	return (0);
}
