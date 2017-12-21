#include "Keys.h"

Keys::Keys()
{
}

void Keys::pushToQueue(std::string s)
{
	fout.open(filePath, std::ios::app | std::ios::out);
	commands.push_back(s);
	pullFromQueue();
}

void Keys::pullFromQueue() 
{
	translateCommand(commands.front());
	for (int i = 0; i < commands.size(); i++)
	{
		fout << commands[i] << std::endl;
	}

	fout.close();
}

void Keys::translateCommand(std::string Command)
{
	if (Command == "Up" || Command == "up")
	{
		keybd_event(VK_UP, 0x26, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(500);
		keybd_event( VK_UP, 0x26, KEYEVENTF_KEYUP, 0);
		Command = " ";
		commands.erase(commands.begin());
	}

	else if (Command == "Left" || Command == "left")
	{	
		keybd_event(VK_LEFT, 0x25, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(500);
		keybd_event(VK_LEFT, 0x25, KEYEVENTF_KEYUP, 0);
		Command = " ";
		commands.erase(commands.begin());
	}

	if (Command == "Right" || Command == "right")
	{	
		keybd_event(VK_RIGHT, 0x27, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(500);
		keybd_event(VK_RIGHT, 0x27, KEYEVENTF_KEYUP, 0);
		Command = " ";
		commands.erase(commands.begin());
	}

	else if (Command == "Down" || Command == "down")
	{
		keybd_event(VK_DOWN, 0x28, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(500);
		keybd_event(VK_DOWN, 0x28, KEYEVENTF_KEYUP, 0);
		Command = " ";
		commands.erase(commands.begin());
	}

	if (Command == "Cross" || Command == "cross")
	{
		keybd_event('Z', 0x5A, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(500);
		keybd_event('Z', 0x5A, KEYEVENTF_KEYUP, 0);
		Command = " ";
		commands.erase(commands.begin());
	}

	else if (Command == "Circle" || Command == "circle")
	{
		keybd_event('X', 0x58, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(500);
		keybd_event('X', 0x58, KEYEVENTF_KEYUP, 0);
		Command = " ";
		commands.erase(commands.begin());
	}

	if (Command == "Square" || Command == "square")
	{
		keybd_event('A', 0x41, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(500);
		keybd_event('A', 0x41, KEYEVENTF_KEYUP, 0);
		Command = " ";
		commands.erase(commands.begin());
	}

	else if (Command == "Triangle" || Command == "triangle")
	{
		keybd_event('S', 0x53, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(500);
		keybd_event('S', 0x53, KEYEVENTF_KEYUP, 0);
		Command = " ";
		commands.erase(commands.begin());
	}

	if (Command == "Start" || Command == "start")
	{
		keybd_event('C', 0x43, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(500);
		keybd_event('C', 0x43, KEYEVENTF_KEYUP, 0);
		Command = " ";
		commands.erase(commands.begin());
	}

	else if (Command == "Select" || Command == "select")
	{
		keybd_event('V', 0x56, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(500);
		keybd_event('V', 0x56, KEYEVENTF_KEYUP, 0);
		Command = " ";
		commands.erase(commands.begin());
	}
}

Keys::~Keys()
{
}
