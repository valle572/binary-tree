#include <memory>
#include <iostream>
using namespace std;

// Global variable to keep track of memory in use
int usedMem = 0;

void* operator new(size_t size) {
    usedMem += size;
    cout << "[Allocating " << size << " bytes]\n";
    return malloc(size);
}

void operator delete(void* memPtr, size_t size) {
    usedMem -= size;
    cout << "[Freeing " << size << " bytes]\n";
    free(memPtr);
}

void PrintDivider() { cout << "________________________________________\n"; };

class Node {
public:
    Node(int nodeData) {
        data = nodeData;
    };
    Node *left  = nullptr;
    Node *right = nullptr;
    int data;
    ~Node() {};
};

class Tree {
public:

    Tree() = default;

    Tree(int data) {  // Tree with one node
        root = insertData(root, data);
    }

    void printTree()           { Print(root); };
    void printTree(Node *node) { Print(node); };
    void freeAllocatedData()   { freeAllocatedData(root); };
    void addData(int data)     { root = insertData(root, data); };
    Node *searchFor(int data)  { return searchData(root, data); };

    ~Tree() {};

private:
    Node *root = nullptr;

    Node *insertData(Node *node, int data) {

        if (node == nullptr) {        // Insert Data
            node = new Node(data);
            cout << "Inserted new data: " << data << "\n\n";
            return node;
        }
        if (data < node->data)       // Recurse left
            node->left  = insertData(node->left, data);

        if (data > node->data)      // Recurse right
            node->right = insertData(node->right, data);
        return node;
    }
    Node *searchData(Node *node, int data) {

        if (node == nullptr || data == node->data)
            return node;                          // Node is found or empty

        node = (data < node->data) ? node->left : node->right;
        return searchData(node, data);            // Recurse left or right
    }
    void Print(Node *node) {
        try {
            if (node == nullptr) throw "Tree is empty";

            if (node->left  != nullptr) Print(node->left);  // Recurse left
            cout << "Node Data: " << node->data << "\n";
            if (node->right != nullptr) Print(node->right); // Recurse Right
        }
        catch (const char *e) {					  // Exception is thrown
            cout << "[Exception occured] " << e << "\n";
        }
    }
    void freeAllocatedData(Node *node) {
        if (node == nullptr)
            return;

        freeAllocatedData(node->left);
        freeAllocatedData(node->right);
        delete node;
    }
};
void BeginTests() {

    int  data[] = {-1, 6, 7, 1, 9, -5, 4},
         arraySize   = sizeof(data) / sizeof(int),
         MAX_SEARCH_VAL = 10;      // for search loop

    PrintDivider();
    cout << "Adding data to the Tree . . .\n\n";

    Tree tree(10);         // Tree with one Node
    for (int i = 0; i < arraySize; i++)
        tree.addData(data[i]);

    PrintDivider();
    cout << "Printing data using In-Order Traversal . . .\n\n";

    tree.printTree();

    PrintDivider();
    cout << "Undergoing a series of searches . . .\n\n";

    for (int toFind = 5; toFind <= MAX_SEARCH_VAL; toFind++) {

        cout << "Looking for data: " << toFind << " . . .\n";
        bool found = tree.searchFor(toFind);

        if (found)
            cout << " [Success]  Found Node: " << toFind << "\n\n";
        else
            cout << "[Not Found] Looked for: " << toFind << "\n\n";
    }

    PrintDivider();
    cout << "Testing exception handling . . .\n\n";
    
    Node *testNode = nullptr;
    Tree testTree;

    testTree.printTree(testNode); // Nullptr

    cout << "\nException handling successful!\n\n";

    PrintDivider();
    cout << "Freeing Memory . . .\n\n";
    tree.freeAllocatedData();

}
int main() {

    BeginTests();
    
    PrintDivider();
    cout << "\nMemory Usage: " << usedMem << " Bytes\n\n";
    PrintDivider();
    cout << "Tests Completed!\n\n";

    return 0;
}