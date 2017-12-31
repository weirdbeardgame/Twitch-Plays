#pragma once
#include <iostream>
#include "twitch.h"
#include "youtube.h"
#include "Settings.h"
class choices
{
private:
	char options = NULL;

public:
	choices();
	void menu(std::string &oauth, std::string &userName, std::string &botName, std::string &service);
	Settings set;
	void execute_choice(std::string &oauth, std::string &userName, std::string &botName, std::string &service);
	~choices();
};

