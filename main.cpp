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

void printDiv() { cout << "________________________________________\n\n"; };

class Node {
public:
    Node(int nodeData) {
        data = nodeData;
    }
    Node *left, *right;
    int data;
};

class Tree {
public:

    Tree() = default;
    Tree(int data) {
        root = insert(root, data);
    }
    Node *contains(int data)   { return search(root, data); };
    void add(int data)         { root = insert(root, data); };
    void freeMemory()         { freeMemory(root); };
    void printTree()           { Print(root); };
    void printTree(Node *node) { Print(node); };

private:
    Node *root = nullptr;

    Node *insert(Node *node, int data) {

        if (!node) {                // Insert data
            node = new Node(data);
            cout << "Inserted new data: " << data << "\n\n";
        }
        else if (data < node->data) // Recurse left
            node->left  = insert(node->left, data);

        else if (data > node->data) // Recurse right
            node->right = insert(node->right, data);

        return node;
    }
    Node *search(Node *node, int target) {
        if (!node || target == node->data) return node;
        
        // Recurse left or right
        node = (target < node->data) ? node->left : node->right;
        return search(node, target);
    }
    void Print(Node *node) {
        try {
            if (!node) throw "Tree is empty";

            if (node->left)  Print(node->left);  // Recurse left
            cout << "Node Data: " << node->data << "\n";
            if (node->right) Print(node->right); // Recurse right
        }
        catch (const char *e) {
            cout << "[Exception Occurred] " << e << "\n";
        }
    }
    void freeMemory(Node *node) {
        if (!node) return;
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }
};
void BeginTests() {
    int  dataArr[] = {-1, 6, 7, 1, 9, -5, 4};

    printDiv();
    cout << "Adding data to the tree . . .\n\n";
    Tree tree(10);
    for (int data : dataArr) tree.add(data);

    printDiv();
    cout << "Printing data using in-order traversal . . .\n\n";
    tree.printTree();

    printDiv();
    cout << "Searching for data: 1-10 . . .\n\n";
    for (int target = 0; target <= 10; target++) {
        string found = tree.contains(target) ? "yes" : "no";
        cout << "Tree has " << target << ": " << found << "\n";
    }

    printDiv();
    cout << "Testing exception handling . . .\n\n";
    tree.printTree(nullptr);
    cout << "\nSuccess!\n";

    printDiv();
    cout << "Freeing memory . . .\n\n";
    tree.freeMemory();
}
int main() {

    BeginTests();
    
    printDiv();
    cout << "\nMemory usage: " << usedMem << " Bytes\n\n";
    printDiv();
    cout << "Tests completed!\n\n";

    return 0;
}