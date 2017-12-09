/*
 * Server.h
 *
 *  Created on: Dec 5, 2017
 *      Author: eviatar
 */

#ifndef SERVER_H_
#define SERVER_H_

class Server {
public:
	Server(int port);
	void start();
	void stop();
	virtual ~Server();
private:
	int port_;
	int server_socket_;

	void handleClient(int player_socket, int player2_socket);
	int calc(int arg1,const char op, int arg2) const;
};

#endif /* SERVER_H_ */
