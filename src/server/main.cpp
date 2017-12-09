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
#include "Server.h"
using namespace std;
int main () {
	Server server(8000);
	try {
		server.start();
	} catch (const char *msg) {
		cout << "Connection Failed. Reason: " << msg << endl;
		exit(-1);
	}
  server.stop();

}



