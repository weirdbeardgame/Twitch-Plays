#include <iostream>
#include "Settings.h"
#include "choices.h"

int main()
{
	choices Menu;
	Settings set;

	set.initalize();
	
	while (true)
	{
		Menu.menu();
	}
	
	return  0;
}