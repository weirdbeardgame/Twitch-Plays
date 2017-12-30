#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "Keys.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_PORT "6667"

enum class state{CONNECTING, CONNECTED};


class IRC
{
private:
	

	WSADATA wsaData;
	SOCKET connectSocket = INVALID_SOCKET;
	state st;

	//Sent data.
	std::string sendBuf;
	char recievebuf[512];

	char pong[24] = "PONG : tmi.twitch.tv\r\n";
	std::string controls = "Up Down Left Right Cross, Circle, Square, Triagle, Start, Select \r\n";
	

	//Size of Buffers.
	int len = 0;
	int len2 = 0;
	int len3 = 0;

	int status = 0; 
	int total = 0; 
	int sendbuflen = 0; 
		
public:
	IRC();
	Keys key;
	int receiveAll(int s);
	void sendAll(int s, std::string buff, int *len);
	int connection(std::string &oauth, std::string &userName, std::string &botName, std::string &service);
	state setState(state s) { return st = s; }
	~IRC();
};

