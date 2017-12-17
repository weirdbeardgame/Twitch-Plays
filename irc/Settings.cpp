#include "Settings.h"

Settings::Settings()
{
}

void Settings::initalize(std::string &oauth, std::string &userName, std::string &botName, std::string &service)
{
	settingFile.open("settings.json");

	if (settingFile.fail())
	{
		defaultSettings(oauth, userName, botName, service);
	}

	else
	{
		setting = jsonf::parse(settingFile);
		readSettings(oauth, userName, botName, service);
	}
}

void Settings::defaultSettings(std::string &oauth, std::string &userName, std::string &botName, std::string &service)
{
	setting = 
	{						
    {"Service", "Twitch" },		
	{"botName", "The name of the bot you want to connect"},
	{"channelName", "The name of your twitch channel to join" },	    
	{"Password", "Your Oauth Here"}	    
	};

	writeSettings(setting);
}

void Settings::readSettings(std::string &oauth, std::string &userName, std::string &botName, std::string &service)
{
		service = setting["Service"].get<std::string>();
		oauth = setting["Password"].get<std::string>();
		userName = setting["channelName"].get<std::string>();
		botName = setting["botName"].get<std::string>();
}

void Settings::editSettings(std::string &oauth, std::string &userName, std::string &botName, std::string &service)
{ 
	char options;

	std::cout << "current setting's are: " 		
		<< "Service: " << service << std::endl
		<< "Channel Name: " << userName << std::endl
		<< "Oauth Token: " << oauth << std::endl
		<< "Bot Name: " << botName << std::endl;

	std::cout << "Options are: " << std::endl;
	std::cout << "C: Edit Channel name" << std::endl	
		      << "B: Edit the name of the Bot" << std::endl 
		      << "S: Edit service - Not Yet implemented." << std::endl
		      << "O: Edit Oauth Token" << std::endl;
	std::cout << ">";
	std::cin >> options;
	options = toupper(options);
	
	std::cin.ignore();
	
	switch (options)
	{
	case 'C':
		std::cout << "Channel is: ";
		std::getline(std::cin , userName);
		setting["channelName"] = userName;
		break;

	case 'B':
		std::cout << "Bot's name is: ";
		std::getline(std::cin, botName);
		setting["botName"] = botName;

	case 'S':
		std::cout << "Not yet implemented." << std::endl;
		setting["Service"] = "Twitch";
		break;

	case 'O':
		std::cout << "Oauth Token: ";
		std::getline(std::cin, oauth);	
		setting["Password"] = oauth;
		break;
	}
	 
	writeSettings(setting);
}

void Settings::writeSettings(jsonf stream)
{
	outputFile.open("settings.json", std::ios::out);

	if (outputFile.fail())
	{
		std::cerr << "File not written" << std::endl;
		system("PAUSE");
		exit(-1);
	}

	outputFile << std::setw(4) << stream << std::endl;
}

Settings::~Settings()
{
}
