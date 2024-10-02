Chat Application Using Socket Programming

This is a simple chat application built using C++ and Winsock. It allows multiple clients to connect to a server and exchange messages in real-time.

Features:
-  Client-Server Architecture: A server that listens for incoming connections and multiple clients that can connect to the server.
-  Multi-threading: Each client runs on a separate thread, allowing simultaneous message exchanges.
-  Real-time Communication: Clients can send and receive messages from the server.


Technologies Used:
- C++ 
- Winsock for socket programming
- Multithreading to handle multiple client connections

 How It Works:
1. The server is initialized and listens for incoming client connections.
2. Once clients connect, the server creates a separate thread for each client.
3. Clients can send messages which are then broadcasted to other connected clients by the server.
4. The communication continues until the client decides to disconnect.

 Prerequisites:
- Windows OS
- Visual Studio for running and compiling the code
- Winsock Library (included by default with Windows)

 Steps to Run:
 1. Server Side:
- Open the `server.cpp` file in Visual Studio.
- Compile and run the server.
- The server will start listening on port `1234` for incoming client connections.

2. Client Side:
- Open the `client.cpp` file in Visual Studio.
- Compile and run the client.
- The client will try to connect to the server on the local IP address `127.0.0.1` and port `1234`.
- Enter your name and start chatting with other connected clients.



Screenshots:
Here are some screenshots showing the application in action:

 1. Server Started:
(![Server Started](./screenshots/server_started.png))

2. Multiple Clients Communication:
![Multiple Clients Communication](./screenshots/Multiple_Clients_Communication.png)