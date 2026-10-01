


#include <winsock2.h>
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
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed!" << endl;
        WSACleanup();
        return 1;
    }

    // 3. Define server address
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // 4. Bind socket
    if (bind(
            serverSocket,
            (sockaddr*)&serverAddress,
            sizeof(serverAddress)) == SOCKET_ERROR)
    {
        cout << "Bind failed!" << endl;

        closesocket(serverSocket);
        WSACleanup();

        return 1;
    }

    // 5. Listen for client
    if (listen(serverSocket, 1) == SOCKET_ERROR)
    {
        cout << "Listen failed!" << endl;

        closesocket(serverSocket);
        WSACleanup();

        return 1;
    }

    cout << "==================================" << endl;
    cout << "       TCP SERVER STARTED         " << endl;
    cout << "==================================" << endl;
    cout << "Port: 9002" << endl;
    cout << "Waiting for client connection..." << endl;

    // 6. Accept client connection
    sockaddr_in clientAddress{};
    int clientLength = sizeof(clientAddress);

    SOCKET clientSocket = accept(
        serverSocket,
        (sockaddr*)&clientAddress,
        &clientLength
    );

    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Accept failed!" << endl;

        closesocket(serverSocket);
        WSACleanup();

        return 1;
    }

    cout << "Client connected successfully!" << endl;

    // Chat loop
    while (true)
    {
        char buffer[1024];

        // 7. Receive message from client
        int bytesReceived = recv(
            clientSocket,
            buffer,
            sizeof(buffer) - 1,
            0
        );

        if (bytesReceived <= 0)
        {
            cout << "Client disconnected." << endl;
            break;
        }

        buffer[bytesReceived] = '\0';

        string clientMessage = buffer;

        cout << endl;
        cout << "Client: " << clientMessage << endl;

        // Exit condition
        if (clientMessage == "exit")
        {
            break;
        }

        // 8. Input server reply
        string serverMessage;

        cout << "Server: ";
        getline(cin, serverMessage);

        // 9. Send reply to client
        send(
            clientSocket,
            serverMessage.c_str(),
            static_cast<int>(serverMessage.length()),
            0
        );

        if (serverMessage == "exit")
        {
            break;
        }
    }

    // 10. Close client connection
    closesocket(clientSocket);

    // 11. Close server socket
    closesocket(serverSocket);

    // 12. Cleanup Winsock
    WSACleanup();

    cout << endl;
    cout << "Server closed." << endl;

    return 0;
}
