#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

class OBST
{
private:
    string keys[10];
    float p[10];      // probabilities of successful search
    float q[11];      // probabilities of unsuccessful search
    float e[11][11];  // expected cost
    float w[11][11];  // weight sum
    int root[11][11]; // root table
    int n;

public:
    // Parameterized constructor
    OBST(string k[], float prob[], float unprob[], int size)
    {
        n = size;
        for (int i = 0; i < n; ++i)
        {
            keys[i] = k[i];
            p[i] = prob[i];
        }
        for (int i = 0; i <= n; ++i)
        {
            q[i] = unprob[i];
        }

        // Initialize matrices
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                e[i][j] = 0;
                w[i][j] = 0;
                root[i][j] = -1;
            }
        }

        buildOBST(); // Automatically build the OBST
    }
    void buildOBST()
    {
        for (int i = 0; i <= n; ++i)
        {
            e[i][i] = q[i];
            w[i][i] = q[i];
        }

        for (int l = 1; l <= n; ++l)
        {
            for (int i = 0; i <= n - l; ++i)
            {
                int j = i + l;
                e[i][j] = numeric_limits<float>::max();
                w[i][j] = w[i][j - 1] + p[j - 1] + q[j];
                for (int r = i + 1; r <= j; ++r)
                {
                    float t = e[i][r - 1] + e[r][j] + w[i][j];
                    if (t < e[i][j])
                    {
                        e[i][j] = t;
                        root[i][j] = r;
                    }
                }
            }
        }
    }

    void printTree(int i, int j, string parent, bool isLeft)
    {
        if (i >= j)
            return;

        int r = root[i][j];
        string node = keys[r - 1];

        if (parent == "")
        {
            cout << "Root: " << node << endl;
        }
        else if (isLeft)
        {
            cout << "Left child of " << parent << ": " << node << endl;
        }
        else
        {
            cout << "Right child of " << parent << ": " << node << endl;
        }

        printTree(i, r - 1, node, true);
        printTree(r, j, node, false);
    }

    void displayOBST()
    {
        cout << "\nOptimal Binary Search Tree Structure:\n";
        printTree(0, n, "", false);
        cout << "\nMinimum Expected Search Cost: " << e[0][n] << endl;
    }

    void displayTables()
    {
        cout << "\nDiagonal-wise Table (Cij, Wij, Rij):\n" << endl;
    
        for (int l = 0; l <= n; ++l) // l is the diagonal level
        {
            for (int i = 0; i <= n - l; ++i)
            {
                int j = i + l;
    
                // Print Cij
                cout << "C" << i << j << "=" << fixed << setprecision(2) << e[i][j] << "  ";
            }
            cout << endl;
    
            for (int i = 0; i <= n - l; ++i)
            {
                int j = i + l;
    
                // Print Wij
                cout << "W" << i << j << "=" << fixed << setprecision(2) << w[i][j] << "  ";
            }
            cout << endl;
    
            for (int i = 0; i <= n - l; ++i)
            {
                int j = i + l;
    
                // Print Rij
                cout << "R" << i << j << "=";
                if (root[i][j] == -1)
                    cout << "--";
                else
                    cout << root[i][j];
                cout << "    ";
            }
    
            cout << "\n\n"; // Gap between diagonals
        }
    }
    
};

int main()
{
    string keys[] = {"flour", "rice", "sugar", "tea"};
    float p[] = {0.1, 0.2, 0.3, 0.1};
    float q[] = {0.05, 0.1, 0.05, 0.05, 0.05};

    OBST tree(keys, p, q, 4);
    tree.displayOBST();
    tree.displayTables();

    return 0;
}
