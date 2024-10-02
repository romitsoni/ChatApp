#include<iostream>
#include<WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include<thread>
#include<vector>

using namespace std;

void InteractWithClient(SOCKET clientSocket,vector<SOCKET>& Clients) {

	char buffer[5000];
	while (1) {
		int result = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (result < 0) {
			cout << "Receiving the data has been failed" << WSAGetLastError() << endl;
			break;
		}
		else if (result == 0) {
			cout << "connection is closed by the client" << endl;
			break;
		}
		else {
			string msg = "";
			msg = string(buffer, result);
			cout << "Msg from client.. " << msg << endl;
		}
		for (auto client : Clients) {
			if (client != clientSocket) {
				send(client, buffer, result, 0);

			}
		}
	}
	auto it = find(Clients.begin(), Clients.end(), clientSocket);
	if (it != Clients.end()) {
		Clients.erase(it);
	}
	closesocket(clientSocket);

}

int main() {	

	WSADATA wsaData;
	sockaddr_in addr;
	int result= WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		cout << "Winsock startup is failed " << endl;
		WSACleanup();
		return 1;
	}
	else {
		cout << "Server Winsock is started" << endl;
	}


	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cout << "Socket creation is failed with error"<< WSAGetLastError() <<endl;
		WSACleanup();
		return 1;
	}
	else {
		cout << "Server Socket is created successfully" << endl;

	}


	int port = 1234;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);





	result = bind(sock, (SOCKADDR*)(&addr), sizeof(addr));
	if (result == SOCKET_ERROR) {
		cout << "Binding Socket to the ip and port has been failed due to the error: " << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	else {
		cout << "Binding IP and Port is Success" << endl;
	}





	result = listen(sock, SOMAXCONN);
	if (result == SOCKET_ERROR) {
		cout << "Listening process is falied due to the error: " << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	else {
		cout << "Server is Listening in the Port: " <<port<< endl;
	}

	vector<SOCKET> Clients;


	while (1) {
		SOCKET clientSocket = accept(sock, nullptr, nullptr);

		if (clientSocket == INVALID_SOCKET) {
			cout << "Invalid Client Socket" << WSAGetLastError() << endl;
		}
		else {
			cout << "Client is connected.." << endl;
		}
		Clients.push_back(clientSocket);

		thread t1(InteractWithClient, clientSocket, ref(Clients));
		t1.detach();


	}



	closesocket(sock);
	WSACleanup();

	return 0;
}

