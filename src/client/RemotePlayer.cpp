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
RemotePlayer::RemotePlayer(const char *serverIP, int serverPort, char symbol):
	server_IP_(serverIP), server_port_(serverPort), client_socket_(0) {
	// TODO Auto-generated constructor stub
	cout << "Client" <<endl;
	//server_IP_ =
}

void RemotePlayer::connectToServer() {
	// create a socket point
	if (server_IP_ == NULL) {
		cout << "it's null :(" <<endl;
	}
	if (server_port_==NULL) {
		cout << "port is null :(" <<endl;
	}
	cout <<"is it here 1 before crash?" <<endl;
	client_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket_ == -1) {
		throw "Error opening socket";
	}
	// convert the ip string to a network address
	cout <<"is it here 2 before crash?" <<endl;
	struct in_addr address;
	if (!inet_aton(server_IP_, &address)) {
		throw "Cant parse IP address";
	}
	// get a hostent structure for the given host address
	cout <<"is it here 3 before crash?" <<endl;
	struct hostent *server;
	server = gethostbyaddr((const void *)&address, sizeof address, AF_INET);
	if (server == NULL) {
		throw "Host is unreachable";
	}
	cout <<"is it here 4 before crash?" <<endl;
	//create a structure for the server address
	struct sockaddr_in server_address;
	bzero((char*)&address, sizeof(address));

	server_address.sin_family = AF_INET;
	memcpy((char*)&server_address.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
	// htons converts values between host and network byte orders
	server_address.sin_port = htons(server_port_);
	cout <<"is it here 5 before crash?" <<endl;
	// establish a connection with the TCP server
	if (connect(client_socket_, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
		throw "Error connecting to server";
	}
	cout << "Connected to server" << endl;
}
int RemotePlayer::getDisksNum() {
  //return disks_num_;
}
void RemotePlayer::setDisksNum(int disks_num) {
  //disks_num_ = disks_num_ + disks_num;
}
bool RemotePlayer::getMyTurn() {
  //return my_turn_;
}
void RemotePlayer::setMyTurn(bool status) {
  //my_turn_ = status;
}
char RemotePlayer::getSymbol() {
  //return symbol_;
}
void RemotePlayer::setSymbol(char symbol) {
  //symbol_ = symbol;
}
char RemotePlayer::getOppositeSymbol() {
  //return other_symbol_;
}
void RemotePlayer::setOppositeSymbol(char other_symbol) {
  //other_symbol_ = other_symbol;
}
void RemotePlayer::turn(GameLogic*& logic, Board*& board, Player*& other) {

}
RemotePlayer::~RemotePlayer() {
	// TODO Auto-generated destructor stub
}

