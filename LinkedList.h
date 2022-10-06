#ifndef PROJECT1_LINKEDLIST_H
#define PROJECT1_LINKEDLIST_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
// Used in later functions.
using namespace std;
using std::vector;


// Prototypes
template<typename T>
struct LinkedList {
    // Structure of a node and its connection the one next to it
    // This will be a doubly linked list.
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };
    Node *head;
    Node *tail;

// All prototypes that will be used to handle nodes.
    void PrintForward() const;

    void PrintReverse() const;

    void AddHead(const T &data);

    void AddTail(const T &data);

    void AddNodesHead(const T *data, unsigned int count);

    void AddNodesTail(const T *data, unsigned int count);

    unsigned int NodeCount() const;

    ~LinkedList();

    LinkedList();

    LinkedList(const LinkedList<T> &list);

    void FindAll(vector<Node *> &outData, const T &value) const;

    const Node *Find(const T &Data) const;

    Node *Find(const T &Data);

    const Node *GetNode(unsigned int index) const;

    Node *GetNode(unsigned int index);

    Node *Head();

    const Node *Head() const;

    Node *Tail();

    const Node *Tail() const;

    void PrintForwardRecursive(const Node *node) const;

    void PrintReverseRecursive(const Node *node) const;

    void InsertAfter(Node *node, const T &data);

    void InsertBefore(Node *node, const T &data);

    void InsertAt(const T &data, unsigned int index);

    bool RemoveHead();

    bool RemoveTail();

    unsigned int Remove(const T &data);

    bool RemoveAt(unsigned int index);

    void Clear();

    const T &operator[](unsigned int index) const;

    T &operator[](unsigned int index);

    bool operator==(const LinkedList<T> &rhs) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);
};

template<typename T>
bool LinkedList<T>::RemoveHead() {
    if (head == nullptr) {
        return false;
    } else if (head->next == nullptr) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return true;
    } else {
        Node *nextNode = head->next;
        nextNode->prev = nullptr;
        delete head;
        head = nextNode;
        return true;
    }
}

template<typename T>
bool LinkedList<T>::RemoveTail() {
    if (tail == nullptr) {
        return false;
    } else if (tail->prev == nullptr) {
        delete tail;
        head = nullptr;
        tail = nullptr;
        return true;
    } else {
        Node *prevNode = tail->prev;
        prevNode->next = nullptr;
        delete tail;
        tail = prevNode;
        return true;
    }
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    if (index >= NodeCount()) {
        return false;
    }
    if (index == 0) {
        if (head == nullptr) {
            return false;
        } else {
            Node *nextNode = head->next;
            nextNode->prev = nullptr;
            delete head;
            head = nextNode;
            return true;
        }
    } else if (index == NodeCount() - 1) {
        if (tail == nullptr) {
            return false;
        } else {
            Node *prevNode = tail->prev;
            prevNode->next = nullptr;
            delete tail;
            tail = prevNode;
            return true;
        }
    } else {
        Node *currentNodeFront = head;
        Node *currentNodeBack = head;
        Node *currentNode = head;
        for (unsigned int i = 0; i < index + 1; i++) {
            currentNodeFront = currentNodeFront->next;
        }
        for (unsigned int i = 0; i < index; i++) {
            currentNode = currentNode->next;
        }
        for (unsigned int i = 0; i < index - 1; i++) {
            currentNodeBack = currentNodeBack->next;
        }
        delete currentNode;
        currentNodeBack->next = currentNodeFront;
        currentNodeFront->prev = currentNodeBack;
        return true;
    }
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T &data) {
    unsigned int count = 0;
    unsigned int index = 0;
    Node *currentNode = head;

    while (currentNode->next != nullptr) {
        if (currentNode->data == data) {
            if (index == 0) {
                if (currentNode == nullptr) {
                    return false;
                } else if (head->next == nullptr) {
                    delete head;
                    head = nullptr;
                    tail = nullptr;
                    return 1;
                } else {
                    currentNode = head->next;
                    currentNode->prev = nullptr;
                    delete head;
                    head = currentNode;
                }
            } else if (index == NodeCount() - 1) {
                if (tail->prev == nullptr) {
                    delete tail;
                    currentNode = nullptr;
                    head = nullptr;
                    tail = nullptr;
                } else {
                    currentNode = tail->prev;
                    currentNode->next = nullptr;
                    delete tail;
                    tail = currentNode;

                }
            } else {
                Node *currentNodeFront = currentNode->next;
                Node *currentNodeBack = currentNode->prev;
                currentNodeBack->next = currentNodeFront;
                currentNodeFront->prev = currentNodeBack;
                delete currentNode;
                currentNode = head;
                for(unsigned int i = 0; i < index; i++) {
                    currentNode = currentNode->next;
                }
            }
            count++;
        } else {
            currentNode = currentNode->next;
            index++;
        }

    }
    return count;
}


