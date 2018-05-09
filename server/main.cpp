#pragma comment(lib, "ws2_32.lib")
#include "LRUCache.h"
#include "Server.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;

int main()
{

	LRUCache cache(10,CapacityType::BYTES);
	HANDLE server_thread_handle;
	Server s =Server::GetInstance();
	server_thread_handle = (HANDLE)_beginthread(&(Server::start_server), 0, &cache);//not to keep what happens in the main waiting
	WaitForSingleObject(server_thread_handle, INFINITE);
	return 0;
}


