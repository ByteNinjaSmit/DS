/*
===========================================
           ASSIGNMENT NO: 3
===========================================

Problem Statement:
------------------
There are flight paths between cities. If there is a direct flight between city A and city B, 
then there is an edge between the cities. The cost of the edge can represent:
  1. The time taken for the flight from city A to city B.
  2. The amount of fuel required for the journey.

Each node in the graph represents an airport or a city. 

Tasks:
------
1. Implement **Adjacency Matrix** representation for the flight paths.
2. Implement **Adjacency List** representation for the flight paths using arrays and linked lists.
3. Allow the user to input:
   - The number of cities.
   - The names of the cities.
   - The fuel cost for flights between cities.
4. Display both representations properly.
5. Justify the storage representation used.

**Constraints:**
- Use **arrays** instead of STL vectors or prebuilt data structures.
- Implement linked lists manually for the adjacency list representation.

*/

#include <iostream>
#include <cstring>
using namespace std;

#define MAX_CITIES 100

class AMS {
public:
    int numOfCities;
    string cities[MAX_CITIES];
    int adjMatrix[MAX_CITIES][MAX_CITIES];

    // Adjacency List using Array-Based Linked List
    struct Node {
        int cityIndex;
        int fuel;
        Node* next;
    };

    Node* adjList[MAX_CITIES]; // Array of linked list heads

    AMS() {
        numOfCities = 0;
        memset(adjMatrix, 0, sizeof(adjMatrix)); // Initialize matrix with 0
        for (int i = 0; i < MAX_CITIES; i++) {
            adjList[i] = nullptr; // Initialize adjacency list heads
        }
    }

    // Accept Cities and Flight Path Data
    void accept() {
        cout << "Enter total number of cities: ";
        cin >> numOfCities;

        for (int i = 0; i < numOfCities; i++) {
            cout << "Enter name of city " << i + 1 << ": ";
            cin >> cities[i];
        }

        cout << "\nEnter flight paths (fuel cost), enter 0 if no flight:\n";
        for (int i = 0; i < numOfCities; i++) {
            for (int j = 0; j < numOfCities; j++) {
                if (i == j) {
                    adjMatrix[i][j] = 0; // No self-loop
                } else {
                    cout << "Fuel required from " << cities[i] << " to " << cities[j] << ": ";
                    cin >> adjMatrix[i][j];

                    if (adjMatrix[i][j] > 0) {
                        addEdge(i, j, adjMatrix[i][j]); // Insert into adjacency list
                    }
                }
            }
        }
    }

    // Add Edge to Adjacency List
     void addEdge(int src, int dest, int fuel) {
        Node* newNode = new Node();
        newNode->cityIndex = dest;
        newNode->fuel = fuel;
        newNode->next = adjList[src];
        adjList[src] = newNode;
    }

    // Display Adjacency Matrix
    void displayMatrix() {
        cout << "\nAdjacency Matrix Representation:\n";
        cout << "    ";
        for (int i = 0; i < numOfCities; i++) {
            cout << cities[i] << "\t";
        }
        cout << endl;

        for (int i = 0; i < numOfCities; i++) {
            cout << cities[i] << "\t";
            for (int j = 0; j < numOfCities; j++) {
                cout << adjMatrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    // Display Adjacency List
    void displayList() {
        cout << "\nAdjacency List Representation:\n";
        for (int i = 0; i < numOfCities; i++) {
            cout << cities[i] << " -> ";
            Node* temp = adjList[i];
            while (temp) {
                cout << cities[temp->cityIndex] << "(" << temp->fuel << ") -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }
};

int main() {
    AMS flight;
    flight.accept();
    flight.displayMatrix();
    flight.displayList();
    return 0;
}
