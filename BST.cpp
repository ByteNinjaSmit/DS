#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const char separator = ' ';
const int nameWidth = 15;
const int numWidth = 8;

template <typename T>
void printElement(T t, const int &width)
{
    cout << left << setw(width) << setfill(separator) << t;
}

class Student
{
public:
    int id, cet;
    string name;
    Student *LC, *RC;

    Student() : LC(NULL), RC(NULL) {}
    void create();
    void insert(Student *root, Student *next);
    void preOrder(Student *root);
    void search(Student *root, int idS);
    int height(Student *root);
    void displayIIT(Student *root);    // Display of All childs of root right side
    void displayNonIIT(Student *root); // Display of All childs of root right side
    void displayPostOrderNonRecursive(Student *root);
    void displayTopper(Student *root);  // Displaying Topper means most right node
    void displayMin(Student *root);
    

};

Student *root;

void Student::create()
{
    Student *newNode = new Student();
    cout << "Enter Name: ";
    cin >> newNode->name;
    cout << "Enter ID: ";
    cin >> newNode->id;
    cout << "Enter CET: ";
    cin >> newNode->cet;
    newNode->LC = NULL;
    newNode->RC = NULL;
    root = newNode;
    int choice = 0;
    do
    {
        cout << "Do you want to add another student? (1/0): ";
        cin >> choice;
        if (choice == 1)
        {
            Student *nNode = new Student();
            cout << "Enter Name: ";
            cin >> nNode->name;
            cout << "Enter ID: ";
            cin >> nNode->id;
            cout << "Enter CET: ";
            cin >> nNode->cet;
            nNode->LC = NULL;
            nNode->RC = NULL;
            insert(root, nNode);
        }
    } while (choice == 1);
}
void Student::insert(Student *root, Student *nextNode)
{
    if (root->cet > nextNode->cet)
    {
        if (root->LC == NULL)
        {
            root->LC = nextNode;
        }
        else
        {
            insert(root->LC, nextNode);
        }
    }
    else if (root->cet < nextNode->cet)
    {
        if (root->RC == NULL)
        {
            root->RC = nextNode;
        }
        else
        {
            insert(root->RC, nextNode);
        }
    }
}
void Student::preOrder(Student *root)
{
    if (root == NULL)
    {
        return;
    }
    printElement(root->id, numWidth);
    printElement(root->name, nameWidth);
    printElement(root->cet, numWidth);
    cout << endl;
    preOrder(root->LC);
    preOrder(root->RC);
}
// Flag for Search Pupose
int flag = 0;
void Student::search(Student *root, int idS)
{
    if (root == NULL || flag == 1)
    {
        return;
    }
    if (root->id == idS)
    {
        printElement(root->id, numWidth);
        printElement(root->name, nameWidth);
        printElement(root->cet, numWidth);
        cout << endl;
        flag = 1;
    }
    search(root->LC, idS);
    search(root->RC, idS);
}

int Student::height(Student *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int LHT = height(root->LC);
    int RHT = height(root->RC);
    return max(LHT, RHT) + 1;
}
void Student::displayIIT(Student *root)
{
    if (root == NULL)
    {
        return;
    }
    printElement(root->id, numWidth);
    printElement(root->name, nameWidth);
    printElement(root->cet, numWidth);
    cout << endl;
    preOrder(root->LC);
    preOrder(root->RC);
}

void Student::displayNonIIT(Student *root)
{
    if (root == NULL)
    {
        return;
    }
    printElement(root->id, numWidth);
    printElement(root->name, nameWidth);
    printElement(root->cet, numWidth);
    cout << endl;
    preOrder(root->LC);
    preOrder(root->RC);
}

// POST ORDER NON Recursive
void Student::displayPostOrderNonRecursive(Student *root)
{
    if (root == NULL)
    {
        return;
    }

    Student *stk[100]; // Stack for traversal
    Student *arr[100];
    Student *temp;
    int i = 0;
    int top = -1;
    temp = root;
    if (root != NULL)
    {
        do
        {
            while (temp != NULL)
            {
                arr[i] = temp;
                i++;
                top++;
                stk[top] = temp;
                temp = temp->RC;
            }
            if (top != -1)
            {
                temp = stk[top];
                temp = temp->LC;
                top--;
            }
        } while (top != 1 || temp != NULL);

        // display inreverse array
        for (int j = i - 1; j >= 0; j--)
        {
            printElement(arr[j]->id, numWidth);
            printElement(arr[j]->name, nameWidth);
            printElement(arr[j]->cet, numWidth);
            cout << endl;
        }
    }
}

// Showing Toppen Of the CET Score

void Student::displayTopper(Student *root)
{
    if (root == NULL)
    {
        return;
    }
    // Most Big Node i think rightest most
    Student *temp = root;
    while (temp->RC != NULL)
    {
        temp = temp->RC;
    }
    cout << "Topper Name: " << temp->name << endl;
    cout << "Topper Score: " << temp->cet << endl;
}

// Showing The Minimum
void Student::displayMin(Student *root)
{
    if (root == NULL)
    {
        return;
    }
    // Most Big Node i think rightest most
    Student *temp = root;
    while (temp->LC != NULL)
    {
        temp = temp->LC;
    }
    cout << "Topper Name: " << temp->name << endl;
    cout << "Topper Score: " << temp->cet << endl;
}

int main()
{
    int ch = 0;
    Student SMS;
    while (ch != 9)
    {
        cout << "1. Create\n2. Display\n3. Search\n4. Height\n5. Display IITian\n6. Display Non IITians\n7. PostOrder Non-Recursive\n8. Display CET Topper \n9. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            SMS.create();
            break;
        case 2:
            printElement("ID", numWidth);
            printElement("Name", nameWidth);
            printElement("CET Score", numWidth);
            cout << endl;
            SMS.preOrder(root);
            break;
        case 3:
        {
            int id;
            cout << "Enter id to be Search: ";
            cin >> id;
            flag = 0;
            SMS.search(root, id);
            if (flag == 0)
            {
                cout << "No Data Found" << endl;
            }
            break;
        }
        case 4:
        {
            cout << "Height Of Tree is: " << SMS.height(root) << endl;
            break;
        }
        case 5:
        {
            cout << "List Of ALL IITians" << endl;
            printElement("ID", numWidth);
            printElement("Name", nameWidth);
            printElement("CET Score", numWidth);
            cout << endl;
            SMS.preOrder(root->RC);
            break;
        }
        case 6:
        {
            cout << "List Of ALL NON IITians" << endl;
            printElement("ID", numWidth);
            printElement("Name", nameWidth);
            printElement("CET Score", numWidth);
            cout << endl;
            SMS.preOrder(root->LC);
            break;
        }
        case 7:
        {
            cout << "List Of ALL Students" << endl;
            printElement("ID", numWidth);
            printElement("Name", nameWidth);
            printElement("CET Score", numWidth);
            cout << endl;
            SMS.displayPostOrderNonRecursive(root);
            break;
        }
        case 8:{
            cout << "Topper Student" << endl;
            SMS.displayTopper(root);
            break;
        }
        case 9:
            cout << "Exiting..........." << endl;
            break;
        default:
            cout << "Enter Correct Choice!!!" << endl;
            break;
        }
    }
    return 0;
}