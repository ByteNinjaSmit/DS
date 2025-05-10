#include <iostream>
#include <iomanip>
using namespace std;

class OBST {
public:
    float cost[11][11], weight[11][11];
    int root[11][11];
    int n;
    float p[10], q[11];
    string keys[10];

    void input() {
        cout << "Enter number of keys: ";
        cin >> n;

        cout << "Enter keys (as strings):\n";
        for (int i = 1; i <= n; i++)
            cin >> keys[i];

        cout << "Enter probabilities of successful search p[i] (i = 1 to n):\n";
        for (int i = 1; i <= n; i++)
            cin >> p[i];

        cout << "Enter probabilities of unsuccessful search q[i] (i = 0 to n):\n";
        for (int i = 0; i <= n; i++)
            cin >> q[i];
    }

    void build() {
        for (int i = 0; i <= n; i++) {
            cost[i][i] = q[i];
            weight[i][i] = q[i];
        }

        for (int l = 1; l <= n; l++) { // chain length
            for (int i = 0; i <= n - l; i++) {
                int j = i + l;
                cost[i][j] = 9999;
                weight[i][j] = weight[i][j - 1] + p[j] + q[j];

                for (int r = i + 1; r <= j; r++) {
                    float temp = cost[i][r - 1] + cost[r][j] + weight[i][j];
                    if (temp < cost[i][j]) {
                        cost[i][j] = temp;
                        root[i][j] = r;
                    }
                }
            }
        }

        cout << fixed << setprecision(2);
        cout << "\nMinimum Expected Search Cost: " << cost[0][n] << endl;
    }

    void printTree(int i, int j, int parent = -1, bool left = true) {
        if (i >= j) return;
        int r = root[i][j];
        if (parent == -1)
            cout << "Root: " << keys[r] << endl;
        else if (left)
            cout << "Left child of " << keys[parent] << ": " << keys[r] << endl;
        else
            cout << "Right child of " << keys[parent] << ": " << keys[r] << endl;

        printTree(i, r - 1, r, true);
        printTree(r, j, r, false);
    }
};

int main() {
    OBST t;
    t.input();
    t.build();
    t.printTree(0, t.n);
    return 0;
}
