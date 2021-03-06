#include <iostream>
#include <string>

class Calculation
{
    double *pData;
    size_t BufferSize;
    size_t Size;
    double Maximum;

public:
    Calculation() :
        pData(nullptr), BufferSize(0), Size(0), Maximum(0)
    {
    }

    ~Calculation()
    {
        delete[] pData;
    }

    Calculation(const Calculation &) = delete;

    Calculation& operator= (const Calculation & other) = delete;

    void Push(double value)
    {
        if (BufferSize >= Size)
            Resize();

        pData[Size++] = value;

        if (value > Maximum)
            Maximum = value;
    }

    void Pop()
    {
        if (Size > 0)
        {
            --Size;
            FindMax();
        }
    }

    void Negative()
    {
        if (Size > 0)
        {
            pData[Size - 1] = -pData[Size - 1];
            FindMax();
        }

    }

    void Add()
    {
        if (Size >= 2)
        {
            pData[Size - 2] += pData[Size - 1];
            --Size;

            FindMax();
        }
    }

    void Subtract()
    {
        if (Size >= 2)
        {
            pData[Size - 2] = pData[Size - 1] - pData[Size - 2];
            --Size;

            FindMax();
        }
    }

    double Max() const
    {
        return Maximum;
    }

    bool IsEmpty() const
    {
        return Size == 0;
    }

    void Print() const
    {
        std::cout << "[";

        if (Size > 0)
            std::cout << pData[0];

        for (size_t i = 1; i < Size; ++i)
            std::cout << "," << pData[i];

        std::cout << "]";
    }

    void SwapWith(Calculation& other)
    {
        std::swap(pData, other.pData);
        std::swap(BufferSize, other.BufferSize);
        std::swap(Size, other.Size);
        std::swap(Maximum, other.Maximum);
    }

private:
    //
    // Удвоява размера на масива от стойности
    //
    void Resize()
    {
        size_t newSize = (Size > 0) ? (Size * 2) : 2;
        double* pBuffer = new double[newSize];

        for (size_t i = 0; i < Size; ++i)
            pBuffer[i] = pData[i];

        delete pData;
        pData = pBuffer;
        BufferSize = newSize;
    }

    //
    // Обновява стойността на Maximum, като претърсва наново масива от стойности
    //
    void FindMax()
    {
        if (Size == 0)
        {
            Maximum = 0.0;
            return;
        }

        Maximum = pData[0];

        for (size_t i = 1; i < Size; ++i)
        {
            if (Maximum < pData[i])
                Maximum = pData[i];
        }
    }
};


class Calculator
{
public:
    Calculation* pCalculations;
    size_t Size;
    const size_t MaxSize;

public:
    Calculator()
        : Size(0), MaxSize(255)
    {
        pCalculations = new Calculation[MaxSize];
    }

    ~Calculator()
    {
        delete [] pCalculations;
    }

    Calculator(const Calculator&) = delete;

    Calculator& operator=(const Calculator&) = delete;

    void Create()
    {
        if (Size < MaxSize)
            ++Size;
    }

    void Add()
    {
        for (size_t i = 0; i < Size; ++i)
            pCalculations[i].Add();
    }

    void Subtract()
    {
        for (size_t i = 0; i < Size; ++i)
            pCalculations[i].Subtract();
    }

    void Negative()
    {
        for (size_t i = 0; i < Size; ++i)
            pCalculations[i].Negative();
    }

    void Max()
    {
        for (size_t i = 0; i < Size; ++i)
        {
            std::cout << i << ":";

            if (pCalculations[i].IsEmpty())
                std::cout << "none";
            else
                std::cout << pCalculations[i].Max();

            std::cout << std::endl;
        }
    }

    void Pop(size_t cindex)
    {
        if (cindex >= Size)
        {
            std::cout << "Error, index is too large\n";
            return;
        }

        pCalculations[cindex].Pop();

        if (pCalculations[cindex].IsEmpty())
        {
            for (size_t i = cindex + 1; i < Size; ++i)
                pCalculations[i - 1].SwapWith(pCalculations[i]);

            --Size;
        }
    }

    void Push(double number, size_t cindex)
    {
        if (cindex < Size)
            pCalculations[cindex].Push(number);
        else
            std::cout << "Error, index is too large\n";
    }

    void Print() const
    {
        for (size_t i = 0; i < Size; ++i)
        {
            std::cout << i << ":";
            pCalculations[i].Print();
            std::cout << std::endl;
        }
    }
};

int main()
{
    Calculator calc;
    size_t cindex;
    double number;

    std::string input;

    while (input != "EXIT")
    {
        std::cout << "> ";
        std::cin >> input;

        // If necessary, input additional parameters
        if (input == "POP")
            std::cin >> cindex;
        else if (input == "PUSH")
            std::cin >> number >> cindex;

        // Perform the requested operation
        if (input == "CREATE")
            calc.Create();
        else if (input == "ADD")
            calc.Add();
        else if (input == "SUBTRACT")
            calc.Subtract();
        else if (input == "NEGATIVE")
            calc.Negative();
        else if (input == "MAX")
            calc.Max();
        else if (input == "PRINT")
            calc.Print();
        else if (input == "POP")
            calc.Pop(cindex);
        else if (input == "PUSH")
            calc.Push(number, cindex);
        else if (input == "EXIT")
            break;
        else
            std::cout << "Wrong command!\n";
    }

    return 0;
}