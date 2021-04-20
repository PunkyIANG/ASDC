#include <iostream>

template <typename T>
struct CircularListNode
{
    T info;
    CircularListNode<T> *nextNode;
    CircularListNode<T> *prevNode;
};

template <typename T>
CircularListNode<T> *SearchPos(CircularListNode<T> *list, int pos)
{
    CircularListNode<T> *node = list;

    if (pos >= 0)
    {
        while (node && pos)
        {
            node = node->nextNode;
            pos--;
        }
    }
    else
    {
        pos = -pos;
        while (node && pos)
        {
            node = node->prevNode;
            pos--;
        }
    }

    return node;
}

template <typename T>
CircularListNode<T> *SearchValue(CircularListNode<T> *list, T value)
{
    CircularListNode<T> *node = list;

    while (node && node->info != value && node != list->prevNode)
    {
        node = node->nextNode;
    }

    if (node->info == value)
    {
        return node;
    }
    else
    {
        return NULL;
    }
}

template <typename T>
void CreateNode(CircularListNode<T> *&node, T info)
{
    node = new CircularListNode<T>;
    node->info = info;
    node->nextNode = node;
    node->prevNode = node;
}

template <typename T>
void InsertBetween(CircularListNode<T> *&prev, CircularListNode<T> *&next, T info)
{
    if (prev->nextNode == next && next->prevNode == prev)
    {
        CircularListNode<T> *node = new CircularListNode<T>;
        node->info = info;
        node->nextNode = next;
        node->prevNode = prev;
        prev->nextNode = node;
        next->prevNode = node;
    }
}

template <typename T>
void InsertBefore(CircularListNode<T> *&next, T info)
{
    CircularListNode<T> *prev = next->prevNode;
    InsertBetween(prev, next, info);
}

template <typename T>
void InsertAfter(CircularListNode<T> *&prev, T info)
{
    CircularListNode<T> *next = prev->nextNode;
    InsertBetween(prev, next, info);
}

template <typename T>
void InsertAtPosition(CircularListNode<T> *&cap, int pos, T info)
{
    if (pos == 0)
    {
        InsertBefore(cap, info);
        return;
    }

    CircularListNode<T> *prev = SearchPos(cap, pos - 1);

    if (prev == NULL)
    {
        CreateNode(cap, info);
        return;
    }

    InsertAfter(prev, info);
}

template <typename T>
void RemoveNextNode(CircularListNode<T> *prev)
{
    CircularListNode<T> *curr = prev->nextNode;
    CircularListNode<T> *next = prev->nextNode->nextNode;

    prev->nextNode = next;
    next->prevNode = prev;

    delete curr;
}

template <typename T>
void RemoveNode(CircularListNode<T> *&node)
{
    if (node == NULL)
        return;

    if (node == node->nextNode && node == node->prevNode)   // single node
    {
        CircularListNode<T> *toDelete = node;
        node = NULL;
        delete toDelete;
    } else {
        CircularListNode<T> *prev = node->prevNode;
        CircularListNode<T> *next = node->nextNode;
        CircularListNode<T> *toDelete = node;

        prev->nextNode = next;
        next->prevNode = next;
        node = next;

        delete toDelete;
    }
}

template <typename T>
void RemoveAtPos(CircularListNode<T> *&list, int pos)
{
    if (list == NULL)
        return;

    CircularListNode<T> *node = SearchPos(list, pos);

    if (node == list) {
        RemoveNode(list);
    } else {
        RemoveNode(node);
    }
}

template <typename T>
void RemoveValue(CircularListNode<T> *&list, T value)
{
    if (list == NULL)
        return;

    if (list->info == value)
    {
        RemoveNode(list);
        return;
    }

    CircularListNode<T> *node = list;

    do
    {
        node = node->nextNode;
    } while (node->info != value && node != list);

    if (node != list)
        RemoveNode(node);
    
    return;
}

template <typename T>
void PrintList(CircularListNode<T> *list)
{
    CircularListNode<T> *node = list;

    do
    {
        std::cout << node->info << '\n';
        node = node->nextNode;
    } while (node != list);
}

template <typename T>
void PrintListBackwards(CircularListNode<T> *list)
{
    CircularListNode<T> *node = list;

    do
    {
        std::cout << node->info << '\n';
        node = node->prevNode;
    } while (node != list);
}

int main()
{
    CircularListNode<int> *list = NULL;

    CreateNode(list, 0);

    InsertBetween(list, list, 1);

    for (int i = 1; i < 6; i++)
        InsertBefore(list, i);


    //RemoveNode(list->nextNode);
    RemoveAtPos(list, 0);

    InsertAtPosition(list, 7, 7);

    PrintList(list);

    //PrintListBackwards(list);
}