#include "Join.h"



Join::Join()
{
	
}


int Join::receiveAll(int s, char* recieve)
{
	int n = 0;
	int left = 512;
	int len = 0;

	while (left > 0)
	{
		n = recv(s, recieve, left, 0);

		if (n == -1)
		{
			std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		else
		{
			left--;

			if (n > 0)
			{
				for (int x = 0; x < n; x++)
				{
					std::cout << recieve[x];
				}
			}

			//Reset the Loop above.
			if (left == 0)
			{
				left = 512;
			}
		}
	}
	return (n <= 0) ? -1 : 0;

}

void Join::sendAll(int s, std::string buf, int *len)
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


void Join::channel()
{
// Initialize Winsock	
	status = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (status != 0)
	{
		std::cerr << "WSAStartup failed with error: " << status << std::endl;
	}

	std::cerr << "WSA startup happened" << std::endl;

	//To clear the struct of junk data.
	memset(&server, 0, sizeof(server));

	std::cerr << "Memory cleared" << std::endl;

	//The basic initalizing setting for winsock.
	server.ai_family = AF_UNSPEC;
	server.ai_socktype = SOCK_STREAM;
	server.ai_protocol = IPPROTO_TCP;

	status = getaddrinfo("https://api.twitch.tv/kraken/oauth2/authorize", "80", &server, &result);

	std::cerr << "Hostname set" << std::endl;

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		// Create a SOCKET for connecting to server
		connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		std::cerr << "Socket created" << std::endl;

		if (connectSocket == INVALID_SOCKET)
		{
			std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
			WSACleanup();
		}

		// Connect to ip address
		status = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

		if (status == SOCKET_ERROR)
		{
			closesocket(connectSocket);
			connectSocket = INVALID_SOCKET;
			std::cerr << "Invalid address" << std::endl;
		}
	}

	std::cerr << "A socket is you" << std::endl;

	freeaddrinfo(result);

	if (connectSocket == INVALID_SOCKET)
	{
		std::cerr << "Unable to Connect" << "Error: " << WSAGetLastError() << std::endl;
		system("PAUSE");
		WSACleanup();
	}

	if (st == state::CONNECTIONERROR)
	{
		std::cerr << "Connection Failed" << std::endl;
		system("PAUSE");
		exit(-1);
	}

	setState(state::SENDING);

	while (st == state::SENDING)
	{
		sendBuf = "GET https://api.twitch.tv/kraken/oauth2/authorize?response_type=token&client_id=ko5qwxt9xu6acgu2gil3rrw9n243pz&redirect_uri=http://localhost&scope=channel_feed_read HTTP/1.1\r\n";
		len = sendBuf.length();
		sendAll(connectSocket, sendBuf, &len);
	}

}



Join::~Join()
{
}
