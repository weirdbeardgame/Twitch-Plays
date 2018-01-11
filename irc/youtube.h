#pragma once
#include <iostream>
#include "conection.h"
class youtube
{
private:
const std::string APPLICATION_NAME;
std::string oauth;
conection youtubeChat;

public:
	youtube();

	void connectYoutube(std::string &oauth, std::string &userName, std::string &botName, std::string &service);

	~youtube();
};

