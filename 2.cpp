#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {
string binary;
int r = 0;

cout << "Enter binary data: ";
cin >> binary;

// Validate input
for (char bit : binary) {
if (bit != '0' && bit != '1') {
cout << "Invalid binary data";
return 0;
}
}

int m = binary.length();

// Find number of parity bits
while (pow(2, r) < (m + r + 1)) {
r++;
}

int totalBits = m + r;

char hamming[100];

// Insert parity positions and data bits from right side
int dataIndex = m - 1;

for (int pos = 1; pos <= totalBits; pos++) {

if ((pos & (pos - 1)) == 0) {
hamming[pos] = '0'; // parity placeholder
}
else {
hamming[pos] = binary[dataIndex];
dataIndex--;
}
}


// Calculate parity bits
for (int i = 0; i < r; i++) {

int parityPos = pow(2, i);
int count = 0;

for (int pos = 1; pos <= totalBits; pos++) {

if (pos & parityPos) {

if (hamming[pos] == '1')
count++;
}
}

if (count % 2 == 0)
hamming[parityPos] = '0';
else
hamming[parityPos] = '1';
}


cout << "\nNumber of data bits: " << m;
cout << "\nNumber of parity bits: " << r;


// Show parity bit coverage
cout << "\n\nParity Bit Coverage:\n";

for (int i = 0; i < r; i++) {

int parityPos = pow(2, i);

cout << "\nP" << parityPos
<< " (Position " << parityPos << ") = "
<< hamming[parityPos];

cout << "\nChecks positions: ";

for (int pos = 1; pos <= totalBits; pos++) {

if (pos & parityPos) {
cout << pos << " ";
}
}

cout << "\nValues considered: ";

for (int pos = 1; pos <= totalBits; pos++) {

if (pos & parityPos) {
cout << hamming[pos] << " ";
}
}

cout << endl;
}


// Show final arrangement
cout << "\n\nHamming Code Arrangement:\n";

cout << "Position: ";
for (int pos = totalBits; pos >= 1; pos--) {
cout << pos << " ";
}

cout << "\nBit: ";

for (int pos = totalBits; pos >= 1; pos--) {
cout << hamming[pos] << " ";
}
char choice;

cout << "\nDo you want to send data with error? (y/n): ";
cin >> choice;

if (choice == 'y' || choice == 'Y') {

int errorPosition;

cout << "Enter the position of bit to flip (from right side): ";
cin >> errorPosition;

if (errorPosition < 1 || errorPosition > totalBits) {
cout << "Invalid position!" << endl;
return 0;
}

// Flip the bit
if (hamming[errorPosition] == '0')
hamming[errorPosition] = '1';
else
hamming[errorPosition] = '0';


cout << "\nError introduced at position "
<< errorPosition << endl;

cout << "Data after introducing error: ";

// Display left to right
for (int pos = totalBits; pos >= 1; pos--) {
cout << hamming[pos];
}

cout << endl;

}
else {

cout << "\nData sent without error: ";

for (int pos = totalBits; pos >= 1; pos--) {
cout << hamming[pos];
}

cout << endl;
}



return 0;
}