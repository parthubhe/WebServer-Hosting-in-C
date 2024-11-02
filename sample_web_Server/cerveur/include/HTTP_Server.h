#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

typedef struct HTTP_Server { //we use typedef for aliasilising i.e shortening the structure name so that we do not have to enter struct node * etch again and again
	int socket;
	int port;	
} HTTP_Server;

void init_server(HTTP_Server* http_server, int port);
//function to initialize the server with the given port
#endif
