#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int INF = 999;

int main() {

int N;


cout << "Enter number of routers: ";
cin >> N;

// Router names
vector<char> name(N);

cout << "\nEnter router names:\n";

for (int i = 0; i < N; i++) {
cout << "Router " << i + 1 << ": ";
cin >> name[i];
}


vector<vector<int>> cost(N, vector<int>(N));

cout << "\nEnter distance between routers.\n";
cout << "Enter 999 if there is no direct connection.\n\n";

for (int i = 0; i < N; i++) {

for (int j = i + 1; j < N; j++) {

int distance;

cout << "Distance " << name[i]
<< " - " << name[j] << ": ";

cin >> distance;

cost[i][j] = distance;
cost[j][i] = distance;
}
}

// Distance from a router to itself = 0
for (int i = 0; i < N; i++) {
cost[i][i] = 0;
}


vector<vector<int>> dist = cost;

// Display initial matrix
cout << "\n\n========== INITIAL COST MATRIX ==========\n\n";

cout << setw(10) << " ";

for (int i = 0; i < N; i++)
cout << setw(8) << name[i];

cout << endl;

for (int i = 0; i < N; i++) {

cout << setw(10) << name[i];

for (int j = 0; j < N; j++) {
cout << setw(8) << dist[i][j];
}

cout << endl;
}


for (int k = 0; k < N; k++) {

for (int i = 0; i < N; i++) {

for (int j = 0; j < N; j++) {

// Avoid adding infinity
if (dist[i][k] != INF &&
dist[k][j] != INF) {

if (dist[i][k] + dist[k][j] < dist[i][j]) {

dist[i][j] =
dist[i][k] + dist[k][j];
}
}
}
}


cout << "\n\n========== STEP " << k + 1
<< " (Through " << name[k] << ") ==========\n\n";

cout << setw(10) << " ";

for (int i = 0; i < N; i++)
cout << setw(8) << name[i];

cout << endl;

for (int i = 0; i < N; i++) {

cout << setw(10) << name[i];

for (int j = 0; j < N; j++) {
cout << setw(8) << dist[i][j];
}

cout << endl;
}
}


cout << "\n\n============================================\n";
cout << " FINAL ROUTING TABLES\n";
cout << "============================================\n";

for (int i = 0; i < N; i++) {

cout << "\nRouting Table for Router " << name[i] << "\n";

cout << left
<< setw(15) << "Destination"
<< setw(10) << "Cost"
<< endl;

cout << "-------------------------\n";

for (int j = 0; j < N; j++) {

cout << left
<< setw(15) << name[j]
<< setw(10) << dist[i][j]
<< endl;
}
}

return 0;
}