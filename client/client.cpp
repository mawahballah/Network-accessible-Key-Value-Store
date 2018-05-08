#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include"Ws2tcpip.h"
#include<tchar.h>
#include<string>
#include<string.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

void process_command(SOCKET socket)
{
	string command;
	while (getline(cin,command))
	{	
		char reply[256] = {};
		send(socket, command.data(), command.size(), NULL);
		recv(socket, reply,sizeof(reply), NULL);
		string serverout(reply);
		cout << serverout<<endl;
	}
}

int main()
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
	InetPton(AF_INET, _T("127.0.0.1"), &addr.sin_addr.s_addr);//localhost address	
	addr.sin_port = htons(1111); //Port = 1111
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL); //Set Connection socket
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) //If we are unable to connect...
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return 0; //Failed to Connect
	}
	std::cout << "Connected!" << std::endl;
	process_command(Connection);
}

