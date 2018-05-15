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

void Keys::translate(std::string s)
{
	if (s == "Up")
	{
		pushButton(UP);
	}

	else if ( s == "Down")
	{
		 pushButton(DOWN);
	}

	if (s == "Left")
	{
		pushButton(LEFT);
	}

	else if (s == "Right")
	{
		pushButton(RIGHT);
	}
	if (s == "Cross")
	{
		pushButton(A);
	}
	else if (s == "Circle")
	{
		pushButton(B);
	}
	if (s == "Square")
	{
		pushButton(X);
	}
	else if (s == "Triangle")
	{ 
		pushButton(Y);
	}
	if (s == "Start")
	{
		pushButton(START);
	}
	else if (s == "Select")
	{
		pushButton(SELECT);
	}
}

void Keys::pullFromQueue()
{
	for (int i = 0; i < commands.size(); i++)
	{
		fout << commands[i] << std::endl;
	}

	fout.close();
	translate(commands.front());
	commands.pop_back();
}

void Keys::pushButton(int b)
{
	switch (b)
	{
	case UP:
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = keylist.Arrow_Up;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		break;

	case LEFT:
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = keylist.Arrow_Left;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		break;

	case RIGHT:
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = keylist.Arrow_Right;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		break;

	case DOWN:
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = keylist.Arrow_Down;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(500);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		break;

	case A:
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = keylist.z;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(100);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		break;

	case B:
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = keylist.x;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(100);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		break;

	case X:
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = keylist.a;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(100);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		break;

	case Y:
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = keylist.s;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(100);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		break;

	case START:
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x2E;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(100);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		break;

	case SELECT:
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = 0x2F;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(100);
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		break;
	}
}

Keys::~Keys()
{
}
