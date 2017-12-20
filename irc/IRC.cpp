#include "IRC.h"

IRC::IRC()
{
}

int IRC::receiveAll(int s, char * recvbuf)
{
	int n = 0;		
	int total = 0;
	int left = 512;
	int len = 0;

	while (total < 512)
	{
		n = recv(connectSocket, recvbuf, left, 0);
		if (n <= 0)
		{
			std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		total += n;
		left -= n;

			if ((strstr(recvbuf, "PING")) != NULL)
			{
				len = strlen(pong);
				sendAll(connectSocket, pong, &len);
				std::cout << "Pong" << std::endl;
			}	

			total++;

			if (n > 0)
			{
				for (int x = 0; x < n; x++)
				{
					std::cout << recvbuf[x];
				}

			/**********************************************
			* This will be replaced with a std vector soon.
			***********************************************/
			if ((strstr(recvbuf, "Up")) != NULL || (strstr(recvbuf, "up")) != NULL)				
			{
				key.pushToQueue("Up");
			}

			else if ((strstr(recvbuf, "Down")) != NULL || (strstr(recvbuf, "down")) != NULL)
			{
				key.pushToQueue("Down");
			}

			if ((strstr(recvbuf, "Left")) != NULL || (strstr(recvbuf, "left")) != NULL)
			{
				key.pushToQueue("Left");
			}

			else if ((strstr(recvbuf, "Right")) != NULL || (strstr(recvbuf, "right")) != NULL)
			{
				key.pushToQueue("Right");
			}

			if ((strstr(recvbuf, "Cross")) != NULL || (strstr(recvbuf, "cross")) != NULL)
			{
				key.pushToQueue("Cross");
			}

			else if ((strstr(recvbuf, "Circle")) != NULL || (strstr(recvbuf, "circle")) != NULL)
			{
				key.pushToQueue("Circle");
			}

			if ((strstr(recvbuf, "Square")) != NULL || (strstr(recvbuf, "square")) != NULL)
			{
				key.pushToQueue("Square");
			}

			else if ((strstr(recvbuf, "Triangle")) != NULL || (strstr(recvbuf, "triangle")) != NULL)
			{
				key.pushToQueue("Triangle");
			}

			if ((strstr(recvbuf, "Square")) != NULL || (strstr(recvbuf, "square")) != NULL)
			{
				key.pushToQueue("Square");
			}

		    else if ((strstr(recvbuf, "Start")) != NULL || (strstr(recvbuf, "start")) != NULL)
			{
				key.pushToQueue("Start");
			}

			if ((strstr(recvbuf, "Select")) != NULL || (strstr(recvbuf, "select")) != NULL)
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

void IRC::sendAll(int s, std::string buf, int *len)
{
	int left = *len;
	int tot = 0;
	while (tot < *len)
	{
		iResult = send(s, buf.c_str() + tot, left, 0);

		if (iResult == -1)
		{
			std::cout << "Send failed with error: " <<  WSAGetLastError() << std::endl;
			break;
		}

		tot += iResult;
		left -= iResult;
	}

	*len = tot;
}

int IRC::connection(std::string &oauth, std::string &userName, std::string &botName, std::string &service)
{
	struct addrinfo server, *result, *ptr; /****************************************************
										   * Server is used for winsock settings
										   * result is obvious, ptr is the resolved ip address
										   ****************************************************/

	std::cout << "WELCOME TO: " << service << std::endl;

	// Initialize Winsock	
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);	

	if (iResult != 0) 
	{		
		std::cout << "WSAStartup failed with error: " << iResult << std::endl;
	}

	//To clear the struct of junk data.
	memset(&server, 0, sizeof(server));
	 
	//The basic initalizing setting for winsock.
	server.ai_family = AF_UNSPEC;
	server.ai_socktype = SOCK_STREAM;
	server.ai_protocol = IPPROTO_TCP;
	
	iResult = getaddrinfo("irc.twitch.tv", DEFAULT_PORT, &server, &result); // - The HostName to be resolved.

	// connect to resolved ip address
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
		iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	
		if (iResult == SOCKET_ERROR) 
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
		exit (-1);
	}

/*****************************************
* Below is the list of sent buffers for
* loging into whatever service you may.
******************************************/
	sendBuf = "PASS " + oauth + "\r\n";
	
	len = sendBuf.length();
	sendAll(connectSocket, sendBuf, &len);
			
	if (iResult == SOCKET_ERROR) 
	{	
		std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
		closesocket(connectSocket);	
		WSACleanup();	
	}
	
	sendBuf = "NICK " + botName + "\r\n";
	
	len = sendBuf.length();
	sendAll(connectSocket, sendBuf, &len);

	if (iResult == SOCKET_ERROR) 
	{			
		std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;			
		closesocket(connectSocket);	
		WSACleanup();	
	}

	sendBuf = "JOIN #" + userName + "\r\n";		
	
	len = sendBuf.length();

	sendAll(connectSocket, sendBuf, &len);

	if (iResult == SOCKET_ERROR) 	
	{	
		std::cerr << "send failed with error: " <<  WSAGetLastError() << std::endl;			
		closesocket(connectSocket);			
		WSACleanup();		
	}
		
	sendBuf = "CAP REQ :twitch.tv/membership\r\n";		
	len = sendBuf.length();	
	sendAll(connectSocket, sendBuf, &len);	
	
	if (iResult == SOCKET_ERROR) 		
	{			
		std::cerr << "send failed with error: " <<  WSAGetLastError() << std::endl;			
		closesocket(connectSocket);			
		WSACleanup();		
	}
		
	sendBuf = "CAP REQ :twitch.tv/commands\r\n";		
	len = sendBuf.length();		
	sendAll(connectSocket, sendBuf, &len);		
	
	if (iResult == SOCKET_ERROR) 		
	{		
	std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;			
		closesocket(connectSocket);		
		WSACleanup();		
	}
			
	while (true)		
	{		
		iResult = receiveAll(connectSocket, recievebuf);		
	}
		
	// cleanup		
	closesocket(connectSocket);		
	WSACleanup();
			
	return 0;
}

IRC::~IRC()
{
}
