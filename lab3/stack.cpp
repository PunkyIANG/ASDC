#include <iostream>
#include "linkedList.cpp"

template <typename T>
struct Stack {
    LinkedListNode<T> *top;
};

template <typename T>
void Push(Stack<T> &stack, T info) {
    AddNodeStart(stack.top, info);
}

template <typename T>
T Pop(Stack<T> &stack) {
    //TODO: stuff
    //AddNodeStart(stack.top, info);
}

template <typename T>
void Print(Stack<T> stack) {
    PrintList(stack.top);
}

template <typename T>
LinkedListNode<T>* SearchValue(const Stack<T> &stack, T info) {
    return SearchValue(stack.top, info);
}

int main() {
    Stack<int> stack;

    for (int i = 0; i < 5; i++) {
        Push(stack, i);
    }

    SearchValue(stack, 2);
    Print(stack);
    
}