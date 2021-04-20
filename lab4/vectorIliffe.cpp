#include <iostream>
#include <math.h> /* pow */
#include <cstdarg>

template <typename T>
class VectorIliffe
{
private:
    T *arr = NULL;

    int *bounds = NULL;
    int n = 0;

    T *DefineArrRecursive(int dimension)
    {
        if (dimension >= n)
            return NULL;

        int size = bounds[2 * dimension + 1] - bounds[2 * dimension] + 1;

        if (dimension < n - 1)
        {
            T *tempArr = new *T[size];

            for (int i = 0; i < size; i++)
                tempArr[i] = DefineArrRecursive(dimension + 1);
            
            return tempArr;
        } else if (dimension == n - 1) {
            T *tempArr = new T[size];

            for (int i = 0; i < size; i++)
                tempArr[i] = 0;

            return tempArr;
        }
    }

public:
    VectorIliffe(int n, ...)
    {
        this->n = n;
        bounds = new int[2 * n];

        va_list args;

        va_start(args, n);

        std::cout << "Bounds: ";

        for (int i = 0; i < 2 * n; i++)
        {
            bounds[i] = va_arg(args, int);
            std::cout << bounds[i] << " ";
        }
        std::cout << '\n';

        va_end(args);

        arr = DefineArrRecursive(0);
    }

    ~VectorIliffe() {
        delete[] arr;
        //fix this shit
    }

    // T &operator[](int index)
    // {
    //     return arr[index];
    // }

    T Get(int firstPos, ...)
    {
        int pos[n];

        pos[0] = firstPos;

        va_list args;
        va_start(args, firstPos);

        for (int i = 1; i < n; i++)
            pos[i] = va_arg(args, int);
        
        va_end(args);

        T *temp = arr;

        for (int i = 0; i < n; i++) {
            temp = temp[pos[i]];
        }

        return *temp;
    }

    void Set(T value, ...)
    {
        int pos[n];

        va_list args;
        va_start(args, value);

        for (int i = 0; i < n; i++)
            pos[i] = va_arg(args, int);
        
        va_end(args);

        T *temp = arr;

        for (int i = 0; i < n; i++) {
            temp = temp[pos[i]];
        }

        *temp = value;
    }
};


int main() {
    VectorIliffe<int> arr(3, 0, 1, 0, 1, 0, 1);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                arr.Set(i * 4 + j * 2 + k, i, j, k);
    
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                std::cout << arr.Get(i, j, k) << '\n';   
}