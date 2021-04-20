#include <iostream>
#include <math.h> /* pow */
#include <cstdarg>

template <typename T>
class VectorIliffe
{
private:
    int dimension = -1;
    int lowBound = -1;
    int highBound = -1;

    VectorIliffe *pointerArr = NULL;
    T *valueArr = NULL;

public:
    VectorIliffe()
    {
        // std::cout << "noArg ctor " << '\n';
    }

    VectorIliffe(int dimension, int lowBound, int highBound)
    {
        this->dimension = dimension - 1;
        this->lowBound = lowBound;
        this->highBound = highBound;

        int size = highBound - lowBound + 1;
        std::cout << "singlArg ctor " << this->dimension << ' ' << lowBound << ' ' << highBound << ' ' << size << '\n';

        if (this->dimension == 0)
        {
            valueArr = new T[size];
        }
    }

    template <typename... Args>
    VectorIliffe(int dimension, int lowBound, int highBound, Args... bounds)
    {

        this->dimension = dimension - 1;
        this->lowBound = lowBound;
        this->highBound = highBound;

        int size = highBound - lowBound + 1;
        std::cout << "multiArg ctor " << this->dimension << ' ' << lowBound << ' ' << highBound << ' ' << size << '\n';
        if (this->dimension)
        {
            pointerArr = new VectorIliffe<T>[size];

            for (int i = 0; i < size; i++)
            {
                pointerArr[i] = VectorIliffe<T>(dimension - 1, bounds...);
            }
        }
        else
        {
            std::cout << "Why would this ever be called? ctor\n";
            valueArr = new T[size];
        }
    }

    ~VectorIliffe()
    {
        if (dimension)
            delete[] pointerArr;
        else
            delete[] valueArr;
    }

    T Get()
    {
        std::cout << "noArg Get " << '\n';
        return NULL;
    }

    T Get(int firstPos)
    {
        std::cout << firstPos << '\n';

        if (dimension == 0)
            return valueArr[firstPos];

        return NULL;
    }

    template <typename... Args>
    T Get(int firstPos, Args... args)
    {
        std::cout << firstPos << ' ';
        
        if (dimension)
        {
            return pointerArr[firstPos].Get(args...);
        }
        else
        {
            std::cout << "Why would this ever be called? Get\n";
            return valueArr[firstPos];
        }
    }

    void Set()
    {
        std::cout << "noArg Set " << '\n';
    }

    void Set(T value, int firstPos)
    {
        std::cout << firstPos << ": " << value << '\n';

        if (dimension == 0)
            valueArr[firstPos] = value;
    }

    template <typename... Args>
    void Set(T value, int firstPos, Args... params)
    {
        if (dimension)
        {
            std::cout << firstPos << ' ';
            pointerArr[firstPos].Set(value, params...);
        }
        else
        {
            std::cout << "Why would this ever be called? Set\n";
            valueArr[firstPos] = value;
        }
    }

    void operator=(const VectorIliffe &vectorIliffe)
    {
        this->dimension = vectorIliffe.dimension;
        this->lowBound = vectorIliffe.lowBound;
        this->highBound = vectorIliffe.highBound;

        this->pointerArr = vectorIliffe.pointerArr;
        this->valueArr = vectorIliffe.valueArr;
    }
};

int main()
{
    // VectorIliffe<int> arr(4, -1, -1, 0, 3, 3, 4, 5, 7);
    VectorIliffe<int> arr(3, 0, 1, 0, 1, 0, 1);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
            {
                arr.Set(i * 4 + j * 2 + k, i, j, k);
                std::cout << "Value: " << arr.Get(i, j, k) << '\n';
            }

    std::cout << '\n';

    // for (int i = 0; i < 2; i++)
    //     for (int j = 0; j < 2; j++)
    //         for (int k = 0; k < 2; k++)
                // std::cout << arr.Get(i, j, k) << '\n';
}