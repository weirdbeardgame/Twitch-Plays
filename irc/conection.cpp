#include "conection.h"

conection::conection()
{

}

int conection::receiveAll(int s, char * recievebuf)
{
	int n = 0;
	int total = 0;
	int left = 512;
	int len = 0;

	while (total < 512)
	{
		n = recv(s, recievebuf, left, 0);
		if (n <= 0)
		{
			std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		total += n;
		left -= n;
		total++;

		if (n > 0)
		{
			for (int x = 0; x < n; x++)
			{
				std::cout << recievebuf[x];
			}

			if (findObject("PING", recievebuf))
			{
				len = strlen(pong);
				std::cout << "Pong" << std::endl;
				sendAll(s, pong, &len);
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
	}

	//Reset the Loop above.

	if (total == 512)
	{
		total = 0;
	}

	return (n <= 0) ? -1 : 0;
}

void conection::sendAll(int s, std::string buf, int *len)
{
	int left = *len;
	int tot = 0;
	std::string sendbuf;

	while (tot < *len)
	{
		status = send(s, buf.c_str() + tot, left, 0);

		if (status == -1)
		{
			std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		tot += status;
		left -= status;
	}

	*len = tot;
}

bool conection::findObject(char *ob, char recieve[])
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


int conection::initalize(SOCKET &connectSocket)
{
	std::cout << "CONNECTING TO: " << service << std::endl;

	std::cerr << "Hostname: " << hostName << " port: " << port << std::endl;


	setState(state::CONNECTING);


	while (st == state::CONNECTING)
	{
		// Initialize Winsock	
		status = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (status != 0)
		{
			std::cerr << "WSAStartup failed with error: " << status << std::endl;
			setState(state::CONNECTIONERROR);
		}

		//To clear the struct of junk data.
		memset(&server, 0, sizeof(server));

		//The basic initalizing setting for winsock.
		server.ai_family = AF_UNSPEC;
		server.ai_socktype = SOCK_STREAM;
		server.ai_protocol = IPPROTO_TCP;

		status = getaddrinfo(hostName.c_str(), port, &server, &result);

		for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
			// Create a SOCKET for connecting to server
			connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

			if (connectSocket == INVALID_SOCKET)
			{
				std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
				WSACleanup();
				setState(state::CONNECTIONERROR);
			}

			// Connect to ip address
			status = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

			if (status == SOCKET_ERROR)
			{
				closesocket(connectSocket);
				connectSocket = INVALID_SOCKET;
				std::cerr << "Invalid address" << std::endl;
				setState(state::CONNECTIONERROR);
			}
		}

		freeaddrinfo(result);

		if (connectSocket == INVALID_SOCKET)
		{
			std::cerr << "Unable to Connect" << "Error: " << WSAGetLastError() << std::endl;
			system("PAUSE");
			WSACleanup();
			setState(state::CONNECTIONERROR);
		}

		if (st == state::CONNECTIONERROR)
		{
			std::cerr << "Connection Failed" << std::endl;
			system("PAUSE");
			exit(-1);
		}

		setState(state::SENDING);
	}
	return 0;
}


conection::~conection()
{
}
