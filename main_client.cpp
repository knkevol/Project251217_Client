#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32")

using namespace std;

int main()
{
	WSAData wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN ServerSockAddr; //ListenSocket 정보
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSockAddr.sin_port = htons(33333);

	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));

	char Buffer[1000000] = { 0, };

	int RecvBytes = recv(ServerSocket, Buffer, sizeof(Buffer), 0);
	if (RecvBytes <= 0)
	{
		//break;
	}

	//파일 쓰기
	FILE* OutputFile = fopen("tree.jpg", "wb");
	int WriteSize = fwrite(Buffer, sizeof(char), RecvBytes, OutputFile);

	fclose(OutputFile);

	closesocket(ServerSocket);


	WSACleanup();

	return 0;
}