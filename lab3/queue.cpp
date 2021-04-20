#include <iostream>
#include "linkedList.cpp"

template <typename T>
struct Queue {
    LinkedListNode<T> *first = NULL;
    LinkedListNode<T> *last = NULL;
};

template <typename T>
void Enqueue(Queue<T> &queue, T info) {
    if (queue.first == NULL) {
        queue.first = new LinkedListNode<T>;
        queue.first->info = info;
        queue.first->nextNode = NULL;
        queue.last = queue.first;
    } else {
        LinkedListNode<T> *temp = new LinkedListNode<T>;
        temp->info = info;
        temp->nextNode = NULL;
        queue.last->nextNode = temp;
        queue.last = temp;
    }
}

template <typename T>
T Dequeue(Queue<T> &queue) {
    T info = queue.first->info;
    queue.first = queue.first->nextNode;
    return info;
}

template <typename T>
void Print(const Queue<T> &queue) {
    PrintList(queue.first);
}

template <typename T>
LinkedListNode<T>* SearchValue(const Queue<T> &queue, T info) {
    return SearchValue(queue.first);
}

int main() {
    Queue<int> queue;

    
    for (int i = 0; i < 5; i++)
    {
        Enqueue(queue, i);
    }

    while (queue.first) {
        std::cout << Dequeue(queue) << '\n';
    }
}