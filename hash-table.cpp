#include <iostream>
#include <iomanip>
using namespace std;

#define SIZE 10

struct DataItem {
    int data;
    int key;
    DataItem(int k = -1, int d = -1) : key(k), data(d) {}
};

class HashTable {
private:
    DataItem** hashArray;
    DataItem* dummyItem;

    int hashCode(int key) const {
        return key % SIZE;
    }

public:
    HashTable() {
        hashArray = new DataItem*[SIZE];
        for (int i = 0; i < SIZE; i++)
            hashArray[i] = nullptr;
        dummyItem = new DataItem(-1, -1);
    }

    ~HashTable() {
        for (int i = 0; i < SIZE; i++)
            if (hashArray[i] && hashArray[i] != dummyItem)
                delete hashArray[i];
        delete[] hashArray;
        delete dummyItem;
    }

    void insert(int key, int data) {
        DataItem* item = new DataItem(key, data);
        int hashIndex = hashCode(key);
        while (hashArray[hashIndex] && hashArray[hashIndex] != dummyItem) {
            if (hashArray[hashIndex]->key == key) {
                hashArray[hashIndex]->data = data;
                delete item;
                return;
            }
            hashIndex = (hashIndex + 1) % SIZE;
        }
        hashArray[hashIndex] = item;
    }

    DataItem* search(int key) const {
        int hashIndex = hashCode(key);
        while (hashArray[hashIndex]) {
            if (hashArray[hashIndex]->key == key)
                return hashArray[hashIndex];
            hashIndex = (hashIndex + 1) % SIZE;
        }
        return nullptr;
    }

    DataItem* remove(int key) {
        int hashIndex = hashCode(key);
        while (hashArray[hashIndex]) {
            if (hashArray[hashIndex]->key == key) {
                DataItem* temp = hashArray[hashIndex];
                hashArray[hashIndex] = dummyItem;
                return temp;
            }
            hashIndex = (hashIndex + 1) % SIZE;
        }
        return nullptr;
    }

    void display() const {
        for (int i = 0; i < SIZE; i++) {
            cout << setw(3) << i << ": ";
            if (!hashArray[i])
                cout << "NULL";
            else if (hashArray[i] == dummyItem)
                cout << "DELETED";
            else
                cout << hashArray[i]->key << ":" << hashArray[i]->data;
            cout << endl;
        }
    }
};

int main() {
    HashTable ht;
    ht.insert(1, 100);
    ht.insert(2, 200);
    ht.insert(12, 1200);    // collision with key 2
    ht.insert(22, 2200);    // another collision
    ht.display();

    DataItem* found = ht.search(12);
    if (found)
        cout << "Found key 12: " << found->data << endl;
    else
        cout << "Key 12 not found.\n";

    ht.remove(12);
    ht.display();

    return 0;
}