#include <iostream>
#include <winsock2.h>
#include <stdint.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

int check() 
{
    int n;
    while (true) {
        cin >> n;
        if ((cin.fail() || cin.peek() != '\n') || (n <= 0))
        {
            cin.clear();
            cin.ignore(1000000, '\n');
            cout << "Error, try again: ";
        }
        else return n;
    }
}

int main()
{
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0)
    {
        cout << "Error";
        return 1;
    }
    //информация об адресе сокета  
    SOCKADDR_IN addr;
    int size_of_addr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;
    //прослушивание
    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    SOCKET newConnection;
      
    newConnection = accept(sListen, (SOCKADDR*)&addr, &size_of_addr);
    if (newConnection == 0)
    {
        cout << "Error\n";
    }
    else
    {
        cout << "Connection succesful\n";            
        int n;
        int i = 0;
        cout << "Input n: ";
        n = check();
        while(true)
        {          
            newConnection = accept(sListen, (SOCKADDR*)&addr, &size_of_addr);  
            for (i; i <= n; i++)
            {
                
                if(send(newConnection, (char*)&i, sizeof(i), NULL) == SOCKET_ERROR)
                {
                    cout << "Failed to write data to socket: " << GetLastError() << endl;
                    break;
                }
                cout << "Client" << newConnection << ":";
                cout << i << endl;
                Sleep(200);
            }
              
            
            if (i >= n)
            {
                cout << "Task complited\n";
                break;
            }
        }
    }
        
    
    return 0;
}

