/*
 * Eviatar Natan
 * 307851808
 */
/*
 * main.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: eviatar
 */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Server.h"
#include <fstream>
using namespace std;
int readPortFromFile();
int main () {
	int port = readPortFromFile();
	Server server(port);
	try {
		server.start();
	} catch (const char *msg) {
		cout << "Connection Failed. Reason: " << msg << endl;
		exit(-1);
	}
  server.stop();

}
/*
 * the function tries to open the server settings file.
 * if opening the file was successful, the function will read the port
 * number from the file, and then return it back.
 * if opening the file failed, the port -1 will be returned.
 */
int readPortFromFile() {
	ifstream server_settings;
	int port;
	server_settings.open("ServerSettings.txt");
	if (server_settings.is_open()) {
		string port_string;
		server_settings >> port_string;
		server_settings >> port;
		server_settings.close();
		cout << "port is " << port << endl;
		return port;
	}
	else {
		cout << "failed opening the file" << endl;
		port = -1;
		return port;
	}

}


