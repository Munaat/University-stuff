#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <random>
#include <chrono>
using namespace std;

string dir = "C:/Users/munaat/CLionProjects/SAPD1/";

struct Product {
    char name[6];
    int code;
};

int generateUniqueCode(set<int>& codes) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100000, 999999);
    int code;
    do {
        code = dis(gen);
    } while (codes.find(code) != codes.end());
    codes.insert(code);
    return code;
}

void createTextFile(const string& filename, int numProducts) {
    ofstream outFile(filename);
    set<int> codes;

    for (int i = 0; i < numProducts; ++i) {
        generateUniqueCode(codes);
    }
    int i = 0;
    for (const auto& code : codes) {
        Product product{};
        string name = "p" + to_string(i);
        copy(name.begin(), name.end(), product.name);
        product.code = code;
        outFile << product.name << " " << product.code << endl;
        i++;
    }
    outFile.close();
}


void createBinaryFile(const string& textFilename, const string& binaryFilename) {
    ifstream inFile(textFilename);
    ofstream outFile(binaryFilename, ios::binary);

    Product product{};
    while (inFile >> product.name >> product.code) {
        outFile.write(reinterpret_cast<char*>(&product), sizeof(Product));
    }

    inFile.close();
    outFile.close();
}

void searchProductByCode(const string& filename, int searchCode) {
    ifstream inFile(filename, ios::binary);
    Product product{};
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (product.code == searchCode) {
            found = true;
            cout << "Found: " << product.name << ", " << product.code << endl;
            break;
        }
    }
    if (!found) {
        cout << "Not found" << endl;
    }
    inFile.close();
}

int main() {
    for(int i = 100;i<=10000;i*=10) {
        cout << "Size: " << i << endl;
        createTextFile(dir + "products.txt", i);
        createBinaryFile(dir + "products.txt", dir + "products.bin");
        int code = 1;
        auto start = chrono::high_resolution_clock::now();
        searchProductByCode(dir + "products.bin", code);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Time: " << duration.count() << endl;
    }
    return 0;
}
