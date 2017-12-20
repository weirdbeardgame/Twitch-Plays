#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "Keys.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_PORT "6667"

class IRC
{
private:
	
	WSADATA wsaData;
	SOCKET connectSocket = INVALID_SOCKET;
	
	//Sent data.
	std::string sendBuf;
	char recievebuf[512];

	char pong[24] = "PONG : tmi.twitch.tv\r\n";
	char *controls = "Controls are: Up Down Left Right Cross, Circle, Square, Triagle, Start, Select\r\n";
	

	//Size of Buffers.
	int len = 0;
	int len2 = 0;
	int len3 = 0;

	int iResult = 0; 
	int total = 0; 
	int sendbuflen = 0; 
		
public:
	IRC();
	Keys key;
	int receiveAll(int s, char * recvbuf);
	void sendAll(int s, std::string buff, int *len);
	int connection(std::string &oauth, std::string &userName, std::string &botName, std::string &service);

	~IRC();
};

