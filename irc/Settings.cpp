#include "Settings.h"

Settings::Settings()
{
}

void Settings::initalize(std::string &o)
{
	settingFile.open("settings.json");

	if (settingFile.fail())
	{
		defaultSettings();
	}

	else
	{
		setting = jsonf::parse(settingFile);
		readSettings(o);
	}
}

void Settings::defaultSettings()
{
	setting = 
	{						
    {"Service", "Twitch" },		
	{"channelName", "The name of your twitch channel to join" },
	{"Oauth", "Required to join your channel"}
	};

	writeSettings(setting);
}

void Settings::readSettings(std::string &o)
{
		service = setting["Service"].get<std::string>();
		userName = setting["channelName"].get<std::string>();
		o = setting["Oauth"].get<std::string>();
}

void Settings::editSettings(std::string &o)
{ 
	char options;

	std::cout << "current setting's are: "
		<< "Service: " << service << std::endl
		<< "Channel Name: " << userName << std::endl
		<< "Oauth Token: " << o << std::endl;

	std::cout << "Options are: " << std::endl;
	std::cout << "C: Edit Channel name" << std::endl
		<< "S: Edit service - Not Yet implemented." << std::endl
		<< "O: Edit Oauth Token" << std::endl
		<< "B: Back to first page" << std::endl;
	std::cout << ">";
	std::cin >> options;
	options = toupper(options);
		
	switch (options)
	{
	case 'C':
		std::cout << "Channel is: ";
		setUserName();
		break;

	case 'B':
		return;
		break;

	case 'O':

		setOathToken(o);
		break;


	case 'S':
		std::cout << "Not yet implemented." << std::endl;
		break;

	}
	 
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

void Settings::setUserName()
{
	std::cout << ">";
	std::cin.ignore();
	std::getline(std::cin, userName);
	setting["channelName"] = userName;
	setting["Service"] = "Twitch";
	setting["Oauth"] = oauth; 
	writeSettings(setting);
}

void Settings::setOathToken(std::string &o)
{
	std::cout << ">";
	std::cin.ignore();
	std::getline(std::cin, o);
	oauth = o;
	setting["channelName"] = userName;
	setting["Service"] = "Twitch";
	setting["Oauth"] = oauth;
	writeSettings(setting);
}

std::string Settings::getUserName()
{
	return userName;
}

std::string Settings::getOauthToken()
{
	return oauth;
}

Settings::~Settings()
{
}
