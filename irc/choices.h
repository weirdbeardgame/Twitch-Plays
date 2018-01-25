#pragma once
#include <iostream>
#include "twitch.h"
#include "youtube.h"
#include "Settings.h"
class choices
{
private:
	char options = NULL;
	std::string service = "Twitch";
	Settings set;
	twitch tw;

public:
	choices();
	void menu(std::string &o);
	void execute_choice(std::string &o);
	~choices();
};

