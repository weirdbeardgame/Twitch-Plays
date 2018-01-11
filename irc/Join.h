#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class Join
{
enum class state { CONNECTING, SENDING, CONNECTED, CONNECTIONERROR };

private:
	struct addrinfo server, *result, *ptr;
	WSADATA wsaData;
	SOCKET connectSocket;
	int len = 0;
	int status = 0;	
	std::string hostName;
	std::string service;	
	std::string redirect = "https://api.twitch.tv/kraken/oauth2/authorize?response_type=token&client_id=ko5qwxt9xu6acgu2gil3rrw9n243pz&redirect_uri=http://localhost&scope=channel_feed_read";
	std::string sendBuf;
	state st;
	char *port;
	char recieveBuf[512];

public:
	Join();
	void channel();
	int receiveAll(int s, char *recieve);
	void sendAll(int s, std::string buff, int *len);
	state setState(state s) { return st = s; }
	state getState() { return st; }
	~Join();
};

