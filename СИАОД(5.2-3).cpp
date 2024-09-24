#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;

string dir = "C:/Users/munaat/CLionProjects/SAPD1/";

struct Product {
    char name[6];
    int code;
};

struct IndexEntry {
    int code;
    streampos offset;
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

vector<IndexEntry> createIndexTable(const string& filename) {
    ifstream file(filename, ios::binary);
    vector<IndexEntry> indexTable;
    Product product{};
    while (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        streampos currentPos = file.tellg();
        indexTable.push_back({product.code, currentPos - static_cast<streamoff>(sizeof(Product))});
    }
    sort(indexTable.begin(), indexTable.end(), [](const IndexEntry& a, const IndexEntry& b) {
        return a.code < b.code;
    });
    file.close();
    return indexTable;
}


streampos binarySearch(const vector<IndexEntry>& indexTable, int key) {
    int left = 0;
    int right = indexTable.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (indexTable[mid].code == key) {
            return indexTable[mid].offset; // Возвращаем смещение
        }
        else if (indexTable[mid].code < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

streampos uniformBinarySearch(const vector<IndexEntry>& indexTable, int key) {
    if (indexTable.empty()) {
        return {-1};
    }
    int m = indexTable.size() / 2;
    int b = m / 2;
    int i = 0;
    while (m >= 0 && m < indexTable.size()) {
        if (indexTable[m].code == key) {
            return indexTable[m].offset;
        }
        else if (indexTable[m].code < key) {
            m += b;
        }
        else {
            m -= b;
        }
        b = (b+1)/2;
        if (b == 1){
            i++;
        }
        if(i>=10){break;}
    }
    return {-1};
}


Product readRecord(const string& filename, streampos offset) {
    Product product{};
    ifstream file(filename, ios::binary);
    file.seekg(offset);
    file.read(reinterpret_cast<char*>(&product), sizeof(Product));
    file.close();
    return product;
}


int main() {
    const string filename = dir+"products.bin";
    auto start = chrono::high_resolution_clock::now();
    auto indexTable = createIndexTable(filename);
    int searchCode = 999971;
    streampos offset = uniformBinarySearch(indexTable, searchCode);
    auto end = chrono::high_resolution_clock::now();
    if (offset != -1) {
        Product product = readRecord(filename, offset);
        cout << "Found product: " << product.name << ", Code: " << product.code << endl;
    } else {
        cout << "Not found" << endl;
    }
    chrono::duration<double> duration = end - start;
    cout << "Time: " << duration.count() << endl;
    return 0;
}