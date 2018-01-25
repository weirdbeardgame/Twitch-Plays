#include "twitch.h"


twitch::twitch()
{		
	twitchBot.setHostName("irc.twitch.tv");
	twitchBot.setPort("6667");
}

int twitch::receiveAll(int s, char * recieve)
{
	int n = 0;
	int left = 512;
	int len = 0;

	while (left > 0)
	{
		n = recv(s, recieve, left, len);

		if (n == -1)
		{
			std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		else
		{

			if (n > 0)
			{
				for (int x = 0; x < n; x++)
				{
					std::cout << recieve[x];
				}


				if (findObject("PING", recieve))
				{
					len = strlen(pong);
					std::cout << "Pong" << std::endl;
					twitchBot.sendAll(s, pong, &len);
				}

				else if (findObject("Up", recieve))
				{
					key.pushToQueue("Up");
				}

				if (findObject("Left", recieve))
				{
					key.pushToQueue("Left");
				}

				else if (findObject("Right", recieve))
				{
					key.pushToQueue("Right");
				}

				if (findObject("Down", recieve))
				{
					key.pushToQueue("Down");
				}

				else if (findObject("Cross", recieve))
				{
					key.pushToQueue("Cross");
				}

				if (findObject("Circle", recieve))
				{
					key.pushToQueue("Circle");
				}

				else if (findObject("Square", recieve))
				{
					key.pushToQueue("Square");
				}

				if (findObject("Triangle", recieve))
				{
					key.pushToQueue("Triangle");
				}

				else if (findObject("Start", recieve))
				{
					key.pushToQueue("Start");
				}

				if (findObject("Select", recieve))
				{
					key.pushToQueue("Select");
				}
			}
			
			len++;
			left--;

			//Reset the Loop above.
			if (left == 0)
			{
				left = 512;
				len = 0;
			}

			return (n <= 0) ? -1 : 0;
		}
	}
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

void twitch::connectTwitch(std::string &o)
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
		while (true)
		{
			recieving();
		}

	}
}

void twitch::recieving()
{
	int error = twitchBot.receiveAll(s, recievebuf);
}

twitch::~twitch()
{

}
