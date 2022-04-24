#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")  
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{

	// Khoi tao thu vien

	WSADATA wsa; 

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	
	// Tao socket

	SOCKET s, new_socket;
	struct sockaddr_in server, client;
	int c;
	const char* message;
	char recvbuf[512];
	int recvbuflen = 512;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("khong the tao socket : %d", WSAGetLastError());
	}

	// Khai bao dia chi server 

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(1234);

	//Bind cau truc dia chi voi socket
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
	}

	puts("Bind done");

	// Chuyen sang trang thai cho ket noi
	listen(s, 3);

	// Cho ket noi moi 
	puts("Dang doi ket noi moi...");

	c = sizeof(struct sockaddr_in);
	new_socket = accept(s, (struct sockaddr*)&client, &c);
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d", WSAGetLastError());
	}
	puts("Connection accepted");

	int iResult = recv(new_socket, recvbuf, recvbuflen, 0);
	int iSendResult = send(new_socket, recvbuf, iResult, 0);

	puts("Received\n");

	recvbuf[iResult] = '\0';
	puts(recvbuf);



	// Tra loi client
	message = "Hello Client\n";
	send(new_socket, message, strlen(message), 0);
	puts("End\n");
	getchar();

	// Dong ket noi va giai phong thu vien

	closesocket(s);
	WSACleanup();

	return 0;
}