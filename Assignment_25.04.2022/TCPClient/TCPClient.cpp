// TCPClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<stdio.h>
#include<winsock2.h>
#include <string>
#include <stdlib.h> 
#include <string>
#include <iostream>
using namespace std;

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#pragma warning(disable:4996) 
#define INFO_BUFFER_SIZE 32767

int main(int argc, char* argv[])
{

	// Khoi tao thu vien

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Ket noi khong thanh cong - %d\n", WSAGetLastError());
		return 1;
	}

	// Tao socket 

	SOCKET s;
	struct sockaddr_in server;
	const char* message;
	char	server_reply[2000];
	int recv_size;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("khong the khoi tao socket : %d", WSAGetLastError());
	}

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(1234);

	if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected"); 

	int action = 1;
	char buf[256];
	char buffer[2048];

    while (true) {
        int helloFromServer = recv(s, buffer, sizeof(buffer), 0);

        if (helloFromServer <= 0)
        {
            if (helloFromServer == -1) {
                helloFromServer = WSAGetLastError();
            }
            break;
        }

        if (helloFromServer < sizeof(buffer)) {
            buffer[helloFromServer] = 0;
        }

        printf("%s \n", buffer);

        break;
    }

    while (action == 1)
    {

        printf("Nhap noi dung tin nhan gui den server\n");

        string input;

        getline(cin, input);

         string message = "Information by client: " + input;

        const char* output = input.c_str();

        send(s, output, strlen(output), 0);

        int valread = recv(s, buf, sizeof(buf), 0);

        if (valread <= 0)
        {
            if (valread == -1) {
                valread = WSAGetLastError();
            }
            break;
        }

        if (valread < sizeof(buf)) {
            buf[valread] = 0;
        }

        printf("Tin nhan nhan gui toi server: %s\n", buf);

        printf("---------------------------- \n");

        if (strcmp((char*)&input, "bye") == 0)
        {
            action = 0;
        }
        fflush(stdin);
    }

    closesocket(s);

    WSACleanup();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
