#include <iostream>
#include "Settings.h"
#include "choices.h"

int main()
{
	choices Menu;
	Settings set;
	std::string oauth;
	std::string userName;

	set.initalize(oauth, userName);
	
	while (true)
	{
		Menu.menu(oauth, userName);
	}
	
	return  0;
}