// Clear the linked list. I used the same functions as the destructor.
template<typename T>
void LinkedList<T>::Clear() {
    Node *nextNode = nullptr;
    while (head != nullptr) {
        nextNode = head->next;
        delete head;
        head = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node *node) const {
    if (node->next != nullptr) {
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    } else {
        cout << node->data << endl;
    }
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node *node) const {
    if (node->prev != nullptr) {
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    } else {
        cout << node->data << endl;
    }
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const {
    Node *currentNode1 = head;
    Node *currentNode2 = rhs.head;
    if (currentNode1 == currentNode2) {
        return true;
    }
    while (currentNode2 != nullptr) {
        currentNode1 = currentNode1->next;
        currentNode2 = currentNode2->next;
        if (currentNode2 == currentNode1) {
            return true;
        }
    }
    return false;
}

template<typename T>
void LinkedList<T>::InsertBefore(Node *node, const T &data) {
    Node *newNode = new Node;
    Node *nodeBefore = node->prev;
    newNode->data = data;
    newNode->next = node;
    node->prev = newNode;
    nodeBefore->next = newNode;
    newNode->prev = nodeBefore;
}

template<typename T>
void LinkedList<T>::InsertAfter(Node *node, const T &data) {
    Node *newNode = new Node;
    Node *nodeAfter = node->next;
    newNode->data = data;
    newNode->next = nodeAfter;
    nodeAfter->prev = newNode;
    node->next = newNode;
    newNode->prev = node;
}

template<typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) {
    if (index > NodeCount()) {
        throw out_of_range("Index Invalid");
    }

    Node *newNode = new Node();
    newNode->data = data;

    if (index == 0) {
        Node *currentNode = head;
        newNode->prev = nullptr;
        newNode->next = currentNode;
        head = newNode;
        currentNode->prev = newNode;
    } else if (index == NodeCount()) {
        Node *currentNode = tail;
        newNode->prev = currentNode;
        newNode->next = nullptr;
        tail = newNode;
        currentNode->next = newNode;
    } else {
        Node *currentNodeFront = head;
        Node *currentNodeBack = head;
        for (unsigned int i = 0; i < index; i++) {
            currentNodeFront = currentNodeFront->next;
        }
        for (unsigned int i = 0; i < index - 1; i++) {
            currentNodeBack = currentNodeBack->next;
        }
        currentNodeBack->next = newNode;
        newNode->prev = currentNodeBack;
        newNode->next = currentNodeFront;
        currentNodeFront->prev = newNode;
    }
}


// Copy Assignment
template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    Clear();
    Node *currentNode1 = nullptr;
    Node *currentNode2 = nullptr;
    head = new Node;
    head->data = rhs.head->data;
    currentNode1 = head;
    currentNode2 = rhs.head;
    currentNode2 = currentNode2->next;
    while (currentNode2 != nullptr) {

        currentNode1->next = new Node;
        currentNode1 = currentNode1->next;
        currentNode1->data = currentNode2->data;
        currentNode2 = currentNode2->next;
    }
    currentNode1->next = nullptr;
    return *this;
}


// Copy Operator
template<typename T>
LinkedList<T>::LinkedList(
        const LinkedList<T> &list) {
    Node *currentNode1 = nullptr;
    Node *currentNode2 = list.head;
    head = new Node;
    head->data = list.head->data;
    currentNode1 = head;
    currentNode2 = currentNode2->next;
    while (currentNode2 != nullptr) {
        currentNode1->next = new Node;
        currentNode1 = currentNode1->next;
        currentNode1->data = currentNode2->data;
        currentNode2 = currentNode2->next;
    }
}

