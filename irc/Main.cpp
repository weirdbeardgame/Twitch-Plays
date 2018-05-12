#include <iostream>
#include "Settings.h"
#include "choices.h"

int main()
{
	choices Menu;
	Settings set;
	std::string oauth;
	std::string userName;

	set.initalize();
	
	while (true)
	{
		Menu.menu();
	}
	
	return  0;
}