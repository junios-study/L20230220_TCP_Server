#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData wsaData;

	//WinSock 초기화
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result != 0)
	{
		cout << "Winsock2 Error." << endl;
		return -1;
	}

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "can't make socket." << GetLastError() << endl;
		return -1;
	}

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_port = htons(4000);
	ServerSockAddr.sin_addr.s_addr = INADDR_ANY; //아무거나

	Result = bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));
	if (Result == SOCKET_ERROR)
	{
		cout << "can't bind." << GetLastError() << endl;
		return -1;
	}

	Result = listen(ServerSocket, 0);
	if (Result == SOCKET_ERROR)
	{
		cout << "can't listen." << GetLastError() << endl;
		return -1;
	}

	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
	int ClientSockAddrLength = sizeof(ClientSockAddr);
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
	if (ClientSocket == INVALID_SOCKET)
	{
		cout << "can't accept." << GetLastError() << endl;
		return -1;
	}

	const char* Message = "Hello World";
	int SendBytes = send(ClientSocket, Message, (int)strlen(Message) + 1, 0);
	if (SendBytes == 0)
	{
		cout << "connect close." << GetLastError() << endl;
			return -1;
	}
	else if (SendBytes < 0)
	{
		cout << "error close." << GetLastError() << endl;
		return -1;
	}

	closesocket(ClientSocket);
	closesocket(ServerSocket);

	//Winsock 정리
	WSACleanup();

	cout << "Hello World" << endl;
	return 0;
}