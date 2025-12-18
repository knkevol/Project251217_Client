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

    //갯수
    int FileCount = 0;
    int RecvByte = recv(ServerSocket, (char*)&FileCount, sizeof(FileCount), 0);
    int NetFileCount = ntohl(FileCount);

    for (int i = 0; i < NetFileCount; i++) {
        //크기
        int NetFileSize = 0;
        RecvByte = recv(ServerSocket, (char*)&NetFileSize, sizeof(NetFileSize), 0);
        if (RecvByte <= 0)
        {
            break;
        }
        int RecvFileSize = ntohl(NetFileSize);

        //내용
        char* Buffer = new char[RecvFileSize];
        RecvByte = recv(ServerSocket, Buffer, RecvFileSize, MSG_WAITALL);

        if (RecvByte == RecvFileSize) {
            char FileName[100];
            sprintf(FileName, "image_%d.jpg", i);
            FILE* ImageFile = fopen(FileName, "wb");
            if (ImageFile)
            {
                fwrite(Buffer, sizeof(char), RecvFileSize, ImageFile);
                fclose(ImageFile);
            }
        }
        delete[] Buffer;
    }

    closesocket(ServerSocket);
    WSACleanup();

    return 0;
}