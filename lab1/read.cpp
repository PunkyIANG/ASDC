#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#define delimiter ','
#define PATH "..\\db_ord.txt"

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
private:
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

        for (int i = 0; i < 5; i++)
        {
            out[i].erase(remove(out[i].begin(), out[i].end(), '\t'), out[i].end());
        }

        id = stoi(out[0]);
        manufacturer = out[1];
        model = out[2];
        boostClock = stoi(out[3]);
        ram = stoi(out[4]);
    }

    GraphicsCard()
    {
        id = 0;
        manufacturer = "---";
        model = "---";
        boostClock = 0;
        ram = 0;
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

GraphicsCard searchOrd(GraphicsCard database[50], int key)
{
    for (int i = 0; i < 50; i++)
    {
        if (database[i].id == key)
        {
            return database[i];
        }
        if (database[i].id > key)
        {
            cout << "No GPU found on key " << key << "\n";
            return GraphicsCard();
        }
    }

    cout << "No GPU found on key " << key << "\n";
    return GraphicsCard();
}

class NodArbore
{
public:
    GraphicsCard gpu;
    NodArbore *smaller;
    NodArbore *bigger;

    NodArbore(GraphicsCard _gpu)
    {
        gpu = _gpu;
        smaller = 0;
        bigger = 0;
    }
    ~NodArbore()
    {
        delete smaller;
        delete bigger;
    }
};

void Adauga(NodArbore *&nod, GraphicsCard gpu)
{
    if (!nod)
    {
        nod = new NodArbore(gpu);
    }
    else
    {
        if (gpu.id < nod->gpu.id)
        {
            Adauga(nod->smaller, gpu);
        }
        else if (gpu.id > nod->gpu.id)
        {
            Adauga(nod->bigger, gpu);
        }
        else
        {
            cout << "Informatie duplicat\n";
        }
    }
}

GraphicsCard SearchABC(NodArbore *nod, int key)
{
    if (!nod)
    {
        cout << "Informatia nu exista in arbore\n";
        return GraphicsCard();
    }

    if (key < nod->gpu.id)
    {
        cout << "Parcurgem " << nod->gpu;
        return SearchABC(nod->smaller, key);
    }

    if (key > nod->gpu.id)
    {
        cout << "Parcurgem " << nod->gpu;
        return SearchABC(nod->bigger, key);
    }

    cout << "Informatia exista in arbore\n";
    return nod->gpu;
}

GraphicsCard SearchBinar(GraphicsCard database[50], int key)
{
    int a = 0;
    int b = 49;
    GraphicsCard result = GraphicsCard();

    while (a < b)
    {
        int i = (a + b) / 2;
        result = database[i];

        if (result.id < key)
        {
            a = i + 1;
        }
        else if (result.id > key)
        {
            b = i;
        }
        else
        {
            a = i;
            b = i;
        }
    }

    return key == result.id ? result : GraphicsCard();
}

int Fibonacci(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        return Fibonacci(n - 1) + Fibonacci(n - 2);
    }
}

GraphicsCard SearchFibonacci(GraphicsCard database[50], int key)
{
    int m = 10;
    int Fm = Fibonacci(m); //closest fibonacci number bigger than database.length

    int i = Fibonacci(m - 1);
    int p = Fibonacci(m - 2);
    int q = Fibonacci(m - 3);

    while (database[i].id == key)
    {
        if (key < database[i].id)
        {
            if (q == 0)
            {
                cout << "Failed to find key " << key << "\n";
                return GraphicsCard();
            }

            i -= q;
            
            int tempP = p;
            p = q;
            q = tempP - q;
        }
        else if (key > database[i].id)
        {
            if (p == 1)
            {
                cout << "Failed to find key " << key << "\n";
                return GraphicsCard();
            }

            i += q;
            p -= q;
            q -= p;
        }
    }
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

    // 1)
    // cout << "\n"
    //      << searchOrd(database, 51);

    // 2)
    // NodArbore *nod;
    // for (int i = 0; i < 50; i++)
    // {
    //     Adauga(nod, database[i]);
    // }
    // cout << SearchABC(nod, 36);
    // delete nod;

    // 3)
    // cout << "\n"
    //      << SearchBinar(database, 50);

    cout << Fibonacci(10);
}