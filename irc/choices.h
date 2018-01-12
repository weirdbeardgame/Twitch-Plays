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

public:
	choices();
	void menu();
	Settings set;
	void execute_choice();
	~choices();
};

