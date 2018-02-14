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
	jsonf keys;
public:
	Settings();
	void initalize();
	void defaultSettings();
	void readSettings();
	void editSettings();
	void writeSettings(jsonf stream);
	void setUserName(const std::string &u);
	void setOathToken(const std::string &o);
	std::string getUserName() const;
	std::string getOauthToken();
	~Settings();
};

