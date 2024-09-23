#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <random>

using namespace std;

string dir = "C:/Users/munaat/CLionProjects/SAPD1/";

struct Product {
    string name;
    int code{};
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
        Product product;
        product.name = "product" + to_string(i);
        product.code = code;
        outFile << product.name << " " << product.code << endl;
        i++;
    }

    outFile.close();
}


void createBinaryFile(const string& textFilename, const string& binaryFilename) {
    ifstream inFile(textFilename);
    ofstream outFile(binaryFilename, ios::binary);

    Product product;
    while (inFile >> product.name >> product.code) {
        outFile.write(reinterpret_cast<char*>(&product), sizeof(Product));
    }

    inFile.close();
    outFile.close();
}


int main() {
    createTextFile(dir+"products.txt", 10000); // Создаем текстовый файл с 10 продуктами
    createBinaryFile(dir+"products.txt", dir+"products.bin"); // Преобразуем в двоичный файл
    return 0;
}
