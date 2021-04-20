#include <iostream>

template <typename T>
struct LinkedListNode {
    T info;
    LinkedListNode<T>* nextNode;
};

template <typename T>
LinkedListNode<T>* SearchPos(LinkedListNode<T>* list, int pos) {
    LinkedListNode<T>* node = list;

    while (node && pos) {
        node = node->nextNode;
        pos--;
    }

    return node;
}

template <typename T>
LinkedListNode<T>* SearchValue(LinkedListNode<T>* list, T value) {
    LinkedListNode<T>* node = list;

    while (node && node->info != value) {
        node = node->nextNode;
    }

    return node;
}

template <typename T>
void AddNodeStart(LinkedListNode<T>* &cap, T info) {
    LinkedListNode<T>* node = new LinkedListNode<T>;
    node->info = info;
    node->nextNode = cap;
    cap = node;
}

template <typename T>
void AddNodeEnd(LinkedListNode<T>* &cap, T info) {
    LinkedListNode<T>* node = new LinkedListNode<T>;
    node->info = info;
    node->nextNode = NULL;

    if (cap) {
        LinkedListNode<T>* temp = cap;
        while (temp->nextNode) 
            temp = temp->nextNode;

        temp->nextNode = node;
    } else {
        cap = node;
    }
}

template <typename T>
void AddAtPosition(LinkedListNode<T>* &cap, int pos, T info) {
    if (pos == 0) {
        AddNodeStart(cap, info);
        return;
    }

    LinkedListNode<T>* prev = SearchPos(cap, pos - 1);

    if (prev == NULL) {
        AddNodeEnd(cap, info);
        return;
    }

    LinkedListNode<T>* next = prev->nextNode;

    LinkedListNode<T>* node = NULL;
    AddNodeStart(node, info);

    prev->nextNode = node;
    node->nextNode = next;
}


template <typename T>
void RemoveNextNode(LinkedListNode<T>* prev) {
    LinkedListNode<T>* curr = prev->nextNode;

    prev->nextNode = prev->nextNode->nextNode;
    delete curr;
}

template <typename T>
void RemoveHead(LinkedListNode<T>* &list) {
    if (list == NULL) 
        return;
    
    LinkedListNode<T>* toRemove = list;
    list = list->nextNode;

    delete toRemove;
}

template <typename T>
void RemoveAtPos(LinkedListNode<T>* &list, int pos) {
    if (list == NULL) 
        return;
    
    if (pos == 0) {
        RemoveHead(list);
        return;
    }


    LinkedListNode<T>* pred = SearchPos(list, pos-1);
    RemoveNextNode(pred);
}

template <typename T>
void RemoveValue(LinkedListNode<T>* &list, T value) {
    if (list == NULL)
        return;
    
    if (list->info == value) {
        RemoveHead(list);
        return;
    }

    LinkedListNode<T>* node = list;

    while (node->nextNode != NULL && node->nextNode->info != value)
        node = node->nextNode;
    
    if (node->nextNode != NULL) {
        RemoveNextNode(node);
    }

    return;
}

template <typename T>
void PrintList(const LinkedListNode<T> *list) {
    auto node = list;

    while (node) {
        std::cout << node->info << '\n';
        node = node->nextNode;
    }
}

// int main() {
//     LinkedListNode<int> *list = NULL;

//     for (int i = 1; i < 6; i++)
//         AddNodeEnd(list, i);
    
//     RemoveAtPos(list, 0);

//     AddAtPosition(list, 7, 7);

//     PrintList(list);
// }