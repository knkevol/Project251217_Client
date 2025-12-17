#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <string>

#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//IP v4, Steram 타입의 소켓 만들어 주셈, TCP
	//문지기
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	//ZeroMemory(&ServerSockAddr, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //수업용
	ServerSockAddr.sin_port = htons(777); //Byte Order

	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));

	char Buffer[1024] = { 0, };

	while(true)
	{
		//네트워크에서 바로 받는다.X OS님의 수신 버퍼에서 꺼내온다.
		int RecvByte = recv(ServerSocket, Buffer, sizeof(Buffer), 0);
		std::cout << Buffer << std::endl;

		char Message[10];
		char Message2[10];
		char temp;
		std::cin >> Message;
		std::cin >> temp;
		std::cin >> Message2;

		int sum = 0;
		switch (temp)
		{
		case '+':
			sum = atoi(Message) + atoi(Message2);
			break;
		case '-':
			sum = atoi(Message) - atoi(Message2);
			break;
		case '*':
			sum = atoi(Message) * atoi(Message2);
			break;
		case '/':
			sum = atoi(Message) / atoi(Message2);
			break;

		}

		std::string sum2 = std::to_string(sum);

		//네트워크로 보낸다X. OS님의 송신 버퍼로 보낸다.
		int SentByte = send(ServerSocket, sum2.c_str(), (int)strlen(Message), 0);


		closesocket(ServerSocket);
	}
	

	WSACleanup();

	return 0;
}

