/*
 * Printer.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: eviatar
 */

#include "Printer.h"
#include <iostream>
using namespace std;
Printer::Printer() {
	// TODO Auto-generated constructor stub

}
void Printer::welcomeMessage() {
	cout << "Welcome to Reversi!" << endl;
	cout << "Please choose if you would like to play against another player " <<
			"or against the computer" << endl;
	cout << "1) Play against another player" << endl;
	cout << "2) Play against the computer" << endl;
	cout << "3) Play against a remote player" << endl;
}
Printer::~Printer() {
	// TODO Auto-generated destructor stub
}

