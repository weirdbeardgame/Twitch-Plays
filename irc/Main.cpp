#include <iostream>
#include "Settings.h"
#include "choices.h"

int main()
{
	choices Menu;
	Settings set;
	std::string oauth;


	set.initalize(oauth);
	
	while (true)
	{
		Menu.menu(oauth);
	}
	
	return  0;
}