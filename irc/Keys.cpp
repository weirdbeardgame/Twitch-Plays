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

void Keys::sendKey(keyboard k)
{
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	ip.ki.wScan = keylist.Arrow_Up;
}

void Keys::translateCommand(std::string Command)
{
	if (Command == "Up" || Command == "up")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 22472;
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
		ip.ki.wScan = 22475;
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
		ip.ki.wScan = 22477;
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
		ip.ki.wScan = 0;
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
		ip.ki.wScan = keylist.z;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(100);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	else if (Command == "Circle" || Command == "circle")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = keylist.x;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(100);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	if (Command == "Square" || Command == "square")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = keylist.a;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(100);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}

	else if (Command == "Triangle" || Command == "triangle")
	{
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = keylist.s;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(100);
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
		Sleep(100);
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
		Sleep(100);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Command = " ";
		commands.pop_front();
	}
}

Keys::~Keys()
{
}
