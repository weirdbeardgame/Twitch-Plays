#pragma once
#include "conection.h"
#include "Settings.h"
#include "Keys.h"
#include <winsock.h>
class twitch
{
private:
	Settings set;
	conection twitchBot;
	std::string botName = "Control_Bot";
	std::string sendBuf;
	std::string userName = set.getUserName();
	SOCKET s;
	Keys key;
	char recievebuf[512];
	char * pong = "PONG tmi.twitch.tv";
	int len;
public:
	twitch();
	int receiveAll(int s, char *recieve);
	bool findObject(char *ob, char recieve[]);
	void connectTwitch(std::string &o);
	void recieving();
	~twitch();

};

