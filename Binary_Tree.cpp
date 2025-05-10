#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Student {
    int id;
    string name;
    Student *LC, *RC;

public:
    Student() : LC(NULL), RC(NULL) {}
    void create();
    void insert(Student *root, Student *next);
    void display(Student *root);
    void displayInorderNonRecursive(Student *root);
    void leafNode(Student *root);
    void internalNode(Student *root);
    int height(Student *root);
    void mirror(Student *root);
    void search(Student *root, int searchId);
};

Student *root = nullptr;

void Student::create() {
    int ch;
    cout << "Enter Student ID: ";
    root = new Student;
    cin >> root->id;
    cout << "Enter Student Name: ";
    cin >> root->name;

    root->LC = root->RC = nullptr;

    do {
        cout << "Do you want to add another Student? (1/0): ";
        cin >> ch;
        if (ch == 1) {
            Student *new_node = new Student;
            cout << "Enter Student ID: ";
            cin >> new_node->id;
            cout << "Enter Student Name: ";
            cin >> new_node->name;
            new_node->LC = new_node->RC = nullptr;
            insert(root, new_node);
        }
    } while (ch != 0);
}

void Student::insert(Student *root, Student *next) {
    char side;
    cout << "Which side of " << root->id << " do you want to insert? (L/R): ";
    cin >> side;

    if (side == 'L' || side == 'l') {
        if (root->LC == nullptr) {
            root->LC = next;
            cout << "Student info added successfully!\n";
        } else {
            insert(root->LC, next);
        }
    } else if (side == 'R' || side == 'r') {
        if (root->RC == nullptr) {
            root->RC = next;
            cout << "Student info added successfully!\n";
        } else {
            insert(root->RC, next);
        }
    } else {
        cout << "Invalid choice. Please enter L or R.\n";
    }
}

void Student::display(Student *root) {
    if (root == nullptr) return;
    display(root->LC);
    cout << "ID: " << root->id << " Name: " << root->name << endl;
    display(root->RC);
}

void Student::displayInorderNonRecursive(Student *root) {
    if (!root) return;

    stack<Student *> s;
    Student *current = root;

    while (!s.empty() || current != nullptr) {
        while (current != nullptr) { 
            s.push(current);
            current = current->LC;
        }
        current = s.top();
        s.pop();
        cout << "ID: " << current->id << " Name: " << current->name << endl;
        current = current->RC;
    }
}

void Student::leafNode(Student *root) {
    if (root == nullptr) return;
    if (!root->LC && !root->RC) {
        cout << "Leaf Node - ID: " << root->id << " Name: " << root->name << endl;
    }
    leafNode(root->LC);
    leafNode(root->RC);
}

void Student::internalNode(Student *root) {
    if (root == nullptr) return;
    if (root->LC || root->RC) {
        cout << "Internal Node - ID: " << root->id << " Name: " << root->name << endl;
    }
    internalNode(root->LC);
    internalNode(root->RC);
}

int Student::height(Student *root) {
    if (root == nullptr) return 0;
    int leftHeight = height(root->LC);
    int rightHeight = height(root->RC);
    return max(leftHeight, rightHeight) + 1;
}

void Student::mirror(Student *root) {
    if (root == nullptr) return; 
    swap(root->LC, root->RC);
    mirror(root->LC);
    mirror(root->RC);
}

void Student::search(Student *root,int searchId){
    if(root ==nullptr) return;
    search(root->LC,searchId);
    if(root->id == searchId){
        cout << "ID: " << root->id << " Name: " << root->name << endl;
        return;
    }
    search(root->RC,searchId);
}

int main() {
    int ch;
    Student tree;

    do {
        cout << "\nBinary Tree Operations\n";
        cout << "1. Create\n2. Display (Inorder)\n3. Height of the Tree\n4. Mirror the Tree\n5. Display Leaf Nodes\n6. Display Internal Nodes\n7. Display Inorder Traversal (Non-recursive)\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            tree.create();
            break;
        case 2:
            tree.display(root);
            break;
        case 3:
            cout << "Height of the tree: " << tree.height(root) << endl;
            break;
        case 4:
            tree.mirror(root);
            cout << "Tree mirrored successfully.\n";
            break;
        case 5:
            tree.leafNode(root);
            break;
        case 6:
            tree.internalNode(root);
            break;
        case 7:
            tree.displayInorderNonRecursive(root);
            break;
        case 8:{
            int temp;
            cout<<"Enter id To be Search: ";
            cin>>temp;
            tree.search(root,temp);
            break;  
        };
        case 9:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
    } while (ch != 9);

    return 0;
}
