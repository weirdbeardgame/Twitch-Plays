#include "Settings.h"

Settings::Settings()
{
}

void Settings::initalize()
{
	settingFile.open("settings.json");

	if (settingFile.fail())
	{
		defaultSettings();
	}

	else
	{
		setting = jsonf::parse(settingFile);
		readSettings();
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

void Settings::readSettings()
{
		service = setting["Service"].get<std::string>();
		userName = setting["channelName"].get<std::string>();
		oauth = setting["Oauth"].get<std::string>();
}

void Settings::editSettings()
{ 
	char options;

	std::cout << "current setting's are: "
		<< "Service: " << service << std::endl
		<< "Channel Name: " << userName << std::endl;

	std::cout << "Options are: " << std::endl;
	std::cout << "C: Edit Channel name" << std::endl
		<< "S: Edit service - Not Yet implemented." << std::endl
		<< "B: Back to first page" << std::endl;
	std::cout << ">";
	std::cin >> options;
	options = toupper(options);
	
	std::cin.ignore();
	
	switch (options)
	{
	case 'C':
		std::cout << "Channel is: ";
		std::getline(std::cin , userName);		
		break;

	case 'B':
		return;
		break;

	case 'S':
		std::cout << "Not yet implemented." << std::endl;
		break;

	}
	 
	setting["channelName"] = userName;
	setting["Service"] = "Twitch";	


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

void Settings::setUserName(std::string us)
{
	setting["channelName"] = us;
	userName = us;
	setting["Service"] = "Twitch";
	setting["Oauth"] = oauth;
	 writeSettings(setting);
}

void Settings::setOathToken(std::string ot)
{
	setting["channelName"] = userName;
	setting["Service"] = "Twitch";
	setting["Oauth"] = ot;
	oauth = ot;
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
