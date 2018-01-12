#include "twitch.h"


twitch::twitch()
{		
	twitchBot.setHostName("irc.twitch.tv");
	twitchBot.setPort("6667");
}

void twitch::connectTwitch()
{
	char recieve[512];		
	twitchBot.initalize(s);

	while (twitchBot.getState() == state::SENDING)
	{
		/*****************************************
		* Below is the list of sent buffers for
		* loging into whatever service you may.
		******************************************/
		sendBuf = "PASS " + oauth + "\r\n";

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
				
		twitchBot.setState(state::CONNECTED);

	}

	while (twitchBot.getState() == state::CONNECTED)
	{
		twitchBot.receiveAll(s, recieve);
	
		if (twitchBot.findObject("PING", recieve))
		{
			len = strlen(pong);
			std::cout << "Pong" << std::endl;
			twitchBot.sendAll(s, pong, &len);
		}

		else if (twitchBot.findObject("Up", recieve))
		{
			key.pushToQueue("Up");

		}

		if (twitchBot.findObject("Left", recieve))
		{
			key.pushToQueue("Left");
		}

		else if (twitchBot.findObject("Right", recieve))
		{
			key.pushToQueue("Right");
		}

		if (twitchBot.findObject("Down", recieve))
		{
			key.pushToQueue("Down");
		}

		else if (twitchBot.findObject("Cross", recieve))
		{
			key.pushToQueue("Cross");
		}

		if (twitchBot.findObject("Circle", recieve))
		{
			key.pushToQueue("Circle");
		}

		else if (twitchBot.findObject("Square", recieve))
		{
			key.pushToQueue("Square");
		}

		if (twitchBot.findObject("Triangle", recieve))
		{
			key.pushToQueue("Triangle");
		}

		else if (twitchBot.findObject("Start", recieve))
		{
			key.pushToQueue("Start");
		}

		if (twitchBot.findObject("Select", recieve))
		{
			key.pushToQueue("Select");
		}

	}
}

twitch::~twitch()
{

}
