



#include <winsock2.h>
#include <iostream>
#include <cstring>

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
    SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed!" << endl;
        WSACleanup();
        return 1;
    }

    // 3. Define server address
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9001);

    // Server is running on the same computer
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 4. Input message
    char message[255];

    cout << "==================================" << endl;
    cout << "       UDP CLIENT STARTED         " << endl;
    cout << "==================================" << endl;

    cout << "Enter a string: ";
    cin.getline(message, sizeof(message));

    // 5. Send message to server
    int bytesSent = sendto(
        clientSocket,
        message,
        strlen(message),
        0,
        (sockaddr*)&serverAddress,
        sizeof(serverAddress)
    );

    if (bytesSent == SOCKET_ERROR)
    {
        cout << "Error sending message!" << endl;

        closesocket(clientSocket);
        WSACleanup();

        return 1;
    }

    cout << endl;
    cout << "Message sent to server: "
         << message << endl;

    // 6. Receive reply from server
    char buffer[255];

    int serverLength = sizeof(serverAddress);

    int bytesReceived = recvfrom(
        clientSocket,
        buffer,
        sizeof(buffer) - 1,
        0,
        (sockaddr*)&serverAddress,
        &serverLength
    );

    if (bytesReceived == SOCKET_ERROR)
    {
        cout << "Error receiving response!" << endl;

        closesocket(clientSocket);
        WSACleanup();

        return 1;
    }

    // Add null character
    buffer[bytesReceived] = '\0';

    // 7. Display server reply
    cout << "Reversed string: "
         << buffer << endl;

    cout << endl;
    cout << "Client completed successfully." << endl;

    // 8. Close client socket
    closesocket(clientSocket);

    // 9. Cleanup Winsock
    WSACleanup();

    return 0;
}
