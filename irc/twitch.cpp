#include "twitch.h"


twitch::twitch()
{		
	twitchBot.setHostName("irc.twitch.tv");
	twitchBot.setPort("6667");
}

bool twitch::findObject(char * ob, char recieve[])
{
	if (strstr(recieve, ob) != NULL)
	{
		return true;
	}

	else
	{
		return false;
	}
}

void twitch::connectTwitch(std::string &o, std::string &u)
{
	char recieve[512];		
	twitchBot.initalize(s);

	if (twitchBot.getState() == state::SENDING)
	{
		/*****************************************
		* Below is the list of sent buffers for
		* loging into whatever service you may.
		******************************************/
		sendBuf = "PASS " + o + "\r\n";

		len = sendBuf.length();
		twitchBot.sendAll(s, sendBuf, &len);

		if (twitchBot.getStatus() == SOCKET_ERROR)
		{
			std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(s);
			WSACleanup();
			twitchBot.setState(state::CONNECTIONERROR);
		}

		std::cerr << "Sent Password" << std::endl;

		sendBuf = "NICK " + botName + "\r\n";

		len = sendBuf.length();
		twitchBot.sendAll(s, sendBuf, &len);

		if (twitchBot.getStatus() == SOCKET_ERROR)
		{
			std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(s);
			WSACleanup();
			twitchBot.setState(state::CONNECTIONERROR);
		}

		std::cerr << "Nick name sent" << std::endl;

		sendBuf = "JOIN #" + u + "\r\n";
		len = sendBuf.length();
		twitchBot.sendAll(s, sendBuf, &len);
		
		if (twitchBot.getStatus() == SOCKET_ERROR)
		{
			std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(s);
			WSACleanup();
			twitchBot.setState(state::CONNECTIONERROR);
		}

		std::cerr << "Channel joined #" << u << std::endl;


		sendBuf = "CAP REQ :twitch.tv/membership\r\n";
		len = sendBuf.length();
		twitchBot.sendAll(s, sendBuf, &len);

		if (twitchBot.getStatus() == SOCKET_ERROR)
		{
			std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(s);
			WSACleanup();
			twitchBot.setState(state::CONNECTIONERROR);
		}

		sendBuf = "CAP REQ :twitch.tv/commands\r\n";
		len = sendBuf.length();
		twitchBot.sendAll(s, sendBuf, &len);

		if (twitchBot.getStatus() == SOCKET_ERROR)
		{
			std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(s);
			WSACleanup();
			twitchBot.setState(state::CONNECTIONERROR);
		}
	}

	while (true)
	{
		recieving();
	}

}

void twitch::recieving()
{
	int error = twitchBot.receiveAll(s, recievebuf);

	if (findObject("PING", recievebuf))
	{
		len = strlen(pong);
		std::cout << "Pong" << std::endl;
		twitchBot.sendAll(s, pong, &len);
	}

	else if (findObject("Up", recievebuf))
	{
		key.pushToQueue("Up");
	}

	if (findObject("Left", recievebuf))
	{
		key.pushToQueue("Left");
	}

	else if (findObject("Right", recievebuf))
	{
		key.pushToQueue("Right");
	}

	if (findObject("Down", recievebuf))
	{
		key.pushToQueue("Down");
	}

	else if (findObject("Cross", recievebuf))
	{
		key.pushToQueue("Cross");
	}

	if (findObject("Circle", recievebuf))
	{
		key.pushToQueue("Circle");
	}

	else if (findObject("Square", recievebuf))
	{
		key.pushToQueue("Square");
	}

	if (findObject("Triangle", recievebuf))
	{
		key.pushToQueue("Triangle");
	}

	else if (findObject("Start", recievebuf))
	{
		key.pushToQueue("Start");
	}

	if (findObject("Select", recievebuf))
	{
		key.pushToQueue("Select");
	}
}

twitch::~twitch()
{

}
