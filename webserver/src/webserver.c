#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>

#define PORT 8080
#define MAX_REQUEST_SIZE 1024

#define ROOT_FOLDER "./"
#define HTTP_HEADER "HTTP/1.1 200 OK\nContent-Type: text/html\n\n"

void handle_request(int);
void send_file(int, const char*);

int main(int argc, char *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is running...\n");

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
        }

        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}

void handle_request(int socket) {
    char request_buffer[MAX_REQUEST_SIZE] = {0};
    int valread = read(socket, request_buffer, MAX_REQUEST_SIZE);

    char *file_path = strtok(request_buffer, " ");
    file_path = strtok(NULL, " ");

    if (strcmp(file_path, "/") == 0 || strcmp(file_path, "/\0") == 0) {
        file_path = "/index.html";
    }

    char full_path[100];
    strcpy(full_path, ROOT_FOLDER);
    strcat(full_path, file_path);
    send_file(socket, full_path);
}

void send_file(int socket, const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *file_content = malloc(file_size * sizeof(char));
    if (file_content == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    fread(file_content, 1, file_size, file);
    send(socket, HTTP_HEADER, strlen(HTTP_HEADER), 0);
    send(socket, file_content, file_size, 0);
    fclose(file);
    free(file_content);
}
