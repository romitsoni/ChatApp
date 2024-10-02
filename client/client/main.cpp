
// steps for the client
// initialize winsock
// create socket
// connect to the server
//send/recv
// close the socket

#include<iostream>
#include<WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include<WS2tcpip.h>
#include<thread>
#include<string>

using namespace std;


bool initialize() {
	WSADATA wsadata;
	int result = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (result != 0) {
		return false;
	}
	return true;
}
void sendMessage(SOCKET S) {

	cout << "Enter your chat Name: " << endl;
	string name;
	getline(cin, name);
	string message;
	
	while (1) {
		getline(cin, message);
		string msg = name + ": " + message;
		send(S, msg.c_str(), msg.length(), 0);

		if (message == "quit") {
			cout << "Stopping the application" << endl;
			break;
		}
	}
	closesocket(S);
	//WSACleanup();
}

void receiveMessage(SOCKET S) {
	char receiveBuffer[5000];
	while (1) {
		
		int bytesReceived = recv(S, receiveBuffer, sizeof(receiveBuffer), 0);
		if (bytesReceived <= 0) {
			cout << "Failed to received Data" << endl;
			break;
		}
		receiveBuffer[bytesReceived] = '\0';
		cout << "Message From the Client: " <<receiveBuffer<<endl;

	}
	closesocket(S);
	//WSACleanup();

}

int main() {
	
	if (!initialize()) {
		cout << "winsock api startup is failed for the client" << endl;
		return 1;
	}
	cout << "Windows Socket is Started for the client" << endl;

	SOCKET S;
	S = socket(AF_INET, SOCK_STREAM, 0);
	if (S == INVALID_SOCKET) {
		cout << "Socket Creation is failed :" << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(1234);
	int res = inet_pton(AF_INET, "127.0.0.1",&serverAddress.sin_addr);

	if (res <= 0) {
		cout << "Error Caught in conversion of IP Address from String to the Binary Format" << endl;
		closesocket(S);
		WSACleanup();
		return 1;
	}
	int result = connect(S, (SOCKADDR*)(&serverAddress), sizeof(serverAddress));

	if (result == SOCKET_ERROR) {
		cout << "Connection to the server has been failed due to error code : " << WSAGetLastError() << endl;
		closesocket(S);
		WSACleanup();
		return 1;
	}
	cout << "Connection to the Server from the Client is successfully established" << endl;

	thread senderThread(sendMessage, S);
	thread receiverThread(receiveMessage, S);

	senderThread.join();
	receiverThread.join();

	return 0;
}