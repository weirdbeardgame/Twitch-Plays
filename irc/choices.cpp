#include "choices.h"



choices::choices()
{

}

void choices::menu()
{
	std::cout << "Service: " << service << std::endl;
	std::cout << "Welcome Options are: " << std::endl
		<< "C: Connect and play let the bot play" << std::endl
		<< "S: Edit Settings" << std::endl
		<< "Q: Quit" << std::endl;

	std::cout << "> ";
	std::cin >> options;
	options = toupper(options);
	execute_choice();
}

void choices::execute_choice()
{
	if (options == 'C')
	{
		if (service == "Twitch")
		{
			while (true)
			{
				tw.connectTwitch();
			}
		}

		else if (service == "Youtube")
		{
			std::cout << "Not implmented" << std::endl;
		}
	}

	if (options == 'S')
	{		
		set.editSettings(o, u);
	}

	if (options == 'Q')
	{
		exit(0);
	}

}

choices::~choices()
{
}
