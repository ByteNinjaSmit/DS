/* Assignment 6
Def - A medical record system is a software application used to manage medical records including patient information, medical history, and treatment plan.
Hash table can be used as a data structure to efficiently store and retrieve medical records.
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

void MedicalRecord::createTable() {
    cout << "Enter number of records to store (max 10): ";
    cin >> total;
    for (int i = 0; i < total; i++) {
        cout << "Enter ID " << i + 1 << ": ";
        cin >> keys[i];
    }

    for (int i = 0; i < 10; i++) {
        records[i].ID = -1; // Initialize hash table
    }
}

void MedicalRecord::insertRecords() {
    for (int i = 0; i < total; i++) {
        int index = keys[i] % 10;

        while (records[index].ID != -1) {
            index = (index + 1) % 10; // Linear probing
        }

        records[index].ID = keys[i];
        cout << "Enter Name for ID " << keys[i] << ": ";
        cin >> records[index].Name;
    }
}

void MedicalRecord::display() {
    cout << "\n--- Medical Records ---\n";
    cout << "Index\tID\tName\n";
    for (int i = 0; i < 10; i++) {
        if (records[i].ID != -1)
            cout << i << "\t" << records[i].ID << "\t" << records[i].Name << "\n";
        else
            cout << i << "\t--\t--\n";
    }
}

void MedicalRecord::search() {
    int id, index, count = 0;
    cout << "Enter ID to search: ";
    cin >> id;
    index = id % 10;

    while (records[index].ID != id && count < 10) {
        index = (index + 1) % 10;
        count++;
    }

    if (records[index].ID == id)
        cout << "Found at index " << index << ": " << records[index].Name << "\n";
    else
        cout << "Record not found.\n";
}

void MedicalRecord::modify() {
    int id, index, count = 0;
    cout << "Enter ID to modify: ";
    cin >> id;
    index = id % 10;

    while (records[index].ID != id && count < 10) {
        index = (index + 1) % 10;
        count++;
    }

    if (records[index].ID == id) {
        cout << "Current Name: " << records[index].Name << "\n";
        cout << "Enter New Name: ";
        cin >> records[index].Name;
        cout << "Record updated.\n";
    } else {
        cout << "Record not found.\n";
    }
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
