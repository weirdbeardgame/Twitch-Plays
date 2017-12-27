#include "Keys.h"

Keys::Keys()
{
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = 0;

}

void Keys::pushToQueue(std::string s)
{
	fout.open("Commands.txt", std::ios::app | std::ios::out);
	commands.push_back(s);
	pullFromQueue();
}
 
void Keys::pullFromQueue() 
{
	
	for (int i = 0; i < commands.size(); i++)
	{
		fout << commands[i] << std::endl;
	}

	fout.close();
	translateCommand(commands.front());
}

void Keys::translateCommand(std::string Command)
{
	if (Command == "Up" || Command == "up")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x48;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	else if (Command == "Left" || Command == "left")
	{	
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x4B;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	if (Command == "Right" || Command == "right")
	{	
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x4D;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	else if (Command == "Down" || Command == "down")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x50;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	if (Command == "Cross" || Command == "cross")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x2C;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	else if (Command == "Circle" || Command == "circle")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x2D;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	if (Command == "Square" || Command == "square")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x1E;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	else if (Command == "Triangle" || Command == "triangle")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x1F;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	if (Command == "Start" || Command == "start")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x2E;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	else if (Command == "Select" || Command == "select")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x2F;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}
}

Keys::~Keys()
{
}
