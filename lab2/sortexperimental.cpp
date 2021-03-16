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

    // ~GraphicsCard() {
    //     cout << id << " ";
    // }

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

void PrintIds(GraphicsCard *database)
{
    for (int i = 0; i < 50; i++)
    {
        cout << database[i].id << ' ';
    }
    cout << '\n';
}

void InsertValue(GraphicsCard *database, int objPos)
{
    GraphicsCard temp = database[objPos];

    cout << "sorting " << objPos << '\n';
    int i;

    for (i = objPos - 1; i >= 0; i--)
    {
        if (database[objPos].id > database[i].id) {
            break;
        }
    }

    int seqStart = i + 1;
    int seqEnd = objPos - 1;

    cout << "seqstart " << seqStart << " seqend " << seqEnd << '\n';
    if (seqEnd - seqStart < 0) {
        return;
    }

    GraphicsCard cache[seqStart - seqEnd];
    copy(database + seqStart, database + seqEnd, cache);

    for (int j = 0; j < seqStart - seqEnd; j++) {
        cout << cache[j];
    }

    cout << "\n";

    copy(cache, cache + seqStart - seqEnd + 1, database + seqStart + 1);
    database[seqStart] = temp;
}

int InsertionSort(GraphicsCard *database)
{
    int count = 0;
    for (int i = 1; i < 50; i++)
    {
        InsertValue(database, i);
    }

    return count;
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

    GraphicsCard insertionSorted[50];
    copy(begin(database), end(database), begin(insertionSorted));


    InsertionSort(insertionSorted);

    for (int i = 0; i < 50; i++)
    {
        cout << i << " " << insertionSorted[i];
    }
}