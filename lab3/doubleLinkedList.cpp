#include <iostream>

template <typename T>
struct DoubleLinkedListNode {
    T info;
    DoubleLinkedListNode<T>* nextNode;
    DoubleLinkedListNode<T>* prevNode;
};

template <typename T>
DoubleLinkedListNode<T>* SearchPos(DoubleLinkedListNode<T>* list, int pos) {
    DoubleLinkedListNode<T>* node = list;

    if (pos >= 0) {
        while (node && pos) {
            node = node->nextNode;
            pos--;
        }
    } else {
        pos = -pos;
        while (node && pos) {
            node = node->prevNode;
            pos--;
        }
    }

    return node;
}

template <typename T>
DoubleLinkedListNode<T>* SearchValue(DoubleLinkedListNode<T>* list, T value) {
    DoubleLinkedListNode<T>* node = list;

    while (node && node->info != value) {
        node = node->nextNode;
    }

    return node;
}

template <typename T>
void AddNodeStart(DoubleLinkedListNode<T>* &cap, T info) {
    DoubleLinkedListNode<T>* node = new DoubleLinkedListNode<T>;
    node->info = info;
    node->nextNode = cap;
    node->prevNode = NULL;

    if (cap)
        cap->prevNode = node;

    cap = node;
}

template <typename T>
void AddNodeEnd(DoubleLinkedListNode<T>* &cap, T info) {
    DoubleLinkedListNode<T>* node = new DoubleLinkedListNode<T>;
    node->info = info;
    node->nextNode = NULL;

    if (cap) {
        DoubleLinkedListNode<T>* temp = cap;
        while (temp->nextNode) 
            temp = temp->nextNode;

        temp->nextNode = node;
        node->prevNode = temp;
    } else {
        cap = node;
    }
}

template <typename T>
void AddAtPosition(DoubleLinkedListNode<T>* &cap, int pos, T info) {
    if (pos == 0) {
        AddNodeStart(cap, info);
        return;
    }

    DoubleLinkedListNode<T>* prev = SearchPos(cap, pos - 1);

    if (prev == NULL) {
        AddNodeEnd(cap, info);
        return;
    }

    DoubleLinkedListNode<T>* next = prev->nextNode;

    DoubleLinkedListNode<T>* node = NULL;
    AddNodeStart(node, info);

    prev->nextNode = node;
    node->prevNode = prev;

    node->nextNode = next;
    next->prevNode = node;
}


template <typename T>
void RemoveNextNode(DoubleLinkedListNode<T>* prev) {
    DoubleLinkedListNode<T>* curr = prev->nextNode;
    DoubleLinkedListNode<T>* next = prev->nextNode->nextNode;

    prev->nextNode = next;
    next->prevNode = prev;

    delete curr;
}

template <typename T>
void RemoveHead(DoubleLinkedListNode<T>* &list) {
    if (list == NULL) 
        return;
    
    DoubleLinkedListNode<T>* toRemove = list;
    list = list->nextNode;
    list->prevNode = NULL;

    delete toRemove;
}

template <typename T>
void RemoveAtPos(DoubleLinkedListNode<T>* &list, int pos) {
    if (list == NULL) 
        return;
    
    if (pos == 0) {
        RemoveHead(list);
        return;
    }


    DoubleLinkedListNode<T>* pred = SearchPos(list, pos-1);
    RemoveNextNode(pred);
}

template <typename T>
void RemoveValue(DoubleLinkedListNode<T>* &list, T value) {
    if (list == NULL)
        return;
    
    if (list->info == value) {
        RemoveHead(list);
        return;
    }

    DoubleLinkedListNode<T>* node = list;

    while (node->nextNode != NULL && node->nextNode->info != value)
        node = node->nextNode;
    
    if (node->nextNode != NULL) {
        RemoveNextNode(node);
    }

    return;
}

template <typename T>
DoubleLinkedListNode<T>* GetTail(DoubleLinkedListNode<T> *list) {
    DoubleLinkedListNode<T>* node = list;

    while (node->nextNode) {
        node = node->nextNode;
    }

    return node;
}

template <typename T>
DoubleLinkedListNode<T>* GetHead(DoubleLinkedListNode<T> *list) {
    DoubleLinkedListNode<T>* node = list;

    while (node->prevNode) {
        node = node->prevNode;
    }

    return node;
}

template <typename T>
void PrintList(const DoubleLinkedListNode<T> *list) {
    auto node = list;

    while (node) {
        std::cout << node->info << '\n';
        node = node->nextNode;
    }
}

template <typename T>
void PrintListBackwards(const DoubleLinkedListNode<T> *list) {
    auto node = list;

    while (node) {
        std::cout << node->info << '\n';
        node = node->prevNode;
    }
}


int main() {
    DoubleLinkedListNode<int> *list = NULL;

    for (int i = 1; i < 6; i++)
        AddNodeEnd(list, i);
    
    RemoveAtPos(list, 0);

    AddAtPosition(list, 7, 7);

    DoubleLinkedListNode<int>* tail = GetTail(list);

    PrintListBackwards(tail);

    //PrintList(list);
}