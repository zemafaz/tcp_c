#include <string.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {

	/**
	  * Create a socket
	  */
	std::cout << "Creating server socket..." << std::endl;
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	
	if (listening == -1) {
		std::cerr << "Can't create a socket!" << std::endl;
		return -1;
	}

	/**
	  * Bind the socket
	  */
	struct sockaddr_in hint;

	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

	std::cout << "Binding socket to sockaddr..." << std::endl;
	if (bind(listening, (struct sockaddr *) &hint, sizeof(hint)) == -1){
		std::cerr << "Can't bind to IP/port" << std::endl;
		return -2;
	}

	/**
	  * Let the socket listen
	  */
	std::cout << "Mark the socket for listening..." << std::endl;
	if (listen(listening, SOMAXCONN) == -1) {
		std::cerr << "Can't listen!";
		return -3;
	}

	/**
	  * Create a client socket and start a call
	  */
	sockaddr_in client;
	socklen_t clientSize = sizeof(client);

	std::cout << "Accept client call..." << std::endl;
	int clientSocket = accept(listening, (struct sockaddr *)&client, &clientSize);

	std::cout << "Received call..." << std::endl;
	if (clientSocket == -1) {
		std::cerr << "Problem with client connecting!" << std::endl;
		return -4;
	}

	std::cout << "Client address: " << inet_ntoa(client.sin_addr) << " and port: " << client.sin_port << std::endl;

	close(listening);

	/**
	  * Exchanging messages
	  */

	char buf[4096];
	while (true) {
		//clear buffer
		memset(buf, 0, 4096);

		// wait for message
		int bytesRecv = recv(clientSocket, buf, 4096, 0);
		if (bytesRecv == -1) {
			std::cerr << "There was a connection issue." << std::endl;
		}
		if (bytesRecv == 0) {
			std::cout << "The client disconnected" << std::endl;
		}

		// display message
		std::cout << "Received: " << std::string(buf, 0, bytesRecv);

		// return message
		send(clientSocket, buf, bytesRecv + 1, 0);
	}

	// close socket
	close(clientSocket);
}
