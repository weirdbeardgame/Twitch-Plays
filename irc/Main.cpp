#include <iostream>
#include "Settings.h"
#include "choices.h"
using namespace std;

int main()
{
    std:string userName;	
	std::string service;
	std::string oauth;
	std::string botName;

	choices Menu;
	Settings set;

	set.initalize(oauth, userName, botName, service);
	
	while (true)
	{
		Menu.menu(oauth, userName, botName, service);
	}
	
	return  0;
}