#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include <queue>
#include "Common.h"

struct keyboard
{
	int Arrow_Up = 22472;
	int Arrow_Right = 22477;
	int Arrow_Down = 22480;
	int Arrow_Left = 22475;
	int z = 0x2C;
	int x = 0x2D;
	int a = 0x1E;
	int s = 0x1F;
};

class Keys
{
private:
	std::deque<std::string>commands;
	std::vector<std::string>fileQueue;
	int keyResult = 0;
	int buffSize = 0; 
	INPUT ip;
	keyboard keylist;
	std::string filePath = "Commands.txt";
	std::ofstream fout;

public:
	Keys();	
	void pushButton(int b);
	void pushToQueue(std::string s);
	void translate(std::string s);
	void pullFromQueue();
	~Keys();
};

