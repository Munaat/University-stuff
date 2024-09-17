#include <iostream>
#include <fstream>
#include <bitset>
#include <chrono>

using namespace std;

const int cap = 10000000;
const int arrsize = (cap / 8);

void add(unsigned char (&obj)[arrsize], int i) {
    if (i >= 0 && i < cap) obj[i / 8] |= (1 << (i % 8));
}

void sorted(const unsigned char obj[arrsize], ofstream& outFile) {
    for (int j = 0; j < arrsize; ++j) {
        bitset<8> s(obj[j]);
        for (int i = 0; i < 8; ++i) {
            if (s[i]) {
                outFile << (i + j * 8) << '\n';
            }
        }
    }
}

int main() {
    unsigned char bitArray[arrsize] = {0};
    ifstream inputFile("C:/Users/munaat/CLionProjects/SAPD1/input.txt");

    auto start = chrono::high_resolution_clock::now();

    int temp;
    while (inputFile >> temp) {
        add(bitArray, temp);
    }
    inputFile.close();

    ofstream outputFile("C:/Users/munaat/CLionProjects/SAPD1/output.txt");
    sorted(bitArray, outputFile);
    outputFile.close();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Sorting time: " << duration.count() << " seconds" << endl;

    return 0;
}


