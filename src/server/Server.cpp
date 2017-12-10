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
Server::Server(int port) {
	// TODO Auto-generated constructor stub
	port_=port;
	server_socket_=0;
	cout << "Server" <<endl;
}
void Server::start(){
	server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket_ == -1) {
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
				throw "Error on binding";
			}
	// start listening to incoming connections
	listen(server_socket_, MAX_CONNECTED_CLIENTS);
	// Define the client socket's structures
	struct sockaddr_in player_address;
	socklen_t player_address_len;
	int first_player, second_player;
	while (true) {
		cout << "Waiting for client connections..." << endl;
		int player_socket = accept(server_socket_, (struct sockaddr *)&player_address, &player_address_len);
		cout <<"Player 1 connected" << endl;
		if (player_socket == -1) {
			throw "Error on accept";
		}
		first_player = 1;
		int n = write(player_socket, &first_player, sizeof(first_player));
		if (n == -1) {
			cout << "Error writing to socket" << endl;
			return;
		}
		int player2_socket = accept(server_socket_, (struct sockaddr *)&player_address, &player_address_len);
				cout <<"Player 2 connected" << endl;
				if (player2_socket == -1) {
					throw "Error on accept";
				}
		second_player = 2;
		n = write(player2_socket, &second_player, sizeof(second_player));
		if (n == -1) {
			cout << "Error writing to socket" << endl;
			return;
	  }
		// write to make the first player wait for the second player connection
		n = write(player_socket, &second_player, sizeof(second_player));
		if (n == -1) {
			cout << "error writing to socket";
			return;
		}
	handleClient(player_socket, player2_socket);

	// close communications with the clients.
	close(player_socket);
	close(player2_socket);
  }
}
void Server::handleClient(int player_socket, int player2_socket) {
	int x_value, y_value;
	const int end_game = 0 ;
	while (true) {

		//reads from first player
		int n = read(player_socket, &x_value, sizeof(x_value));
		if (n == -1) {
			cout << "error reading x value" << endl;
			return;
		}
		if (n == 0) {
			cout << "player disconnected" << endl;
			return;
		}
		n = read(player_socket, &y_value, sizeof(y_value));
		if (n == -1) {
			cout << "error reading y value" << endl;
			return;
		}
		// return if both players have no available moves
		if (x_value == end_game && y_value == end_game) {
			return;
		}
		/*if (isClientClosed(player2_socket)) {
			return;
		}*/
		n = write(player2_socket, &x_value, sizeof(x_value));
		if (n == -1) {
			cout << "error writing to socket";
		}
		n = write(player2_socket, &y_value, sizeof(y_value));
		if (n == -1) {
			cout << "error writing to socket";
		}

		//reads from second player
		n = read(player2_socket, &x_value, sizeof(x_value));
		if (n == -1) {
			cout << "error reading x value" << endl;
			return;
		}
		if (n == 0) {
			cout << "player disconnected" << endl;
			return;
		}
		n = read(player2_socket, &y_value, sizeof(y_value));
		if (n == -1) {
			cout << "error reading y value" << endl;
			return;
		}
		// return if both players have no available moves
		if (x_value == end_game && y_value == end_game) {
			return;
		}
		/*if (isClientClosed(player_socket)) {
			return;
		}*/
		n = write(player_socket, &x_value, sizeof(x_value));
		if (n == -1) {
			cout << "error writing to socket";
		}
		n = write(player_socket, &y_value, sizeof(y_value));
		if (n == -1) {
			cout << "error writing to socket";
		}
	}

}
bool Server::isClientClosed(int player_socket) {
	pollfd pfd;
	pfd.fd = player_socket;
	pfd.events = POLLIN | POLLHUP | POLLRDNORM;
	pfd.revents = 0;
		//call poll with a timeout of 100 ms
		if (poll(&pfd, 1, 100) > 0) {
			//if result>0, data available on socket or socket has been closed.
			char buffer[32];
			if (recv(player_socket,buffer,sizeof(buffer),MSG_PEEK | MSG_DONTWAIT) ==0) {
				//if recv returns zero, it means the connection has been closed.
				return true;
			}
		}
	return false;
}
void Server::stop(){
	close(server_socket_);
}
Server::~Server() {
	// TODO Auto-generated destructor stub
}

