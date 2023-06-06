#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        cout << "WSAStartup failed: " << iResult << endl;
        return 1;
    }

    SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        cout << "Error creating socket: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(27015);

    iResult = bind(ListenSocket, (SOCKADDR*)&service, sizeof(service));
    if (iResult == SOCKET_ERROR) {
        cout << "bind failed with error: " << WSAGetLastError() << endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        cout << "listen failed with error: " << WSAGetLastError() << endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server started!" << endl;

    SOCKET ClientSocket = INVALID_SOCKET;
    while (true) {
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            cout << "accept failed: " << WSAGetLastError() << endl;
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        cout << "New client connected!" << endl;

        int n;
        recv(ClientSocket, (char*)&n, sizeof(int), 0);
        for (int i = 1; i <= n; i++) {
            send(ClientSocket, (char*)&i, sizeof(int), 0);
        }

        closesocket(ClientSocket);
        cout << "Client disconnected!" << endl;
    }

    closesocket(ListenSocket);
    WSACleanup();

    return 0;
}