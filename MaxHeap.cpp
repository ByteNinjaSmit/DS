#include <iostream>
using namespace std;

class MaxHeap {
    int arr[100];
    int size;

public:
    MaxHeap() {
        size = 0;
    }

    void insert(int val) {
        int i = ++size;
        while (i > 1 && val > arr[i / 2]) {
            arr[i] = arr[i / 2];
            i /= 2;
        }
        arr[i] = val;
    }

    void display() {
        for (int i = 1; i <= size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    void heapify(int i) {
        int largest = i;
        int l = 2 * i, r = 2 * i + 1;

        if (l <= size && arr[l] > arr[largest]) largest = l;
        if (r <= size && arr[r] > arr[largest]) largest = r;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(largest);
        }
    }

    int deleteMax() {
        if (size == 0) return -1;
        int maxVal = arr[1];
        arr[1] = arr[size--];
        heapify(1);
        return maxVal;
    }
};

int main() {
    MaxHeap h;
    h.insert(50);
    h.insert(30);
    h.insert(20);
    h.insert(40);
    h.insert(60);
    h.display();
    cout << "Deleted max: " << h.deleteMax() << endl;
    h.display();
    return 0;
}
