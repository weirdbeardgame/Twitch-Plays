#pragma once
#include <iostream>
#include "twitch.h"
#include "youtube.h"
#include "Common.h"
class choices
{
private:
	char options = NULL;
	std::string service = "Twitch";
	twitch tw;

public:
	choices();
	void menu();
	void execute_choice();
	~choices();
};

