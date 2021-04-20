#include <iostream>

using namespace std;

template <typename T>
struct NodArbore
{
    T info;
    NodArbore *smaller = NULL;
    NodArbore *bigger = NULL;
};

template <typename T>
void Adauga(NodArbore<T> *&nod, T info)
{
    // cout << "Checking  if (!nod) " << nod << "\n";
    if (!nod)
    {
        // cout << "Adding " << info;
        nod = new NodArbore<T>;
        nod->info = info;
        cout << "Added " << info << '\n';
    }
    else
    {
        // cout << "Wut D:\n";
        if (info < nod->info)
        {
            Adauga(nod->smaller, info);
        }
        else if (info > nod->info)
        {
            Adauga(nod->bigger, info);
        }
        else
        {
            cout << "Informatie duplicat\n";
        }
    }
}

template <typename T>
T SearchABC(NodArbore<T> *nod, T key)
{
    if (!nod)
    {
        cout << "Informatia nu exista in arbore\n";
        return key;
    }

    if (key < nod->info)
    {
        // cout << "Parcurgem " << nod->gpu;
        return SearchABC(nod->smaller, key);
    }

    if (key > nod->info)
    {
        // cout << "Parcurgem " << nod->gpu;
        return SearchABC(nod->bigger, key);
    }

    cout << "Informatia exista in arbore\n";
    return nod->info;
}

template <typename T>
void Print(T info)
{
    cout << info << '\n';
}

template <typename T>
void PreorderPrint(NodArbore<T> *list)
{
    if (list)
    {
        Print(list->info);
        PreorderPrint(list->smaller);
        PreorderPrint(list->bigger);
    }
}

template <typename T>
void InorderPrint(NodArbore<T> *list)
{
    if (list)
    {
        InorderPrint(list->smaller);
        Print(list->info);
        InorderPrint(list->bigger);
    }
}

template <typename T>
void PostorderPrint(NodArbore<T> *list)
{
    if (list)
    {
        PostorderPrint(list->smaller);
        PostorderPrint(list->bigger);
        Print(list->info);
    }
}

template <typename T>
NodArbore<T> *Delete(NodArbore<T> *list, int info)
{
    if (list == NULL)
    {
        return NULL;
    }
    if (info < list->info)
    {   // info is in the left sub tree.
        list->smaller = Delete(list->smaller, info);
    }
    else if (info > list->info)
    {   // info is in the right sub tree.
        list->bigger = Delete(list->bigger, info);
    }
    else
    {
        // case 1: no children
        if (list->smaller == NULL && list->bigger == NULL)
        {
            delete (list); // wipe out the memory, in C, use free function
            list = NULL;
        }
        // case 2: one child (bigger)
        else if (list->smaller == NULL)
        {
            NodArbore<T> *temp = list; // save current node as a backup
            list = list->bigger;
            delete temp;
        }
        // case 3: one child (smaller)
        else if (list->bigger == NULL)
        {
            NodArbore<T> *temp = list; // save current node as a backup
            list = list->smaller;
            delete temp;
        }
        // case 4: two children
        else
        {
            NodArbore<T> *temp = FindMin(list->bigger);      // find minimal value of bigger sub tree
            list->info = temp->info;                         // duplicate the node
            list->bigger = Delete(list->bigger, temp->info); // delete the duplicate node
        }
    }
    return list; // parent node can update reference
}

template <typename T>
NodArbore<T> *FindMin(NodArbore<T> *list)
{
    if (!list)
    {
        return NULL;
    }

    if (list->smaller)
    {
        FindMin(list->smaller);
    }

    return list;
}

int main()
{
    NodArbore<int> *list = NULL;

    for (int i = 0; i < 10; i++)
    {
        Adauga(list, rand() % 10);
    }

    Delete(list, 1);

    cout << "stuff\n";

    PreorderPrint(list);
    cout << '\n';

    InorderPrint(list);
    cout << '\n';

    PostorderPrint(list);
    cout << '\n';
}
