#include <iostream>
#include <math.h> /* pow */
#include <cstdarg>

template <typename T>
class DirectAccess
{
private:
    T *arr = NULL;
    int *bounds = NULL;
    int n = 0;
    bool isRand = true;

    int GetD(int i)
    {
        if (isRand)
        {
            if (i == n-1)
                return 1;

            return (bounds[2 * i + 1] - bounds[2 * i] + 1) * GetD(i + 1);
        }
        else
        {
            if (i == 0)
                return 1;

            return (bounds[2 * i + 1] - bounds[2 * i] + 1) * GetD(i - 1);
        }
    }

    int GetTotalDim() {
        int res = 1;

        for (int i = 0; i < n; i++)
            res *= bounds[2 * i + 1] - bounds[2 * i] + 1;
        
        return res;
    }

public:
    DirectAccess() {}

    DirectAccess(bool isRand, int n, ...)
    {
        this->isRand = isRand;
        this->n = n;
        bounds = new int[2*n];

        va_list args;

        va_start(args, n);

        std::cout << "Bounds: ";

        for (int i = 0; i < 2*n; i++) {
            bounds[i] = va_arg(args, int);
            std::cout << bounds[i] << " ";
        }
        std::cout << '\n';

        va_end(args);

        for (int i = 0; i < n; i++) {
            std::cout << "Dimension " << i << ": " << GetD(i) << '\n';
        }

        arr = new T[GetTotalDim()];

        std::cout << "Total dim: " << GetTotalDim() << '\n';
    }

    ~DirectAccess()
    {
        delete[] bounds;
        delete[] arr;
    }

    T* GetAddr(int pos[]) {
        T *res = arr;

        T *oldres = arr;

        int firstSum = 0;

        for (int i = 0; i < n; i++)
        {
            firstSum += bounds[i * 2] * GetD(i);
        }

        int secondSum = 0;

        for (int i = 0; i < n; i++)
        {
            secondSum += pos[i] * GetD(i);
        }

        std::cout << "sums " << firstSum << " " << secondSum << "\n";

        // res -= (int) pow(sizeof(T), firstSum);
        // res += (int) pow(sizeof(T), secondSum);

        res -= sizeof(T) * firstSum;
        res += sizeof(T) * secondSum;

        std::cout << "diff: " << res - oldres << "\n";

        return res;
    }

    T Get(int firstPos, ...)
    {
        int pos[n];

        pos[0] = firstPos;

        va_list args;
        va_start(args, firstPos);

        for (int i = 1; i < n; i++)
            pos[i] = va_arg(args, int);
        
        va_end(args);

        return *GetAddr(pos);
    }

    void Set(T value, ...)
    {
        int pos[n];

        va_list args;
        va_start(args, value);

        for (int i = 0; i < n; i++)
            pos[i] = va_arg(args, int);
        
        va_end(args);

        *GetAddr(pos) = value;
    }
};

int main()
{
    DirectAccess<int> test(false, 3, 0, 1, 0, 1, 0, 1);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                test.Set(i * 4 + j * 2 + k, i, j, k);
    
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                std::cout << "addr " << i << j << k << ": " << test.Get(i, j, k) << "\n";
}