#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#pragma warning(disable:4996) 

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
	DWORD size;
	char cName[500];

	GetComputerNameA(cName, &size);

	puts(cName);

	DWORD test;
	int i;
	DWORD mydrives = 100;

	char lpBuffer[100];
	test = GetLogicalDriveStrings(mydrives, (LPWSTR)lpBuffer);

	char driv[20];
	int count = 0;

	if (test != 0)
	{
		printf("GetLogicalDriveStrings() return value: %d, Error (if any): %d \n", test, GetLastError());
		printf("The logical drives :\n");

		for (i = 0; i < test * 2 + 1; i++) {
			if (lpBuffer[i] > 0) {
				driv[count] = lpBuffer[i];
				count++;
			}

		}

	}
	driv[count] = '\0';

	char nameDrive;
	printf("%s", driv);
	LPCWSTR DriveDisk[3] = { L"C:",L"D:",L"E:"};


	BOOL test2, fResult;
	DWORD dwSectPerClust, dwBytesPerSect, dwFreeClusters, dwTotalClusters;
	__int64 lpFreeBytesAvailable, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes;


	for (int i = 0; i < 3; i++) {
		test2 = GetDiskFreeSpaceEx(
			DriveDisk[i],
			(PULARGE_INTEGER)&lpFreeBytesAvailable,
			(PULARGE_INTEGER)&lpTotalNumberOfBytes,
			(PULARGE_INTEGER)&lpTotalNumberOfFreeBytes
		);
		if (test2 != 0) {
			printf("\nDrive to be checked: %s\n", DriveDisk[i]);

			printf("Using GetDiskFreeSpaceEx()...\n");

			//kiem tra gia tri tra ve

			printf("The return value: %d, error code: %d\n", test2, GetLastError());

			printf("Total number of free bytes available for user-caller: %ul\n", lpFreeBytesAvailable);

			printf("Total number of bytes available for user: %ul\n", lpTotalNumberOfBytes);
						
			printf("Total number of free bytes on disk: %ul\n", lpTotalNumberOfFreeBytes);

		}
		else {
			printf("\nDrive to be checked: %s\n", DriveDisk[i]);
			printf("The return value: %d, error code: %d\n", test2, GetLastError());
		}
	}

	char newLine[] = "\n";
	strcat(cName, newLine);
	char txt[] = "The logical drives of this machine : \n";
	strcat(cName, txt);
	strcat(cName, driv);
	strcat(cName, newLine);

	const char* mess = cName;

	if (send(s, mess, strlen(mess), 0) < 0)
	{
		puts("Send failed");
		return 1;
	}

	puts("Data Send\n");

	
	if ((recv_size = recv(s, server_reply, 2000, 0)) == SOCKET_ERROR)
	{
		puts("nhan thong tin that bai");
	}
	return 0;
}