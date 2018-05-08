#include "Server.h"

Server* Server::instance = NULL;
HANDLE Server::mutex = NULL;

Server Server::GetInstance() {
	if (instance == NULL) {
		instance = new Server();
	}
	return *instance;
}

vector<string> Server::operation_variables(string message) {
	stringstream ss(message);
	string token;
	vector<string> tokens;
	while (ss >> token) {
		tokens.push_back(token);
	}
	return tokens;
}

bool Server::isvalid_message(string message) {
	vector<string> tokens = operation_variables(message);
	if (tokens.size() > 0) {
		if (tokens[0] == "quit" && tokens.size() == 1)
			return true;
		else if ((tokens[0] == "get" || tokens[0] == "delete") && tokens.size() == 2)
			return true;
		else if (tokens[0] == "put" && tokens.size() == 3)
			return true;
	}
	return false;
}

void Server::process_connection(void * data) {
	ConnectionParams& connection = *(ConnectionParams *)data;

	SOCKET client = connection.client;
	LRUCache* cache = connection.cache;

	while (1) {
		char MOTD[256] = {}; //Create buffer with message of the day
		int bytesreceived;
		string message;
		if (bytesreceived = recv(client, MOTD, sizeof(MOTD), 0) > 0) {
			message = MOTD;
			printf("receive %s from client %d\n", message.c_str(), client);
			if (isvalid_message(message)) {

				vector<string> operation = operation_variables(message);
				string cmd, key, value;
				cmd = operation[0];

				if (operation.size() >= 2)
					key = operation[1];
				if (operation.size() >= 3)
					value = operation[2];

				if (cmd == "quit") {
					break;
				}
				else {
					WaitForSingleObject(mutex, INFINITE);
					if (cmd == "get") {
						message = cache->get(key);
					}
					else if (operation[0] == "delete") {
						cache->deleteentry(key);
						message = "successful operation";
					}
					else if (operation[0] == "put") {
						if (cache->getCapacity() < key.size() + value.size()) {
							message = "Cache Overflow";
						}
						else {
							cache->put(key, value);
							message = "successful operation";
						}
					}
					ReleaseMutex(mutex);
				}
			}
			else {
				message = "not valid";
			}
			send(client, message.data(), message.size(), NULL);

		}
		Sleep(100);
	}
	printf("End Call\n");
}

void Server::start_server(void * data) {
	LRUCache& cache = *(LRUCache *)data;
	//WinSock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr); //length of the address (required for accept call)
	InetPton(AF_INET, _T("127.0.0.1"), &addr.sin_addr.s_addr);//Broadcast locally	
	addr.sin_port = htons(1111); //Port
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //Create socket to listen for new connections
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //Bind the address to the socket
	while (1)
	{
		listen(sListen, SOMAXCONN); //Places sListen socket in a state in which it is listening for an incoming connection. Note:SOMAXCONN = Socket Oustanding Max Connections
		SOCKET newConnection; //Socket to hold the client's connection
		newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); //Accept a new connection
		if (newConnection == 0) //If accepting the client connection failed
		{
			cout << "Failed to accept the client's connection." << endl;
		}
		else //If client connection properly accepted
		{
			cout << "Client Connected! " << newConnection << endl;

			ConnectionParams connection(newConnection, &cache);
			_beginthread(&process_connection, 0, &connection);
			
		}
	}
}

