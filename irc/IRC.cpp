#include "IRC.h"

IRC::IRC()
{
}

int IRC::receiveAll(int s)
{
	int n = 0;
	int left = 512;
	int len = 0;

	std::vector <char> recieve(512);

	while (left > 0)
	{
		n = recv(s, recieve.data(), recieve.size(), 0);

		if (n == -1)
		{
			std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		else
		{
			recieve.resize(n);

			if(std::find(recieve.begin(), recieve.end(), 'PING') != recieve.end())
			{
				len = strlen(pong);
				sendAll(s, pong, &len);
				std::cout << "Pong" << std::endl;
			}

			if (n > 0)
			{
				for (int x = 0; x < n; x++)
				{
					std::cout << recieve[x];
				}

				/**********************************************
				* This will be replaced with a std vector soon.
				***********************************************/
				if (std::find(recieve.begin(), recieve.end(), 'Up') != recieve.end())
				{
					key.pushToQueue("Up");
					std::cerr << "It's all upity in here" << std::endl;
				}

				else if ((strstr(recieve.data(), "Down")) != NULL || (strstr(recieve.data(), "down")) != NULL)
				{
					key.pushToQueue("Down");
				}

				if ((strstr(recieve.data(), "Left")) != NULL || (strstr(recieve.data(), "left")) != NULL)
				{
					key.pushToQueue("Left");
				}

				else if ((strstr(recieve.data(), "Right")) != NULL || (strstr(recieve.data(), "right")) != NULL)
				{
					key.pushToQueue("Right");
				}

				if ((strstr(recieve.data(), "Cross")) != NULL || (strstr(recieve.data(), "cross")) != NULL)
				{
					key.pushToQueue("Cross");
				}

				else if ((strstr(recieve.data(), "Circle")) != NULL || (strstr(recieve.data(), "circle")) != NULL)
				{
					key.pushToQueue("Circle");
				}

				if ((strstr(recieve.data(), "Square")) != NULL || (strstr(recieve.data(), "square")) != NULL)
				{
					key.pushToQueue("Square");
				}

				else if ((strstr(recieve.data(), "Triangle")) != NULL || (strstr(recieve.data(), "triangle")) != NULL)
				{
					key.pushToQueue("Triangle");
				}

				if ((strstr(recieve.data(), "Square")) != NULL || (strstr(recieve.data(), "square")) != NULL)
				{
					key.pushToQueue("Square");
				}

				else if ((strstr(recieve.data(), "Start")) != NULL || (strstr(recieve.data(), "start")) != NULL)
				{
					key.pushToQueue("Start");
				}

				if ((strstr(recieve.data(), "Select")) != NULL || (strstr(recieve.data(), "select")) != NULL)
				{
					key.pushToQueue("Select");
				}
			}
		}

		//Reset the Loop above.

		if (left == 0)
		{
			left = 512;
		}

		return (n <= 0) ? -1 : 0;
	}
}

void IRC::sendAll(int s, std::string buf, int *len)
{
	int left = *len;
	int tot = 0;
	while (tot < *len)
	{
		status = send(s, buf.c_str() + tot, left, 0);

		if (status == -1)
		{
			std::cout << "Send failed with error: " <<  WSAGetLastError() << std::endl;
			break;
		}

		tot += status;
		left -= status;
	}

	*len = tot;
}

int IRC::connection(std::string &oauth, std::string &userName, std::string &botName, std::string &service)
{
	
	setState(state::CONNECTING);
	
	
	struct addrinfo server, *result, *ptr; /****************************************************
										   * Server is used for winsock settings
										   * result is obvious, ptr is the resolved ip address
										   ****************************************************/
	while (st == state::CONNECTING)
	{

		std::cout << "CONNECTING TO: " << service << std::endl;

		// Initialize Winsock	
		status = WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (status != 0)
		{
			std::cout << "WSAStartup failed with error: " << status << std::endl;
		}

		//To clear the struct of junk data.
		memset(&server, 0, sizeof(server));

		//The basic initalizing setting for winsock.
		server.ai_family = AF_UNSPEC;
		server.ai_socktype = SOCK_STREAM;
		server.ai_protocol = IPPROTO_TCP;

		status = getaddrinfo("irc.twitch.tv", DEFAULT_PORT, &server, &result); // - The HostName to be resolved.

		// connect to resolved ip address via pointer
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
			// Create a SOCKET for connecting to server
			connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

			if (connectSocket == INVALID_SOCKET)
			{
				std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
				WSACleanup();
				exit(-1);
			}

			// Connect to ip address
			status = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

			if (status == SOCKET_ERROR)
			{
				closesocket(connectSocket);
				connectSocket = INVALID_SOCKET;
				std::cerr << "Invalid address" << std::endl;
				exit(-1);
			}
		}

		freeaddrinfo(result);

		if (connectSocket == INVALID_SOCKET)
		{
			std::cerr << "Unable to Connect" << "Error: " << WSAGetLastError() << std::endl;
			system("PAUSE");
			WSACleanup();
			exit(-1);
		}

		/*****************************************
		* Below is the list of sent buffers for
		* loging into whatever service you may.
		******************************************/
		sendBuf = "PASS " + oauth + "\r\n";

		len = sendBuf.length();
		sendAll(connectSocket, sendBuf, &len);

		if (status == SOCKET_ERROR)
		{
			std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(connectSocket);
			WSACleanup();
		}

		sendBuf = "NICK " + botName + "\r\n";

		len = sendBuf.length();
		sendAll(connectSocket, sendBuf, &len);

		if (status == SOCKET_ERROR)
		{
			std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(connectSocket);
			WSACleanup();
		}

		sendBuf = "JOIN #" + userName + "\r\n";

		len = sendBuf.length();

		sendAll(connectSocket, sendBuf, &len);

		if (status == SOCKET_ERROR)
		{
			std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(connectSocket);
			WSACleanup();
		}

		sendBuf = "CAP REQ :twitch.tv/membership\r\n";
		len = sendBuf.length();
		sendAll(connectSocket, sendBuf, &len);

		if (status == SOCKET_ERROR)
		{
			std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(connectSocket);
			WSACleanup();
		}

		sendBuf = "CAP REQ :twitch.tv/commands\r\n";
		len = sendBuf.length();
		sendAll(connectSocket, sendBuf, &len);

		if (status == SOCKET_ERROR)
		{
			std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(connectSocket);
			WSACleanup();		
		}
		
		setState(state::CONNECTED);
}
		

std::cout << "CONNECTED TO: " << service << std::endl;
	
while (st == state::CONNECTED)			
{		
	status = receiveAll(connectSocket);			
}
			
// cleanup			
closesocket(connectSocket);			
WSACleanup();
				
return 0;
}

IRC::~IRC()
{
}
