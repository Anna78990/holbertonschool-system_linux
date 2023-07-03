#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_TODOS 10

typedef struct {
    int id;
    char title[100];
    char description[200];
} Todo;

Todo todos[MAX_TODOS];
int numTodos = 0;

void addTodo(const char *title, const char *description) {
    if (numTodos >= MAX_TODOS) {
        printf("Maximum number of todos reached.\n");
        return;
    }

    Todo todo;
    todo.id = numTodos;
    strncpy(todo.title, title, sizeof(todo.title));
    strncpy(todo.description, description, sizeof(todo.description));

    todos[numTodos++] = todo;
}

const char *getTodosJson() {
    static char json[MAX_BUFFER_SIZE] = "[";
    int length = sizeof(json);

    for (int i = 0; i < numTodos; i++) {
        Todo todo = todos[i];
        char todoJson[MAX_BUFFER_SIZE];
        snprintf(todoJson, sizeof(todoJson), "{\"id\":%d,\"title\":\"%s\",\"description\":\"%s\"}",
                 todo.id, todo.title, todo.description);

        length += snprintf(json + length, sizeof(json) - length, "%s%s", i == 0 ? "" : ",", todoJson);
    }

    snprintf(json + length, sizeof(json) - length, "]");

    return json;
}

void handleRequest(const char *method, const char *path) {
    if (strcmp(method, "GET") == 0 && strcmp(path, "/todos") == 0) {
        const char *todosJson = getTodosJson();

        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: application/json\n");
        printf("Content-Length: %lu\n", strlen(todosJson));
        printf("\n");
        printf("%s", todosJson);
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("\n");
    }
}

int main(void) {
    addTodo("Dishes", "Not_really_urgent");
    addTodo("Laundry", "To_be_done_by_yesterday");

    const char *request = "GET /todos HTTP/1.1\n"
                          "User-Agent: curl/7.35.0\n"
                          "Host: localhost:8080\n"
                          "Accept: */*\n"
                          "\n";

    // Simulating receiving a request
    handleRequest("GET", "/todos");

    return 0;
}

