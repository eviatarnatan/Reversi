/*
 * Eviatar Natan
 * 307851808
 */
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
	/*
	 * the constructor. receive a port and sets the port and the socket.
	 */
	Server(int port);
	/*
	 * start running the server. the server each time wait for two clients to
	 * log to the server. after the clients finished playing the game. the server
	 * will wait for the next 2 players to join the game.
	 */
	void start();
	/*
	 * checks if the client that waits for the other player has closed his
	 * connection.
	 */

	bool isClientClosed(int player_socket);
	/*
	 * stops the server socket
	 */
	void stop();
	/*
	 * default destructor
	 */
	virtual ~Server();
private:
	int port_;
	int server_socket_;
	/*
	 * handles the client. receives a socket from each player and while
	 * the game isn't over, reads and writes points from one client to
	 * the other.
	 */
	void handleClient(int player_socket, int player2_socket);
};

#endif /* SERVER_H_ */
