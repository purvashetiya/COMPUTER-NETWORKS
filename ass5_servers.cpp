

Skip to content
Using Gmail with screen readers
in:sent 
2 of 61
Assignment5_Server
Inbox

Purva <purvashetiya2.0@gmail.com>
Attachments
09:47 (6 minutes ago)
to purva.shetiya, tanushree.walunj

#include <iostream> #include <vector> #include <iomanip> using namespace std; const int INF = 999; int main() { int N; cout << "Enter number of routers: "; cin >> N; // Router names vector<char> name(N); cout << "\nEnter router names:\n"; for (int i = 0; i < N; i++) { cout << "Router " << i + 1 << ": "; cin >> name[i]; } vector<vector<int>> cost(N, vector<int>(N)); cout << "\nEnter distance between routers.\n"; cout << "Enter 999 if there is no direct connection.\n\n"; for (int i = 0; i < N; i++) { for (int j = i + 1; j < N; j++) { int distance; cout << "Distance " << name[i] << " - " << name[j] << ": "; cin >> distance; cost[i][j] = distance; cost[j][i] = distance; } } // Distance from a router to itself = 0 for (int i = 0; i < N; i++) { cost[i][i] = 0; } vector<vector<int>> dist = cost; // Display initial matrix cout << "\n\n========== INITIAL COST MATRIX ==========\n\n"; cout << setw(10) << " "; for (int i = 0; i < N; i++) cout << setw(8) << name[i]; cout << endl; for (int i = 0; i < N; i++) { cout << setw(10) << name[i]; for (int j = 0; j < N; j++) { cout << setw(8) << dist[i][j]; } cout << endl; } for (int k = 0; k < N; k++) { for (int i = 0; i < N; i++) { for (int j = 0; j < N; j++) { // Avoid adding infinity if (dist[i][k] != INF && dist[k][j] != INF) { if (dist[i][k] + dist[k][j] < dist[i][j]) { dist[i][j] = dist[i][k] + dist[k][j]; } } } } cout << "\n\n========== STEP " << k + 1 << " (Through " << name[k] << ") ==========\n\n"; cout << setw(10) << " "; for (int i = 0; i < N; i++) cout << setw(8) << name[i]; cout << endl; for (int i = 0; i < N; i++) { cout << setw(10) << name[i]; for (int j = 0; j < N; j++) { cout << setw(8) << dist[i][j]; } cout << endl; } } cout << "\n\n============================================\n"; cout << " FINAL ROUTING TABLES\n"; cout << "============================================\n"; for (int i = 0; i < N; i++) { cout << "\nRouting Table for Router " << name[i] << "\n"; cout << left << setw(15) << "Destination" << setw(10) << "Cost" << endl; cout << "-------------------------\n"; for (int j = 0; j < N; j++) { cout << left << setw(15) << name[j] << setw(10) << dist[i][j] << endl; } } return 0; }
 4 attachment
  •  Scanned by Gmail

Mail Delivery Subsystem <mailer-daemon@googlemail.com>
09:47 (6 minutes ago)
to me

Error Icon
Address not found
Your message wasn't delivered to tanushree.walunj@mitwpu.edu because the domain mitwpu.edu couldn't be found. Check for typos or unnecessary spaces and try again.
LEARN MORE
The response was:
DNS Error: DNS type 'mx' lookup of mitwpu.edu responded with code NXDOMAIN Domain name not found: mitwpu.edu For more information, go to https://support.google.com/mail/?p=BadRcptDomain

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
Assignment5_Server.cpp
Displaying Assignment5_Client.cpp.