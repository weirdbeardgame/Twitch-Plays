#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using jsonf = nlohmann::json;

class Settings
{
private:
	std::ifstream settingFile;
	std::ofstream outputFile;
	jsonf setting;
public:
	Settings();
	void initalize(std::string &oauth, std::string &userName, std::string &botName, std::string &service);
	void defaultSettings(std::string &oauth, std::string &userName, std::string &botName, std::string &service);
	void readSettings(std::string &oauth, std::string &userName, std::string &botName, std::string &service);
	void editSettings(std::string &oauth, std::string &userName, std::string &botName, std::string &service);
	void writeSettings(jsonf stream);
	~Settings();
};

