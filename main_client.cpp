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

	

	int FileSize = 0;

	int RecvBytes = recv(ServerSocket, (char*)&FileSize, sizeof(FileSize), MSG_WAITALL);
	FileSize = ntohl(FileSize); //순서뒤집어서 사용
	if (RecvBytes <= 0)
	{
		//break;
	}

	FILE* OutputFile = fopen("tree.jpg", "wb");


	char* Buffer = new char[FileSize];
	RecvBytes = recv(ServerSocket, Buffer, FileSize, MSG_WAITALL);
	if (!RecvBytes)
	{
		//break;
	}
	int WriteSize = fwrite(Buffer, sizeof(char), RecvBytes, OutputFile);

	

	fclose(OutputFile);

	closesocket(ServerSocket);


	WSACleanup();

	return 0;
}