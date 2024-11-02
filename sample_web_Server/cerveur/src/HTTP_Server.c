#include "E:\downloads_29_10_24\sample_web_Server\cerveur\include\HTTP_Server.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
//IMPORT THE NECESSARY LIBLARIES i.e the socket and ws2tcpip
#pragma comment(lib, "ws2_32.lib")  // This line tells the compiler to link the Winsock library (ws2_32.lib) so that the socket functions can be used in the program.

void init_server(HTTP_Server *http_server, int port) {
    // Initialize Winsock/Server by passing port as the parameter
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return;
    }
    /*WSAStartup is crucial inbuilt function in the winsoc2 lib,for preparing your application to use Winsock for network operations. 
    Without it, any subsequent calls to socket functions would likely fail, 
    as the necessary environment wouldn't be set up. After finishing with Winsock operations,
     it's also important to call WSACleanup to free up resources allocated by Winsock.
     here the MAKEWORD(2,2) tells that the version of Winsoc2 is 2.2
     */

    http_server->port = port;

    // Create socket
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }/*A socket is created using the inbuilt socket function:
AF_INET: Indicates that the socket will use IPv4 addresses.
SOCK_STREAM: Indicates that it will be a stream socket (TCP). */

    // Set up server address structure
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    /*A sockaddr_in structure is defined to hold the server's address information.
The following fields are set:
sin_family: Set to AF_INET for IPv4.
sin_port: Set to the specified port using htons to convert from host byte order to network byte order.
sin_addr.s_addr: Set to INADDR_ANY, which means the server will accept connections on any local address. */


    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return;
    }
    /*The bind function associates the socket with the specified address and port.
If binding fails, an error message is printed, the socket is closed, Winsock resources are cleaned up, and the function returns.
    */


    // Listen for connections
    if (listen(server_socket, 5) == SOCKET_ERROR) {
        printf("Listen failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return;
    }
/*The listen function makes the socket ready to accept incoming connections.
The second parameter (5) specifies the maximum number of pending connections that can be queued.
If listening fails, an error message is printed, the socket is closed, Winsock resources are cleaned up, and the function returns.
*/


    http_server->socket = server_socket;
    printf("HTTP Server Initialized\nPort: %d\n", http_server->port);
}
