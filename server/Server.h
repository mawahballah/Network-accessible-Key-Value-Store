#pragma once

#include "LRUCache.h"
#include <WinSock2.h>
#include <iostream>
#include "Ws2tcpip.h"
#include <tchar.h>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <windows.h>
class Server
{
	Server() {
		instance = NULL;
		mutex = CreateMutex(NULL, FALSE, NULL);
	}
	static Server* instance;
	static HANDLE mutex;
public:
	static Server GetInstance();
	~Server() { delete instance; }
	struct ConnectionParams {
		SOCKET client;
		LRUCache* cache;

		ConnectionParams(SOCKET client, LRUCache* cache) {
			this->client = client;
			this->cache = cache;
		}
	};

	static vector<string> operation_variables(string message);
	static bool isvalid_message(string message);

	static void process_connection(void * data);

	static void start_server(void * data);
};

