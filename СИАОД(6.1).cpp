#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class UniversitySpecialization {
public:
    string code;
    string university;

    UniversitySpecialization(string c, string u) : code(c), university(u) {}
};

class HashTable {
private:
    vector<pair<string, UniversitySpecialization*>> table;
    int capacity;
    int size;
    float loadFactor;

    int hashFunction(const string& key) {
        hash<string> hashFunc;
        cout << key << " is " << hashFunc(key) << ", aka " << hashFunc(key) % capacity << endl;
        return hashFunc(key) % capacity;
    }

    void rehash() {
        cout << "Rehashing..." << endl;
        capacity *= 2;
        vector<pair<string, UniversitySpecialization*>> oldTable = table;

        table.clear();
        table.resize(capacity);
        size = 0;

        for (const auto& pair : oldTable) {
            if (pair.second != nullptr) {
                insert(pair.first, *pair.second);
            }
        }
    }

public:
    HashTable(int initialCapacity = 10, float loadFactorThreshold = 0.7) : capacity(initialCapacity), size(0), loadFactor(loadFactorThreshold) {
        table.resize(capacity);
    }

    void insert(const string& key, const UniversitySpecialization& specialization) {
        if ((float)size / capacity >= loadFactor) {
            rehash();
        }

        int index = hashFunction(key);
        while (table[index].second != nullptr) {
            index = (index + 1) % capacity; // Линейное пробирование
        }

        table[index] = {key, new UniversitySpecialization(specialization)};
        size++;
        cout << key << " inserted in bucket num " << index << endl;
    }

    void remove(const string& key) {
        int index = hashFunction(key);
        while (table[index].second != nullptr) {
            if (table[index].first == key) {
                delete table[index].second;
                table[index].second = nullptr;
                size--;
                cout << key << " removed from bucket num " << index << endl;
                return;
            }
            index = (index + 1) % capacity; // Линейное пробирование
        }
        cout << "Not found" << endl;
    }

    void search(const string& key) {
        int index = hashFunction(key);
        while (table[index].second != nullptr) {
            if (table[index].first == key) {
                cout << "Found: " << table[index].second->code << ", " << table[index].second->university << " in bucket num "  << index << endl;
                return;
            }
            index = (index + 1) % capacity; // Линейное пробирование
        }
        cout << "Not found" << endl;
    }

    void display() const {
        for (const auto& pair : table) {
            if (pair.second != nullptr) {
                cout << "Specialization code: " << pair.second->code << ", Name: " << pair.second->university << endl;
            }
        }
    }

    ~HashTable() {
        for (auto& pair : table) {
            delete pair.second;
        }
    }
};

int main() {
    HashTable ht;
    ht.insert("09.03.04", UniversitySpecialization("09.03.04", "IPT"));
    ht.insert("09.03.06", UniversitySpecialization("09.03.06", "ITM"));
    int choice;
    string menu = "Menu:\n0 - Add data\n1 - Remove data\n2 - Search data\n3 - Display data\n4 - Exit";
    string temp1, temp2;
    while (true) {
        cout << menu << endl;
        cin >> choice;
        switch (choice) {
            case 0:
                cout << "Enter code of specialization:" << endl;
                cin >> temp1;
                cout << "Enter name of specialization:" << endl;
                cin >> temp2;
                ht.insert(temp1, UniversitySpecialization(temp1, temp2));
                break;
            case 1:
                cout << "Enter code to remove:" << endl;
                cin >> temp1;
                ht.remove(temp1);
                break;
            case 2:
                cout << "Enter code to search:" << endl;
                cin >> temp1;
                ht.search(temp1);
                break;
            case 3:
                ht.display();
                break;
            case 4:
                return 0;
            default:
                cout << "Incorrect input" << endl;
        }
    }
}
/*
    char l = 'k';
    ht.insert("09.03.01", UniversitySpecialization("09.03.01", "IIT"));

    ht.insert("09.03.02", UniversitySpecialization("09.03.02", "IAI"));

    ht.insert("09.03.03", UniversitySpecialization("09.03.03", "ICST"));

    ht.insert("09.03.04", UniversitySpecialization("09.03.04", "IPT"));

    ht.insert("09.03.05", UniversitySpecialization("09.03.05", "IRI"));

    ht.insert("09.03.06", UniversitySpecialization("09.03.06", "ITM"));

    ht.insert("09.03.07", UniversitySpecialization("09.03.07", "IFCT"));

    ht.insert("09.03.08", UniversitySpecialization("09.03.08", "F"));

    ht.insert("09.03.09", UniversitySpecialization("09.03.09", "G"));

    ht.insert("09.03.10", UniversitySpecialization("09.03.10", "H"));

    ht.insert("09.03.11", UniversitySpecialization("09.03.11", "I"));

    ht.insert("09.03.12", UniversitySpecialization("09.03.12", "J"));

    ht.insert("09.03.13", UniversitySpecialization("09.03.13", "K"));

    ht.insert("09.03.14", UniversitySpecialization("09.03.14", "L"));

    ht.insert("09.03.15", UniversitySpecialization("09.03.15", "M"));

    ht.insert("09.03.16", UniversitySpecialization("09.03.16", "N"));

    ht.insert("09.03.17", UniversitySpecialization("09.03.17", "O"));

    ht.insert("09.03.18", UniversitySpecialization("09.03.18", "P"));

    ht.insert("09.03.19", UniversitySpecialization("09.03.19", "Q"));

    ht.search("09.03.01");
    ht.remove("09.03.01");
    ht.remove("09.03.14");
    ht.remove("09.03.14");
    return 0;
}
*/