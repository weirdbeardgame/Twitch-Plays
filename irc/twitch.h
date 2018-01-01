#pragma once
#include "conection.h"
#include <winsock.h>
class twitch
{
private:
	conection twitchBot;
	std::string botName;
	std::string sendBuf;
	SOCKET s;
	
	char * pong = "PONG tmi.twitch.tv";
	int len;
public:
	twitch();
	void connectTwitch(std::string &oauth, std::string &userName, std::string &botName, std::string &service);
	~twitch();

};

