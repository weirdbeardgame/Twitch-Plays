#include "IRC.h"

IRC::IRC()
{
}

int IRC::receiveAll(int s, std::vector <char> recvbuf)
{

	int left = 512;
	int n = -1;
	int len = 0;

	while (total < 512)
	{
		n = recv(connectSocket, &recvbuf[0], left, 0);
		if (n <= 0)
		{
			std::cout << "recv failed with error: " <<  WSAGetLastError() << std::endl;
			break;
		}

		total += n;
		left -= n;
		
		/**********************************************************************
		* Below is a list of the commands this will be dynamic in the future
		* Each are manually pushed into the queue and looped through.
		**********************************************************************/
		if (n > 0)
		{
			for (int x = 0; x < n; x++)
			{
				std::cout << recvbuf[x];
			}

			if ((strstr(recvbuf.data(), "PING")) != NULL)
			{
				len = strlen(pong);
				sendAll(connectSocket, pong, &len);
				std::cout << "Pong" << std::endl;
			}	


			/**********************************************
			* This will be replaced with a std vector soon.
			***********************************************/
			if ((strstr(recvbuf.data(), "Up")) != NULL || (strstr(recvbuf.data(), "up")) != NULL)				
			{
				key.pushToQueue("Up");
			}

			else if ((strstr(recvbuf.data(), "Down")) != NULL || (strstr(recvbuf.data(), "down")) != NULL)
			{
				key.pushToQueue("Down");
			}

			if ((strstr(recvbuf.data(), "Left")) != NULL || (strstr(recvbuf.data(), "left")) != NULL)
			{
				key.pushToQueue("Left");
			}

			else if ((strstr(recvbuf.data(), "Right")) != NULL || (strstr(recvbuf.data(), "right")) != NULL)
			{
				key.pushToQueue("Right");
			}

			if ((strstr(recvbuf.data(), "Cross")) != NULL || (strstr(recvbuf.data(), "cross")) != NULL)
			{
				key.pushToQueue("Cross");
			}

			else if ((strstr(recvbuf.data(), "Circle")) != NULL || (strstr(recvbuf.data(), "circle")) != NULL)
			{
				key.pushToQueue("Circle");
			}

			if ((strstr(recvbuf.data(), "Square")) != NULL || (strstr(recvbuf.data(), "square")) != NULL)
			{
				key.pushToQueue("Square");
			}

			else if ((strstr(recvbuf.data(), "Triangle")) != NULL || (strstr(recvbuf.data(), "triangle")) != NULL)
			{
				key.pushToQueue("Triangle");
			}

			if ((strstr(recvbuf.data(), "Square")) != NULL || (strstr(recvbuf.data(), "square")) != NULL)
			{
				key.pushToQueue("Square");
			}

		    else if ((strstr(recvbuf.data(), "Start")) != NULL || (strstr(recvbuf.data(), "start")) != NULL)
			{
				key.pushToQueue("Start");
			}

			if ((strstr(recvbuf.data(), "Select")) != NULL || (strstr(recvbuf.data(), "select")) != NULL)
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
		printf("WSAStartup failed with error: %d\n", iResult);
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
		iResult = receiveAll(connectSocket, recvbuf);		
	}
		
	// cleanup		
	closesocket(connectSocket);		
	WSACleanup();
			
	return 0;
}

IRC::~IRC()
{
}
