/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Server.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: eviatar
 */

#include "Server.h"
#include <sys/socket.h>
#include <poll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX_CONNECTED_CLIENTS 10
pthread_mutex_t lock_server_run;
pthread_mutex_t lock_server_accept;
pthread_mutex_t lock_server_wait;
pthread_mutex_t lock_server_close;
Server::Server(int port) {
	// TODO Auto-generated constructor stub
	port_=port;
	server_socket_=0;
	running = 1;
	cout << "Server" <<endl;
}
void Server::start(){
	pthread_t thread;
	server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	Handler handler;
	int *client_socket = new int[1];
	if (server_socket_ == -1) {
		delete[] client_socket;
		throw "Error opening socket";
	}
	//assign a local address to the socket
	struct sockaddr_in serverAddress;
	bzero((void *)&serverAddress, sizeof (serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port_);
	if (bind(server_socket_, (struct sockaddr*)&serverAddress,
			sizeof(serverAddress)) == -1) {
				delete[] client_socket;
				throw "Error on binding";
			}
	// start listening to incoming connections
	listen(server_socket_, MAX_CONNECTED_CLIENTS);
	cout << "In server:\n" << endl;
	cout << "listening to port\n" << endl;
	Info *info = new Info();
	info->handler = &handler;
	info->running = &running;
	// accepts a new client connection
	AcceptStruct *accept_struct = new AcceptStruct();
	pthread_mutex_lock(&lock_server_run);
	accept_struct->server_socket = &server_socket_;
	pthread_mutex_unlock(&lock_server_run);
	accept_struct->client_socket = client_socket;
	pthread_mutex_lock(&lock_server_run);
	accept_struct->handler = &handler;
	pthread_mutex_unlock(&lock_server_run);
	pthread_mutex_lock(&lock_server_run);
	accept_struct->running = &running;
	pthread_mutex_unlock(&lock_server_run);
	try {
			// creates a thread that waits for exit message to close server
			pthread_create(&thread, NULL, waitForCloseMessage, (void *)info);
	} catch (const char *message) {
			delete info;
			delete accept_struct;
			delete[] client_socket;
			throw message;
	}
	try {
			// creates a thread in charge of accepting new clients
			pthread_create(&thread, NULL, acceptNewClient, (void *) accept_struct);
	} catch (const char *msg) {
			delete info;
			delete accept_struct;
			delete[] client_socket;
			throw msg;
	}
	// while exit command wasn't entered
	while(true) {
			pthread_mutex_lock(&lock_server_run);
			// if exit command has been entered
			if(running == 0) {
					pthread_mutex_unlock(&lock_server_run);
					break;
			}
			pthread_mutex_unlock(&lock_server_run);
	}
	delete info;
	delete accept_struct;
	delete[] client_socket;
}
void* Server::acceptNewClient(void *accept_struct) {
    AcceptStruct *accept_struct1 = (AcceptStruct*)accept_struct;
    pthread_mutex_lock(&lock_server_accept);
    int serverSocket = *accept_struct1->server_socket;
    pthread_mutex_unlock(&lock_server_accept);
    pthread_mutex_lock(&lock_server_accept);
    Handler *handler = accept_struct1->handler;
    pthread_mutex_unlock(&lock_server_accept);
    pthread_mutex_lock(&lock_server_accept);
    int is_running = *accept_struct1->running;
    pthread_mutex_unlock(&lock_server_accept);
    int temp_client_socket = 0;
    // as long as server is running
    while (is_running) {
        cout << "Waiting for client connections..." << endl;
        struct sockaddr_in firstClientAddress;
        socklen_t firstClientAddressLen;
        // accepting the client
        temp_client_socket = accept(serverSocket, (struct sockaddr *) &firstClientAddress,
                                              &firstClientAddressLen);
        pthread_mutex_lock(&lock_server_accept);
        *accept_struct1->client_socket = temp_client_socket;
        pthread_mutex_unlock(&lock_server_accept);
        pthread_mutex_lock(&lock_server_accept);
        try {
            // run handler
            handler->run(temp_client_socket);
        } catch (const char* msg) {
            pthread_mutex_unlock(&lock_server_accept);
            delete accept_struct1;
            throw msg;
        }
        pthread_mutex_unlock(&lock_server_accept);
        pthread_mutex_lock(&lock_server_accept);
        // update servers running status
        is_running = *accept_struct1->running;
        pthread_mutex_unlock(&lock_server_accept);
    }
    delete accept_struct1;
}

void *Server::waitForCloseMessage(void* info) {
    Info *info1 = (Info*)info;
    string close_server;
    // waits to receive "exit"
    do {
        cin >> close_server;
    } while(close_server.compare("exit") != 0);
    pthread_mutex_lock(&lock_server_wait);
    info1->handler->closeThreads();
    pthread_mutex_unlock(&lock_server_wait);
    pthread_mutex_lock(&lock_server_wait);
    // updates servers running status
    *info1->running = 0;
    pthread_mutex_unlock(&lock_server_wait);
}

void Server::stop() {
    pthread_mutex_lock(&lock_server_close);
    // close the server's socket
    close(server_socket_);
    pthread_mutex_unlock(&lock_server_close);
}
Server::~Server() {
	// TODO Auto-generated destructor stub
}

