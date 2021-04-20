#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <time.h>
#include <chrono>
#define delimiter '\t'
#define PATH "..\\db_neord3.txt"

using namespace std;

void tokenize(const string &str, const char delim, string out[5])
{
    stringstream sstream(str);

    string result;

    int i = 0;

    while (getline(sstream, result, delim))
    {
        out[i] = result;
        i++;
    }
}

class GraphicsCard
{
public:
    int id;
    string manufacturer;
    string model;
    int boostClock;
    int ram;

    GraphicsCard(const string &line)
    {
        string out[5];
        tokenize(line, delimiter, out);

        // for (int i = 0; i < 5; i++)
        // {
        //     out[i].erase(remove(out[i].begin(), out[i].end(), '\t'), out[i].end());
        // }

        // cout << out[0] + " ";
        // cout << out[1] + " ";
        // cout << out[2] + " ";
        // cout << out[3] + " ";
        // cout << out[4] + " ";
        // cout << '\n';

        id = stoi(out[0]);
        manufacturer = out[1];
        model = out[2];
        boostClock = stoi(out[3]);
        ram = stoi(out[4]);
    }

    GraphicsCard()
    {
        id = -1;
        manufacturer = "---";
        model = "---";
        boostClock = 0;
        ram = 0;
    }

    GraphicsCard(const GraphicsCard &copy)
    {
        id = copy.id;
        manufacturer = copy.manufacturer;
        model = copy.model;
        boostClock = copy.boostClock;
        ram = copy.ram;
    }

    // friend istream &operator>>(istream &is, GraphicsCard &card);
    friend ostream &operator<<(ostream &os, const GraphicsCard &card);
};

// istream &operator>>(istream &is, GraphicsCard &card)
// {
//     string line;
//     is >> line;

//     card = GraphicsCard(line);
//     return is;
// }

ostream &operator<<(ostream &os, const GraphicsCard &card)
{
    os << card.id << " " << card.manufacturer << " " << card.model << " "
       << card.boostClock << " " << card.ram << '\n';
    return os;
}

void BubbleSort(GraphicsCard *database)
{
    for (int i = 0; i < 49; i++)
    {
        for (int j = i; j < 50; j++)
        {
            if (database[i].id > database[j].id)
            {
                GraphicsCard swap = database[j];
                database[j] = database[i];
                database[i] = swap;
            }
        }
    }
}

void InsertValue(GraphicsCard *database, int objPos)
{
    GraphicsCard temp = database[objPos];

    int i;

    for (i = objPos - 1; i >= 0; i--)
    {
        if (temp.id > database[i].id)
            break;
        else
            database[i + 1] = database[i];
    }

    database[i + 1] = temp;
}

void InsertionSort(GraphicsCard *database)
{
    for (int i = 1; i < 50; i++)
    {
        InsertValue(database, i);
    }
}

void SelectionSort(GraphicsCard *database)
{
    for (int i = 0; i < 49; i++)
    {
        int smallest = i;
        for (int j = i; j < 50; j++)
        {
            if (database[smallest].id > database[j].id)
            {
                smallest = j;
            }
        }

        GraphicsCard swap = database[smallest];
        database[smallest] = database[i];
        database[i] = swap;
    }
}

void PrintIds(GraphicsCard *database)
{
    for (int i = 0; i < 50; i++)
    {
        cout << database[i].id << ' ';
    }
    cout << '\n';
}

void Partition(GraphicsCard *database, int start, int end, int &pivot)
{
    int i;
    // PrintIds(database);

    for (i = pivot - 1; i >= start; i--)
    {
        if (database[pivot].id < database[i].id)
        {

            GraphicsCard temp = database[i];

            for (int j = i; j <= end - 1; j++)
            {
                database[j] = database[j + 1];
            }

            database[end] = temp;
            pivot--;
            // PrintIds(database);
        }
    }
}

void QuickSortRecursive(GraphicsCard *database, int start, int end)
{
    if (!(start < end)) {
        return;
    }

    int pivot = end;
    Partition(database, start, end, pivot);
    //PrintIds(database);

    QuickSortRecursive(database, start, pivot - 1);
    QuickSortRecursive(database, pivot + 1, end);
}

void QuickSort(GraphicsCard *database)
{
    int pivot = 49;
    //PrintIds(database);
    Partition(database, 0, 49, pivot);
    //PrintIds(database);

    QuickSortRecursive(database, 0, pivot - 1);
    QuickSortRecursive(database, pivot + 1, 49);
    //PrintIds(database);
}

int main()
{
    ifstream file;
    string line;
    file.open(PATH);
    GraphicsCard database[50];

    if (file.is_open())
    {
        int i = 0;

        while (getline(file, line))
        {
            // cout << line << "\n";
            database[i] = GraphicsCard(line);
            i++;
        }
    }
    else
    {
        cout << "Unable to open file \n";
    }

    for (int i = 0; i < 50; i++)
    {
        cout << database[i];
    }

    cout << "\n";

    // GraphicsCard bubbleSorted[50];
    // copy(begin(database), end(database), begin(bubbleSorted));

    // BubbleSort(bubbleSorted);

    // for (int i = 0; i < 50; i++)
    // {
    //     cout << i << " " << bubbleSorted[i];
    // }

    GraphicsCard insertionSorted[50];
    copy(begin(database), end(database), begin(insertionSorted));

    InsertionSort(insertionSorted);

    for (int i = 0; i < 50; i++)
    {
        cout << i << " " << insertionSorted[i];
    }

    // GraphicsCard selectionSorted[50];
    // copy(begin(database), end(database), begin(selectionSorted));

    // SelectionSort(selectionSorted);

    // for (int i = 0; i < 50; i++)
    // {
    //     cout << i << " " << selectionSorted[i];
    // }

    // GraphicsCard quickSorted[50];
    // copy(begin(database), end(database), begin(quickSorted));

    // QuickSort(quickSorted);

    // for (int i = 0; i < 50; i++)
    // {
    //     cout << quickSorted[i];
    // }
}