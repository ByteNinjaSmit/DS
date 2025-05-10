/* 
Assignemnt no: 5

Problem Statement: 

a pizaa delivery company want to optimize it's delivery process to minimize it's delivery time and fuel cost
the company has a central pizza hub where all pizza's are prepaid multiple delivery location where customer are waiting for there order
a road network connecting the hub to all delivery location with each road segment having a specefic distance or traveled time 
the goal his to determine shortest path from pizza hub to each customer location so that
delivery's can be made as quickly and efficently as possible 


Date: 18/03/2025
Author: Smitraj Bankar

Algorithm : Dijkshtra's

*/

#include <iostream>

using namespace std;

class PizzaDelivery {
private:
    int numLocations;
    int adjMatrix[10][10]; // Assuming max 10 locations for simplicity

public:
    // Constructor
    PizzaDelivery(int locations) {
        numLocations = locations;
        for (int i = 0; i < numLocations; i++) {
            for (int j = 0; j < numLocations; j++) {
                if (i == j)
                    adjMatrix[i][j] = 0;
                else
                    adjMatrix[i][j] = 9999; // Large value for infinity
            }
        }
    }

    // Function to accept user input for roads
    void acceptRoads(int roads) {
        int from, to, distance;
        for (int i = 0; i < roads; i++) {
            cout << "Enter road " << i + 1 << " (from, to, distance): ";
            cin >> from >> to >> distance;
            adjMatrix[from][to] = distance;
            adjMatrix[to][from] = distance; // Since roads are bidirectional
        }
    }

    // Dijkstra's Algorithm to find shortest path from hub to all locations
    void shortestPath(int hub) {
        int dist[10];
        bool visited[10];

        for (int i = 0; i < numLocations; i++) {
            dist[i] = 9999; // Initialize distances to a large value
            visited[i] = false;
        }

        dist[hub] = 0;

        for (int i = 0; i < numLocations - 1; i++) {
            int minDist = 9999, minIndex;
            for (int j = 0; j < numLocations; j++) {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    minIndex = j;
                }
            }

            visited[minIndex] = true;

            for (int j = 0; j < numLocations; j++) {
                if (!visited[j] && adjMatrix[minIndex][j] != 9999 &&
                    dist[minIndex] + adjMatrix[minIndex][j] < dist[j]) {
                    dist[j] = dist[minIndex] + adjMatrix[minIndex][j];
                }
            }
        }

        // Display shortest distances
        cout << "Shortest distances from the Pizza Hub:\n";
        for (int i = 0; i < numLocations; i++) {
            cout << "To location " << i << ": " << dist[i] << "\n";
        }
    }
};

int main() {
    int locations, roads;
    cout << "Enter number of locations: ";
    cin >> locations;
    PizzaDelivery deliverySystem(locations);

    cout << "Enter number of roads: ";
    cin >> roads;
    deliverySystem.acceptRoads(roads);

    int hub;
    cout << "Enter hub location: ";
    cin >> hub;
    deliverySystem.shortestPath(hub);

    return 0;
}
