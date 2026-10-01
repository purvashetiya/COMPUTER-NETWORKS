

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    // 1. Initialize Winsock
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "WSAStartup failed!" << endl;
        return 1;
    }

    // 2. Create TCP socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed!" << endl;
        WSACleanup();
        return 1;
    }

    // 3. Define server address
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);

    // Server is running on same computer
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 4. Connect to server
    cout << "Connecting to server..." << endl;

    if (connect(
            clientSocket,
            (sockaddr*)&serverAddress,
            sizeof(serverAddress)) == SOCKET_ERROR)
    {
        cout << "Connection failed!" << endl;

        closesocket(clientSocket);
        WSACleanup();

        return 1;
    }

    cout << "Connected to server successfully!" << endl;

    // Chat loop
    while (true)
    {
        // 5. Input message
        string clientMessage;

        cout << endl;
        cout << "Client: ";
        getline(cin, clientMessage);

        // 6. Send message to server
        send(
            clientSocket,
            clientMessage.c_str(),
            static_cast<int>(clientMessage.length()),
            0
        );

        // Exit condition
        if (clientMessage == "exit")
        {
            break;
        }

        // 7. Receive reply from server
        char buffer[1024];

        int bytesReceived = recv(
            clientSocket,
            buffer,
            sizeof(buffer) - 1,
            0
        );

        if (bytesReceived <= 0)
        {
            cout << "Server disconnected." << endl;
            break;
        }

        buffer[bytesReceived] = '\0';

        cout << "Server: " << buffer << endl;

        if (string(buffer) == "exit")
        {
            break;
        }
    }

    // 8. Close client socket
    closesocket(clientSocket);

    // 9. Cleanup Winsock
    WSACleanup();

    cout << endl;
    cout << "Client closed." << endl;

    return 0;
}
