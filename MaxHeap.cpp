/*
Heap is a special tree-based data structure that satisfies the heap property.
*/
#include <iostream>
using namespace std;

class heaptree
{
public:
    int totalkeys;
    int heap[10];

    void insert()
    {
        // accept total keys
        cout << "Enter total number of keys: ";
        cin >> totalkeys;

        // accept each key and put into heap array
        for (int loc = 0; loc < totalkeys; loc++)
        {
            cout << "Enter key: ";
            cin >> heap[loc];
            // pass the location in built function
            built(loc);
        }
    }

    void built(int loc)
    {
        // update the parent location
        int parent = (loc - 1) / 2;
        while (loc > 0 && heap[parent] < heap[loc])
        {                                  // apply the while loop for loc>0 and head[parent] > head[loc]
            swap(heap[parent], heap[loc]); // swap the position
            loc = parent;                  // update the location and parent value
            parent = (loc - 1) / 2;
        }
    }

    void display()
    {
        if (totalkeys > 0)
        { // only print when total keys are greater than 0
            cout << "Heap Tree: ";
            for (int loc = 0; loc < totalkeys; loc++)
            {                             // if cond^n satisfies then apply for loop from 0 to total keys
                cout << heap[loc] << " "; // print heap[loc] value
            }
            cout << endl;
        }
        else
        { // else empty
            cout << "Heap is empty!\n";
        }
    }
} heapObject; // object creation

int main()
{
    int choice;
    do
    {
        cout << "1. Accept Data \t 2. Display Heap \t 0. Exit Program\n";
        cout << "Enter the Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            heapObject.insert();
            break;
        case 2:
            heapObject.display();
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    } while (choice != 0);
    return 0;
}