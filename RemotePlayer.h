/*
 * RemotePlayer.h
 *
 *  Created on: Dec 5, 2017
 *      Author: eviatar
 */

#ifndef REMOTEPLAYER_H_
#define REMOTEPLAYER_H_

class RemotePlayer {
public:
	RemotePlayer(const char *serverIP, int serverPort);
	void connectToServer();
	virtual ~RemotePlayer();
private:
	int client_socket_;
	int server_port_;
	const char *server_IP_;
};

#endif /* REMOTEPLAYER_H_ */
