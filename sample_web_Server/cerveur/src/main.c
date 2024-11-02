#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <errno.h>

#pragma comment(lib, "ws2_32.lib")

#include "E:\\downloads_29_10_24\\sample_web_Server\\cerveur\\include\\HTTP_Server.h"
#include "E:\\downloads_29_10_24\\sample_web_Server\\cerveur\\include\\Response.h"
#include "E:\\downloads_29_10_24\\sample_web_Server\\cerveur\\include\\Routes.h"

#define RECIPE_FILE_PATH "E:\\downloads_29_10_24\\sample_web_Server\\rms_code_fs\\recipes.txt" //define macro or the filepath

int main() {
    // Initialize Winsock,need to do this again and again
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    // Initialize HTTP_Server
    HTTP_Server http_server;
    init_server(&http_server, 6969); //calling the init_Server from the HTTP_server.h header file and passing the port

    SOCKET client_socket;//creating the socket

    // Registering Routes
    struct Route* route = initRoute("/", "index.html"); //initialize the route '/' to render index.html
    addRoute(route, "/about", "about.html"); //add a route with endpoint /about to render about.html

    printf("\n====================================\n");
    printf("========= ALL AVAILABLE ROUTES ========\n");
    inorder(route); // Display all available routes

    while (1) { //This infinite loop handles incoming client connections. It accepts a client connection and receives messages
        char client_msg[4096] = "";

        client_socket = accept(http_server.socket, NULL, NULL);
        if (client_socket == INVALID_SOCKET) {
            printf("Accept failed: %d\n", WSAGetLastError());
            continue;
        }

        recv(client_socket, client_msg, sizeof(client_msg) - 1, 0);
        printf("%s\n", client_msg);

        // Parsing client request for HTTP method and route
        char *method = NULL, *urlRoute = NULL;
        char *client_http_header = strtok(client_msg, "\n");
        char *header_token = strtok(client_http_header, " ");
        int header_parse_counter = 0;
        /*The strtok() method splits str[] according to given delimiters and returns the next token. 
        It needs to be called in a loop to get all tokens. It returns NULL when there are no more tokens. 
        The code splits the client message to extract the HTTP method (e.g., GET) and the requested URL route.*/

        while (header_token != NULL) {
            if (header_parse_counter == 0)
                method = header_token;
            else if (header_parse_counter == 1)
                urlRoute = header_token;

            header_token = strtok(NULL, " ");
            header_parse_counter++;
        }

        printf("Method: %s\nRoute: %s\n", method, urlRoute);

        char content_type[50] = "Content-Type: text/html\r\n";
        char response_data[4096] = "<html><body>";
        char http_header[4096]; // Declare http_header here

        // Serve the content of recipes.txt for the root URL
        if (strcmp(urlRoute, "/") == 0) { //if route is '/' open recipe.txt 
            FILE *file = fopen(RECIPE_FILE_PATH, "r");
            if (file == NULL) {
                perror("Could not open recipes.txt"); //if error(might be because of non existent files) throw error 
                strcat(response_data, "<h1>500 Internal Server Error</h1>"); //apeend this header to response_Data variable
            } else {
                char line[256]; //initialize the buffer to hold each line from the recipe.txt
                int line_count = 0; //count the no of lines

                while (fgets(line, sizeof(line), file) != NULL) { // The fgets function reads up to 255 characters or until a newline character is encountered. and stores the travesed lines into line var
                    // Process the recipe lines, 
                    if (line_count % 7 == 0) { // Recipe name i.e. fetch the first line
                        strcat(response_data, "<div class='recipe'><h2>");
                        strcat(response_data, line);
                        strcat(response_data, "</h2><p><strong>Ingredients:</strong> ");
                    } else if (line_count % 7 == 1) {
                        strcat(response_data, line); // Ingredients i.e fetch the second line and so on
                    } else if (line_count % 7 == 2) {
                        strcat(response_data, "</p><p><strong>Instructions:</strong> ");
                        strcat(response_data, line); // Instructions
                    } else if (line_count % 7 == 3) {
                        // Ensure this path is correct and relative to the server
                        strcat(response_data, "</p><p><strong>Image:</strong> <img src='/static/images/");
                        strcat(response_data, line); // Image file name
                        strcat(response_data, "' alt='Recipe Image' style='width:100px;height:auto;' /></p>");
                    } else if (line_count % 7 == 4) {
                        strcat(response_data, "<p><strong>Time Required:</strong> ");
                        strcat(response_data, line); // Time required
                    } else if (line_count % 7 == 5) {
                        strcat(response_data, "<p><strong>Cuisine:</strong> ");
                        strcat(response_data, line); // Cuisine
                    } else if (line_count % 7 == 6) {
                        strcat(response_data, "<p><strong>Dish Type:</strong> ");
                        strcat(response_data, line); // Dish type
                        strcat(response_data, "</p></div>"); // Close recipe div
                    }
                    line_count++;
                }

                fclose(file);
            }
        } else if (strstr(urlRoute, "/static/") == urlRoute) { //find urlroute in static using strstr
            // Serve static files
            char file_path[256];
            snprintf(file_path, sizeof(file_path), "E:\\downloads_29_10_24\\sample_web_Server\\cerveur\\%s", urlRoute);
            //finding the image files
            FILE *file = fopen(file_path, "rb");
            if (file) {
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                fseek(file, 0, SEEK_SET);

                char *file_content = malloc(file_size);
                fread(file_content, 1, file_size, file);
                fclose(file);

                // Set Content-Type for image based on file extension
                const char *content_type = "Content-Type: image/jpeg\r\n"; // Assuming jpeg; modify if needed
                snprintf(http_header, sizeof(http_header), "HTTP/1.1 200 OK\r\n%sContent-Length: %ld\r\n\r\n", content_type, file_size);
                //snprinf is a prinf fucntion but for formatting strings
                send(client_socket, http_header, (int)strlen(http_header), 0);
                send(client_socket, file_content, file_size, 0);
                free(file_content);
                continue; // Continue to avoid sending additional response below
            } else {
                snprintf(http_header, sizeof(http_header), "HTTP/1.1 404 Not Found\r\n\r\n");
                send(client_socket, http_header, (int)strlen(http_header), 0);
                continue; // Continue to avoid sending additional response below
            }
        } else {
            struct Route *destination = search(route, urlRoute); //create a destination node and call the search function to find the file
            if (destination == NULL) {
                strcat(response_data, "<h1>404 Not Found</h1>");
            } else {
                strcat(response_data, "<h1>Serving file: ");
                strcat(response_data, destination->value);
                strcat(response_data, "</h1>");
            }
        }

        strcat(response_data, "</body></html>"); // Close body and html tags

        // Prepare HTTP response for HTML content
        snprintf(http_header, sizeof(http_header), "HTTP/1.1 200 OK\r\n%s\r\n", content_type);

        // Send the response
        send(client_socket, http_header, (int)strlen(http_header), 0);
        send(client_socket, response_data, (int)strlen(response_data), 0);
        closesocket(client_socket); //closing connection code
    }

    // Clean up Winsock
    WSACleanup();
    return 0;
}
