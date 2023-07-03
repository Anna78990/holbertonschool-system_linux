#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

char **get_query(char *path)
{
    char** query = NULL;
    char* path_dup = strdup(path);
    char* token = strtok(path_dup, "&");
    int count = 0;

    while (token) {
        query = realloc(query, sizeof(char*) * (count + 1));
        query[count] = strdup(token);
        count++;
        token = strtok(NULL, "&");
    }

    query = realloc(query, sizeof(char*) * (count + 1));
    query[count] = NULL;

    free(path_dup);
    return query;
}

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

void handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    char *path, *q_start, *q_end;
    char **queries;

    bytes_received = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_received < 0)
    {
        perror("Error reading from socket");
        close(client_socket);
        return;
    }
    buffer[bytes_received] = '\0';
    printf("Raw request:\n%s\n", buffer);
    path = get_path(buffer + 4);
    q_start = strchr(path, '?');
    q_end = strstr(q_start, " HTTP");
    for (i = 0; i < q_end - q_start; i++)
    {
	if (i == 0 && q_start[i] != '?')
	{
		buf[i] = '\0';
		break;
	}
	else if (i > 0)
		buf[i - 1] = q_start[i];
	}
    }
    buf[i] = '\0';
    queries = get_query(buf);
    i = 0;
    while (queries[i])
	printf("query[%d] is %s\n", i, queries[i++]);
    
    printf("query_str is %s, path is %s, buffer is %s\n", query_str, path, buffer);
    if (query_str != NULL) {
	printf("I found QUERY\n");
        *query_str = '\0';
        query_str++;
        printf("Path: %s\n", path);
        printf("Queries:\n");

        char *query_token = strtok(query_str, "&");
        while (query_token != NULL) {
            char *key = strtok(query_token, "=");
            char *value = strtok(NULL, "=");
            printf("Query: \"%s\" -> \"%s\"\n", key, value);
            query_token = strtok(NULL, "&");
        }
    } else {
        printf("Path: %s\n", path);
    }

    // Send the HTTP response back to the client
    const char *response = "HTTP/1.1 200 OK\r\n"
                           "Content-Length: 0\r\n"
                           "Connection: close\r\n\r\n";
    write(client_socket, response, strlen(response));

    // Close the connection with the client
    close(client_socket);
}

int main(void) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;

    // Create the socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind the socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }

    // Start listening for client connections
    if (listen(server_socket, 5) < 0) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080\n");

    while (1) {
        // Accept a client connection
        client_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Error accepting connection");
            exit(EXIT_FAILURE);
        }

        // Convert client IP address to string and print it
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        printf("Client connected: %s\n", client_ip);

        // Handle the client request
        handle_client(client_socket);
    }

    // Close the server socket
    close(server_socket);

    return 0;
}
