#include <iostream>
using namespace std;

class OBST {
    int keys[10];
    int freq[10];
    int cost[10][10];
    int root[10][10];

public:
    void input(int k[], int f[], int n) {
        for (int i = 0; i < n; i++) {
            keys[i] = k[i];
            freq[i] = f[i];
        }
    }

    void build(int n) {
        for (int i = 0; i < n; i++) {
            cost[i][i] = freq[i];
            root[i][i] = i;
        }

        for (int L = 2; L <= n; L++) {
            for (int i = 0; i <= n - L; i++) {
                int j = i + L - 1;
                cost[i][j] = 9999;
                int sum = 0;
                for (int s = i; s <= j; s++)
                    sum += freq[s];

                for (int r = i; r <= j; r++) {
                    int c = ((r > i) ? cost[i][r - 1] : 0) +
                            ((r < j) ? cost[r + 1][j] : 0) + sum;
                    if (c < cost[i][j]) {
                        cost[i][j] = c;
                        root[i][j] = r;
                    }
                }
            }
        }

        cout << "Minimum Cost: " << cost[0][n - 1] << endl;
    }

    void printTree(int i, int j, int parent, bool left) {
        if (i > j) return;
        int r = root[i][j];
        if (parent == -1)
            cout << "Root: " << keys[r] << endl;
        else if (left)
            cout << "Left child of " << keys[parent] << ": " << keys[r] << endl;
        else
            cout << "Right child of " << keys[parent] << ": " << keys[r] << endl;

        printTree(i, r - 1, r, true);
        printTree(r + 1, j, r, false);
    }
};

int main() {
    OBST obst;
    int keys[] = {10, 20, 30, 40};
    int freq[] = {4, 2, 6, 3};
    int n = 4;

    obst.input(keys, freq, n);
    obst.build(n);
    obst.printTree(0, n - 1, -1, false);

    return 0;
}
