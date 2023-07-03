#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    // Receive the client request
    bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("Error receiving request");
        exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0';
    printf("Raw request:\n%s\n", buffer);

    // Parse the request path and query parameters
    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");
    strtok(NULL, "\r\n"); // Skip the HTTP version line
    char *query = strchr(path, '?');
    if (query) {
        *query = '\0'; // Remove the '?' to separate path and query
        query++; // Move to the query string
    }

    printf("Path: %s\n", path);
    if (query) {
        printf("Query: ");
        char *token = strtok(query, "&");
        while (token) {
            char *key = strtok(token, "=");
            char *value = strtok(NULL, "=");
            printf("\"%s\" -> \"%s\"\n", key, value);
            token = strtok(NULL, "&");
        }
    }

    // Send a response to the client
    const char *response = "HTTP/1.1 200 OK\r\n"
                           "Content-Length: 0\r\n"
                           "Connection: close\r\n"
                           "\r\n";
    ssize_t bytes_sent = send(client_socket, response, strlen(response), 0);
    if (bytes_sent < 0) {
        perror("Error sending response");
        exit(EXIT_FAILURE);
    }

    // Close the client socket
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

