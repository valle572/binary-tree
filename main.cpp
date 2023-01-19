#include <memory>
#include <iostream>


// Global variable to keep track of memory in use
int usedMem = 0;


void* operator new(size_t size) {
    usedMem += size;
    std::cout << "[Allocating " << size << " bytes]\n";
    return malloc(size);
}
void operator delete(void* memPtr, size_t size) noexcept {
    usedMem -= size;
    std::cout << "[Freeing " << size << " bytes]\n";
    free(memPtr);
}
void printDiv() {
    std::cout << "\n======================================================\n";
};


class Node {
public:
    Node(int nodeData) {
        data = nodeData;
    }
    Node *leftPtr, *rightPtr;
    int data;
};


class Tree {
public:

    Tree() = default;
    Tree(int data) {
        rootPtr = insert(rootPtr, data);
    }
    Node *contains(int data)      { return search(rootPtr, data); };
    void add(int data)            { rootPtr = insert(rootPtr, data); };
    void clearTree()              { deleteNode(rootPtr); };
    void printTree()              { print(rootPtr); };
    void printTree(Node *nodePtr) { print(nodePtr); };

private:
    Node *rootPtr = nullptr;

    Node *insert(Node *nodePtr, int data) {

        if (!nodePtr) {                // Insert data
            nodePtr = new Node(data);
            std::cout << "Inserted new data: " << data << "\n\n";
        }
        else if (data < nodePtr->data) // Recurse left
            nodePtr->leftPtr  = insert(nodePtr->leftPtr, data);

        else if (data > nodePtr->data) // Recurse right
            nodePtr->rightPtr = insert(nodePtr->rightPtr, data);

        return nodePtr;
    }
    Node *search(Node *nodePtr, int num) {
        if (!nodePtr || num == nodePtr->data) return nodePtr;
        
        // Recurse left or right
        nodePtr = (num < nodePtr->data) ? nodePtr->leftPtr : nodePtr->rightPtr;
        return search(nodePtr, num);
    }
    void print(Node *nodePtr) {
        try {
            if (!nodePtr) throw "Tree is empty";

            if (nodePtr->leftPtr)  print(nodePtr->leftPtr);  // Recurse left
            std::cout << "Node Data: " << nodePtr->data << "\n";
            if (nodePtr->rightPtr) print(nodePtr->rightPtr); // Recurse right
        }
        catch (const char *e) {
            std::cout << "[Exception Occurred] " << e << "\n";
        }
    }
    void deleteNode(Node *nodePtr) {
        if (!nodePtr) return;
        deleteNode(nodePtr->leftPtr);
        deleteNode(nodePtr->rightPtr);
        delete nodePtr;
    }
};


void BeginTests() {
    int  dataArr[] = {-1, 6, 7, 1, 9, -5, 4};

    printDiv();
    std::cout << "Adding data to the tree . . .\n\n";
    Tree tree(10);
    for (int data : dataArr) tree.add(data);

    printDiv();
    std::cout << "Printing data using in-order traversal . . .\n\n";
    tree.printTree();

    printDiv();
    std::cout << "Searching for data: 0-9 . . .\n\n";
    for (int target = 0; target < 10; target++) {
        std::string found = tree.contains(target) ? "yes" : "no";
        std::cout << "Tree has " << target << ": " << found << "\n";
    }

    printDiv();
    std::cout << "Testing exception handling . . .\n\n";
    tree.printTree(nullptr);
    std::cout << "\nSuccess!\n";

    printDiv();
    std::cout << "Freeing memory . . .\n\n";
    tree.clearTree();
}


int main() {

    BeginTests();
    
    printDiv();
    std::cout << "\nMemory usage: " << usedMem << " bytes\n\n";
    printDiv();
    std::cout << "Tests completed!\n\n";

    return 0;
}