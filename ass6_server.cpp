
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <algorithm>

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

    // 2. Create UDP socket
    SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed!" << endl;
        WSACleanup();
        return 1;
    }

    // 3. Define server address
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9001);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // 4. Bind socket to IP address and port
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

    cout << "==================================" << endl;
    cout << "       UDP SERVER STARTED         " << endl;
    cout << "==================================" << endl;
    cout << "Port: 9001" << endl;
    cout << "Waiting for client..." << endl;

    // 5. Client address
    sockaddr_in clientAddress{};
    int clientLength = sizeof(clientAddress);

    char buffer[255];

    // 6. Receive message from client
    int bytesReceived = recvfrom(
        serverSocket,
        buffer,
        sizeof(buffer) - 1,
        0,
        (sockaddr*)&clientAddress,
        &clientLength
    );

    if (bytesReceived == SOCKET_ERROR)
    {
        cout << "Error receiving message!" << endl;

        closesocket(serverSocket);
        WSACleanup();

        return 1;
    }

    // Add null character
    buffer[bytesReceived] = '\0';

    string message = buffer;

    cout << endl;
    cout << "Message received from client: "
         << message << endl;

    // 7. Reverse the string
    reverse(message.begin(), message.end());

    // 8. Send reversed string to client
    int bytesSent = sendto(
        serverSocket,
        message.c_str(),
        static_cast<int>(message.length()),
        0,
        (sockaddr*)&clientAddress,
        clientLength
    );

    if (bytesSent == SOCKET_ERROR)
    {
        cout << "Error sending response!" << endl;

        closesocket(serverSocket);
        WSACleanup();

        return 1;
    }

    cout << "Reversed string sent to client: "
         << message << endl;

    cout << endl;
    cout << "Server completed successfully." << endl;

    // 9. Close server socket
    closesocket(serverSocket);

    // 10. Cleanup Winsock
    WSACleanup();

    return 0;
}
