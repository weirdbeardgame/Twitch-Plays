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
	std::string oauth = set.getOauthToken();
	SOCKET s;
	Keys key;

	char * pong = "PONG tmi.twitch.tv";
	int len;
public:
	twitch();
	void connectTwitch();
	~twitch();

};