// Overloaded subscript operator
template<typename T>
T &LinkedList<T>::operator[](unsigned int index) {
    if (index >= NodeCount()) {
        throw out_of_range("Index Invalid");
    }
    Node *currentNode = head;
    for (unsigned int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->data;

}

// Overloaded subscript operator with constant
template<typename T>
const T &LinkedList<T>::operator[](unsigned int index) const {
    if (index >= NodeCount()) {
        throw out_of_range("Index Invalid");
    }
    Node *currentNode = head;
    for (unsigned int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->data;
}

// Find nodes that have a value to it.
template<typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T &value) const {
    Node *currentNode = head;
    while (currentNode != nullptr) {
        if (currentNode->data == value) {
            outData.push_back(currentNode);
        }
        currentNode = currentNode->next;
    }
}

// Find the first node with said data
template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &Data) {
    Node *currentNode = head;
    while (currentNode != nullptr) {
        if (currentNode->data == Data) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }
    return nullptr;
}

// Find the first node with said data but that is now a constant
template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Find(const T &Data) const {
    Node *currentNode = head;
    while (currentNode != nullptr) {
        if (currentNode->data == Data) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }
    return nullptr;
}

// Get the data of a specific node
template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) {
    if (index >= NodeCount()) {
        throw out_of_range("Index Invalid");
    }
    Node *currentNode = head;
    for (unsigned int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

// Get the data of a specific node but with constant
template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) const {
    if (index >= NodeCount()) {
        throw out_of_range("Invalid Index");
    }
    Node *currentNode = head;

    for (unsigned int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

// Returns head of the linked list
template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Head() {
    return head;
}

// Returns head of the linked list but is constant
template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Head() const {
    return head;
}

// Returns tail of the linked list
template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Tail() {
    return tail;
}

// Returns tail of the linked list but is constant
template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Tail() const {
    return tail;
}


// Default constructor
template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

// Destructor
template<typename T>
LinkedList<T>::~LinkedList<T>() {
    Node *nextNode = nullptr;
    while (head != nullptr) {
        nextNode = head->next;
        delete head;
        head = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

// Adding a new node head
template<typename T>
void LinkedList<T>::AddHead(const T &data) {
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = head;
    newNode->prev = nullptr;
    if (tail == nullptr) {
        tail = newNode;
    }
    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;
}

// Adding a new node tail
template<typename T>
void LinkedList<T>::AddTail(const T &data) {
    Node *newNode = new Node;
    newNode->data = data;
    newNode->prev = tail;
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
    }
    if (tail != nullptr) {
        tail->next = newNode;
    }
    tail = newNode;
}

// Adding multiple node heads from an array
template<typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count) {
    for (unsigned int i = count; i > 0; i--) {
        AddHead(data[i - 1]);
    }
}

// Adding multiple node heads from an array
template<typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        AddTail(data[i]);
    }
}

// Gives the total node count that are in the linked list
template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
    Node *currentNode1 = head;
    Node *currentNode2 = tail;
    int count1 = 0;
    int count2 = 0;
    while (currentNode1 != nullptr) {
        count1++;
        currentNode1 = currentNode1->next;
    }
    while (currentNode2 != nullptr) {
        count2++;
        currentNode2 = currentNode2->prev;
    }
    if (count1 > count2) {
        return count1;
    } else if (count2 > count1) {
        return count2;
    } else {
        return count1;
    }
}

// Prints out the list of nodes from head to tail
template<typename T>
void LinkedList<T>::PrintForward() const {
    Node *currentNode = head;
    while (currentNode != nullptr) {
        cout << currentNode->data << endl;
        currentNode = currentNode->next;
    }
}

// Prints out the list of nodes from tail to head
template<typename T>
void LinkedList<T>::PrintReverse() const {
    Node *current2Node = tail;
    while (current2Node != nullptr) {
        cout << current2Node->data << endl;
        current2Node = current2Node->prev;
    }
}

#endif //PROJECT1_LINKEDLIST_H