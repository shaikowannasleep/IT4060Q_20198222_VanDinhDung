// TCPSever.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include <string.h> 
#include <stdlib.h> 
#include <string>
#include <iostream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")  
#pragma warning(disable:4996)

void ToUp(char* p) {
	while (*p) {
		*p = toupper(*p);
		p++;
	}
}


int main(int argc, char* argv[])
{
    // Khoi tao thu vien
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Tao socket
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai bao dia chi server
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(1234);

    // Gan cau truc dia chi voi socket
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));

    // Chuyen sang trang thai cho ket noi
    listen(listener, 5);

    // Cho ket noi moi
    SOCKET client = accept(listener, NULL, NULL);

    FILE* helloClientFile = fopen("C:\\Users\\shuna\\Documents\\GitHub\\IT4060Q_20198222_VanDinhDung\\Assignment_25.04.2022\\TCPSever\\hello_client.txt", "r");

    FILE* clientMessage = fopen("C:\\Users\\shuna\\Documents\\GitHub\\IT4060Q_20198222_VanDinhDung\\Assignment_25.04.2022\\TCPSever\\client_message.txt", "a");
    int ret;

    char buf[256];

    char buffer[2048];

    while (!feof(helloClientFile)) {
        ret = fread(buffer, 1, sizeof(buffer), helloClientFile);

        if (ret > 0)
        {
            send(client, buffer, ret, 0);
        }
    }

    while (1)
    {
        ret = recv(client, buf, sizeof(buf), 0);

        if (ret <= 0)
        {
            if (ret == -1) {
                ret = WSAGetLastError();
            }
            break;
        }

        if (ret < sizeof(buf)) {
            buf[ret] = 0;
        }

        fwrite(buf, 1, ret, clientMessage);

        fwrite("\n", sizeof(char), 1, clientMessage);

        printf("Tin nhan nhan duoc tu client: %s\n", buf);

        ToUp(buf);

        send(client, buf, sizeof(buf), 0);
    }

    fclose(helloClientFile);

    fclose(clientMessage);

    // Dong ket noi
    closesocket(client);
    closesocket(listener);
    WSACleanup();

	return 0;
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
