/*
Assignment 7
A student record system is software application used to manage student records including student info, 10th, 12th
result. Hash table can be used  as a data structure to efficiently store or retrieve student records

algo: linear probing with chain hashing
*/

#include <iostream>
using namespace std;

class MedicalRecord {
    int ID;
    string Name;

public:
    void createTable();
    void insertRecords();
    void display();
    void search();
    void modify();
} records[10];

int keys[10], total;
int chain[10];  // chain array

void MedicalRecord::createTable() {
    cout << "Enter number of records to store (max 10): ";
    cin >> total;
    for (int i = 0; i < total; i++) {
        cout << "Enter ID " << i + 1 << ": ";
        cin >> keys[i];
    }

    for (int i = 0; i < 10; i++) {
        records[i].ID = -1;
        chain[i] = -1;
    }
}

void MedicalRecord::insertRecords() {
    for (int i = 0; i < total; i++) {
        int id = keys[i];
        int index = id % 10;
        int newIndex = index;

        // No collision
        if (records[index].ID == -1) {
            cout << "Enter Name for ID " << id << ": ";
            cin >> records[index].Name;
            records[index].ID = id;
        } else {
            // Collision: linear probing to find empty slot
            do {
                newIndex = (newIndex + 1) % 10;
            } while (records[newIndex].ID != -1);

            // Store at new location
            cout << "Enter Name for ID " << id << ": ";
            cin >> records[newIndex].Name;
            records[newIndex].ID = id;

            // Chain from original index
            int temp = index;
            while (chain[temp] != -1) {
                temp = chain[temp];
            }
            chain[temp] = newIndex;
        }
    }
}

void MedicalRecord::display() {
    cout << "\n--- Medical Records ---\n";
    cout << "Index\tID\tName\tChain\n";
    for (int i = 0; i < 10; i++) {
        if (records[i].ID != -1)
            cout << i << "\t" << records[i].ID << "\t" << records[i].Name << "\t" << chain[i] << "\n";
        else
            cout << i << "\t--\t--\t" << chain[i] << "\n";
    }
}

void MedicalRecord::search() {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;
    int index = id % 10;

    while (index != -1) {
        if (records[index].ID == id) {
            cout << "Found at index " << index << ": " << records[index].Name << "\n";
            return;
        }
        index = chain[index];
    }

    cout << "Record not found.\n";
}

void MedicalRecord::modify() {
    int id;
    cout << "Enter ID to modify: ";
    cin >> id;
    int index = id % 10;

    while (index != -1) {
        if (records[index].ID == id) {
            cout << "Current Name: " << records[index].Name << "\n";
            cout << "Enter New Name: ";
            cin >> records[index].Name;
            cout << "Record updated.\n";
            return;
        }
        index = chain[index];
    }

    cout << "Record not found.\n";
}

int main() {
    MedicalRecord m;
    m.createTable();
    m.insertRecords();
    m.display();

    int choice;
    do {
        cout << "\nMenu:\n1. Search\n2. Modify\n3. Display\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: m.search(); break;
            case 2: m.modify(); break;
            case 3: m.display(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
