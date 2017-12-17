#include "choices.h"



choices::choices()
{

}

void choices::menu(std::string &oauth, std::string &userName, std::string &botName, std::string &service)
{
	std::cout << "Welcome to Twitch Plays" << std::endl
		<< "Options are: " << std::endl
		<< "C: Connect and play let the bot play" << std::endl
		<< "S: Edit Settings" << std::endl
		<< "Q: Quit" << std::endl;

	std::cout << "> ";
	std::cin >> options;
	options = toupper(options);
	execute_choice(oauth, userName, botName, service);
}

void choices::execute_choice(std::string &oauth, std::string &userName, std::string &botName, std::string &service)
{

	switch (options)
	{	
	case 'C':
		connect.connection(oauth, userName, botName, service);
		break;

	case 'S':
		set.editSettings(oauth, userName, botName,  service);
		break;

	case 'Q':
		exit(0);
		break;
	}

}

choices::~choices()
{
}
