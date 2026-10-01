

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
Assignment6_Client.cpp
Displaying Assignment6_Client.cpp.