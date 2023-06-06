#include <iostream>
#include <winsock2.h>
#include <stdint.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

int main()
{
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0)
    {
        cout << "Error";
        return 1;
    }

    SOCKADDR_IN addr;
    int size_of_addr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
    {
        cout << "Failed connection\n";
        return 1;
    }
    cout << "Connection successfull\n";
    int k;
    while (recv(Connection, (char*)&k, sizeof(k), NULL) != SOCKET_ERROR)
    {
        cout << k << endl;
        Sleep(200);
    }

    closesocket(Connection);

    return 0;
}
