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
	std::string userName;
	std::string service;
	std::string oauth;
	jsonf setting;
public:
	Settings();
	void initalize(std::string &o);
	void defaultSettings();
	void readSettings(std::string &o);
	void editSettings(std::string &o);
	void writeSettings(jsonf stream);
	void setUserName();
	void setOathToken(std::string &o);
	std::string getUserName();
	std::string getOauthToken();
	~Settings();
};

