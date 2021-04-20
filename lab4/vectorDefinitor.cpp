#include <iostream>
#include <math.h> /* pow */
#include <cstdarg>

template <typename T>
class VectorDefinitor
{
private:
    T *arr = NULL;
    int n = 0;
    int *bounds = NULL;
    bool isRand = true;
    int *D = NULL;
    int firstSum = 0;
    int totalSize = 0;

    int SetD() {
        D = new int[n];

        if (isRand) {
            D[n-1] = 1;

            for (int i = n-2; i >= 0; i--) {
                D[i] = (bounds[2 * i + 1] - bounds[2 * i] + 1) * D[i + 1];
            }
        } else {
            D[0] = 1;

            for (int i = 1; i < n; i++) {
                D[i] = (bounds[2 * i + 1] - bounds[2 * i] + 1) * D[i - 1];
            }
        }
    }

    void SetTotalDim() {
        totalSize = 1;

        for (int i = 0; i < n; i++)
            totalSize *= bounds[2 * i + 1] - bounds[2 * i] + 1;
    }

    void SetFirstSum() {
        for (int i = 0; i < n; i++)
        {
            firstSum += bounds[i * 2] * D[i];
        }
    }

public:

    VectorDefinitor() {}

    VectorDefinitor(bool isRand, int n, ...)
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

        SetD();
        SetTotalDim();

        for (int i = 0; i < n; i++) {
            std::cout << "Dimension " << i << ": " << D[i] << '\n';
        }


        arr = new T[totalSize];

        std::cout << "Total size: " << totalSize << '\n';
    }

    ~VectorDefinitor()
    {
        delete[] bounds;
        delete[] arr;
    }

    T* GetAddr(int pos[]) {
        T *res = arr;

        T *oldres = arr;

        int secondSum = 0;

        for (int i = 0; i < n; i++)
        {
            secondSum += pos[i] * D[i];
        }

        std::cout << "sums " << firstSum << " " << secondSum << "\n";

        // res -= (int) pow(sizeof(T), firstSum);
        // res += (int) pow(sizeof(T), secondSum);

        res += sizeof(T) * (secondSum - firstSum);

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
    VectorDefinitor<int> test(false, 3, 0, 1, 0, 1, 0, 1);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                test.Set(i * 4 + j * 2 + k, i, j, k);
    
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                std::cout << "addr " << i << j << k << ": " << test.Get(i, j, k) << "\n";
}