/*
 * RemotePlayer.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: eviatar
 */

#include "RemotePlayer.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
using namespace std;
RemotePlayer::RemotePlayer(const char *serverIP, int serverPort) {
	// TODO Auto-generated constructor stub
	server_IP_ = serverIP;
	server_port_ = serverPort;
	client_socket_ = 0;
}

void RemotePlayer::connectToServer() {
	// create a socket point
	client_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket_ == -1) {
		throw "Error opening socket";
	}
	// convert the ip string to a network address
	struct in_addr address;
	if (!inet_aton(server_IP_, &address)) {
		throw "Cant parse IP address";
	}
	// get a hostent structure for the given host address
	struct hostent *server;
	server = gethostbyaddr((const void *)&address, sizeof address, AF_INET);
	if (server == NULL) {
		throw "Host is unreachable";
	}
	//create a structure for the server address
	struct sockaddr_in server_address;
	bzero((char*)&address, sizeof(address));

	server_address.sin_family = AF_INET;
	memcpy((char*)&server_address.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
	// htons converts values between host and network byte orders
	server_address.sin_port = htons(server_port_);

	// establish a connection with the TCP server
	if (connect(client_socket_, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
		throw "Error connecting to server";
	}
	cout << "Connected to server" << endl;
}
RemotePlayer::~RemotePlayer() {
	// TODO Auto-generated destructor stub
}

