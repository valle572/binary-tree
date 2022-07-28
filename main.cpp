#include <memory>
#include <iostream>
using namespace std;

int usedMem = 0; // Global Memory Tracker

void* operator new(size_t size) {
    
    usedMem += size;
    cout << "[Allocating " << size << " bytes]\n";
    return malloc(size);
}

void operator delete(void* mem, size_t size) {

    usedMem -= size;
    cout << "[Freeing " << size << " bytes]\n";
    free(mem);
}

// Prints message specifying data being inserted
void addMsg(int data) { cout << "Attempting to add: " << data << "\n"; };
void divider() { cout << "________________________________________\n"; };

class Node {
public:
    Node(int nodeData) {
        data = nodeData;
    };
    Node *left         = nullptr;
    Node *right        = nullptr;
    int data;
    ~Node() {};
};

class Tree {
public:

    Tree() = default;

    Tree(int data) {  // Tree with one node
        root = Insert(root, data);
    }

    void PrintTree()           { Print(root); };
    void PrintTree(Node *node) { Print(node); };
    void cleanTree()           { cleanTree(root); };
    void Add(int data)         { root = Insert(root, data); };
    Node *Find(int data)       { return Search(root, data); };

    ~Tree() {};

private:
    Node *root = nullptr;

    Node *Insert(Node *node, int data) {

        if (node == nullptr) {        // Insert Data
            node = new Node(data);
            addMsg(data);
            cout << "Inserted new data: " << data << "\n\n";
            return node;
        }
        if (data < node->data)       // Recurse left
            node->left  = Insert(node->left, data);

        if (data > node->data)      // Recurse right
            node->right = Insert(node->right, data);
        return node;
    }
    Node *Search(Node *node, int data) {

        if (node == nullptr || data == node->data)
            return node;                          // Node is found or empty

        node = (data < node->data) ? node->left : node->right;
        return Search(node, data);                // Recurse left or right
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
    void cleanTree(Node *node) {
        if (node == nullptr)
            return;

        cleanTree(node->left);
        cleanTree(node->right);
        delete node;
    }
};
void beginTests() {

    int  data[] = {-1, 6, 7, 1, 9, -5, 4},
         size   = sizeof(data) / sizeof(int),
         maxVal = 10;      // for search loop

    divider();
    cout << "Adding data to the Tree . . .\n\n";

    Tree tree(10);         // Tree with one Node
    for (int i = 0; i < size; i++)
        tree.Add(data[i]);

    divider();
    cout << "Printing data using In-Order Traversal . . .\n\n";

    tree.PrintTree();

    divider();
    cout << "Undergoing a series of searches . . .\n\n";

    for (int toFind = 5; toFind <= maxVal; toFind++) {

        cout << "Looking for data: " << toFind << " . . .\n";
        bool found = tree.Find(toFind);

        if (found)
            cout << " [Success]  Found Node: " << toFind << "\n\n";
        else
            cout << "[Not Found] Looked for: " << toFind << "\n\n";
    }

    divider();
    cout << "Testing exception handling . . .\n\n";
    
    Node *testNode = nullptr;
    Tree testTree;

    testTree.PrintTree(testNode); // Nullptr

    cout << "\nException handling successful!\n\n";

    divider();
    cout << "Freeing Memory . . .\n\n";
    tree.cleanTree();

}
int main() {

    beginTests();
    
    divider();
    cout << "\nMemory Usage: " << usedMem << " Bytes\n\n";
    divider();
    cout << "Tests Completed!\n\n";

    return 0;
}