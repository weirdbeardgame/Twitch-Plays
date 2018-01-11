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
	}
}

twitch::~twitch()
{

}
