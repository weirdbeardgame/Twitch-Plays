#include "choices.h"



choices::choices()
{

}

void choices::menu(std::string &o)
{
	std::cout << "Service: " << service << std::endl;
	std::cout << "Welcome Options are: " << std::endl
		<< "C: Connect and play let the bot play" << std::endl
		<< "S: Edit Settings" << std::endl
		<< "Q: Quit" << std::endl;

	std::cout << "> ";
	std::cin >> options;
	options = toupper(options);
	execute_choice(o);
}

void choices::execute_choice(std::string &o)
{
	if (options == 'C')
	{
		if (service == "Twitch")
		{
			tw.connectTwitch(o);
		}

		else if (service == "Youtube")
		{
			std::cout << "Not implmented" << std::endl;
		}
	}

	if (options == 'S')
	{		
		set.editSettings(o);
	}

	if (options == 'Q')
	{
		exit(0);
	}

}

choices::~choices()
{
}
