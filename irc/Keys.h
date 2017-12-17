#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include <queue>

class Keys
{
private:
	std::deque<std::string>commands;
	std::vector<std::string>fileQueue;
	int keyResult = 0;
	int buffSize = 0; 
	std::string filePath = "Commands.txt";
	std::ofstream fout;

public:
	Keys();	
	void translateCommand(std::string Command);
	void pushToQueue(std::string s);
	void pullFromQueue();
	~Keys();
};

