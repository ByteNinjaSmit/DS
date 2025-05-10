/*
    Assignment 4
    Author Name: Smitraj Bankar
    Date : 11/03/2024

    Definition: You are a job seeker preparing for an interview in different cities.
    You have to visit each and every company within the shortest distance using the shortest path.

    Algorithm: Prim's Algorithm
    Method: MST (Minimum Spanning Tree)
*/

#include <iostream>
#define INF 999999
#define SIZE 10

using namespace std;

class JOB {
public:
    int V;
    int graph[SIZE][SIZE];
    int parent[SIZE];
    int key[SIZE];
    bool mstSet[SIZE];

    // object craring 
    JOB(int vertices) {
        V = vertices;
        for (int i = 0; i < SIZE; i++) {
            parent[i] = -1;
            key[i] = INF;
            mstSet[i] = false;
            for (int j = 0; j < SIZE; j++) {
                graph[i][j] = 0;
            }
        }
    }

    void inputGraph() {
        cout << "Enter the adjacency matrix representing the distances between cities:" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cin >> graph[i][j];
            }
        }
    }

    int findMinKey() {
        int min = INF, minIndex = -1;
        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    void primMST() {
        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < V - 1; count++) {
            int u = findMinKey();
            mstSet[u] = true;

            for (int v = 0; v < V; v++) {
                if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }
    }

    void printMST() {
        cout << "Edge \tWeight" << endl;
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << endl;
        }
    }
};

int main() {
    int V;
    cout << "Enter the number of cities (nodes) (max 10): ";
    cin >> V;
    
    if (V > SIZE) {
        cout << "Error: Maximum number of cities allowed is " << SIZE << "." << endl;
        return 1;
    }
    
    JOB job(V);
    job.inputGraph();
    job.primMST();
    job.printMST();
    
    return 0;
}