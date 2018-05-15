#pragma once
#include "conection.h"
#include "Common.h"
#include "Keys.h"
#include <winsock.h>
class twitch
{
private:
	conection twitchBot;
	std::string botName = "Control_Bot";
	std::string sendBuf;
	SOCKET s;
	Keys key;
	char recievebuf[512];
	char * pong = "PONG tmi.twitch.tv";
	int len;
public:
	twitch();
	bool findObject(char *ob, char recieve[]);
	void connectTwitch();
	void recieving();
	~twitch();

};

