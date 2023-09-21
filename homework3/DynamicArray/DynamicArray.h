#include <iostream>

template <typename T>
class DynamicArray
{
    template <typename T> friend std::ostream& operator<< (std::ostream& stream, const DynamicArray<T>& ll);
public:

    DynamicArray(float reserveCoef_ = 1.5) : sizeOfArray{ 0 }, reserveCoef{ reserveCoef_ }
    {
        if (reserveCoef_ < 1)
        {
            std::cout << "Reserve coef must not be smaller than 1" << std::endl;
            exit(1);
        }
        sizeOfAllocatedMemory = (int) ceil(reserveCoef);
        firstElementPtr = (T*) malloc(sizeof(T) * sizeOfAllocatedMemory);
        if (firstElementPtr == 0) 
        {
            std::cout << "Memory was not allocated";
            exit(1);
        }
    }

    DynamicArray(int const &arrSize, float reserveCoef_ = 1.5) : sizeOfArray{ 0 }, reserveCoef{ reserveCoef_ }
    {
        if (reserveCoef_ < 1)
        {
            std::cout << "Reserve coef must not be smaller than 1" << std::endl;
            exit(1);
        }
        sizeOfAllocatedMemory = arrSize * (int) ceil(reserveCoef);
        std::cout << "sizeOfAllocatedMemory: " << sizeOfAllocatedMemory << std::endl;
        firstElementPtr = new T[sizeOfAllocatedMemory];
        if (firstElementPtr == 0) 
        {
            std::cout << "Memory was not allocated";
            exit(1);
        }
    };

    DynamicArray(const DynamicArray& other)
    {
        float otherReserveCoef = other.reserveCoef;
        int otherArraySize = other.size();
        int newAllocatedMemorySize = otherArraySize * otherReserveCoef;
        T* tempArrayPtr = (T*) malloc(sizeof(T) * newAllocatedMemorySize);
        if (tempArrayPtr != 0) 
        {
            for (int i = 0; i < otherArraySize-1; i++)
            {
                new(tempArrayPtr + i) T(other.firstElementPtr[i]);
            }
            delete[] firstElementPtr;
            firstElementPtr = tempArrayPtr;
            sizeOfAllocatedMemory = newAllocatedMemorySize;
            sizeOfArray = otherArraySize;
            reserveCoef = otherReserveCoef;
        }
    };

    T& operator[](const int index) const
    {
        return firstElementPtr[index];
    }

    ~DynamicArray()
    {
        delete[] firstElementPtr;
    };

    DynamicArray& operator=(const DynamicArray& other) 
    {
        delete[] firstElementPtr;
        sizeOfArray = other.size();
        reserveCoef = other.reserveCoef;
        sizeOfAllocatedMemory = sizeOfArray + (sizeOfArray * reserveCoef);
        firstElementPtr = malloc(sizeof(T)* sizeOfAllocatedMemory);
        if (firstElementPtr != 0) 
        {
        for (int i = 0; i < sizeOfArray; i++)
            {
                new(firstElementPtr + i) T(other.firstElementPtr + i);
            }
        }
        return *this;
    };


    DynamicArray(DynamicArray&& other) 
    {
        firstElementPtr = other.firstElementPtr;
        sizeOfArray = other.sizeOfArray;
        sizeOfAllocatedMemory = other.sizeOfAllocatedMemory;
        other.firstElementPtr = nullptr;
        other.sizeOfArray = 0;
        other.sizeOfAllocatedMemory = 0;
    };

    DynamicArray& operator=(DynamicArray&& other) 
    {
        if (this != &other)
        {
            delete[] firstElementPtr;
            firstElementPtr = other.firstElementPtr;
            sizeOfArray = other.sizeOfArray;
            sizeOfAllocatedMemory = other.sizeOfAllocatedMemory;
            other.firstElementPtr = nullptr;
            other.sizeOfArray = 0;
            other.sizeOfAllocatedMemory = 0;
        }
    };

    void insert(T value, int index)
    {
        if (index >= 0 && index<=sizeOfArray)
        {
            sizeOfArray++;
            int availableMemorySize = (sizeOfAllocatedMemory - sizeOfArray) * sizeof(T);
            int neededMemory = sizeof(T);
            if (availableMemorySize >= neededMemory)
            {
                T tempValue = *(firstElementPtr + index);
                new(firstElementPtr + index) T(value);
                index++;
                for (int i=index; i<sizeOfArray; i++)
                {
                    T currentTempValue = *(firstElementPtr + i);
                    *(firstElementPtr + i) = tempValue;
                    tempValue = currentTempValue;
                }  
            } 
            else
            {
                int newAllocatedMemorySize = sizeOfArray + (int)((float)sizeOfArray * reserveCoef);
                T* tempArrayPtr = (T*) malloc(sizeof(T) * newAllocatedMemorySize);
                if (tempArrayPtr != 0) {
                    for (int i=0; i<index; i++)
                    {
                        new (tempArrayPtr+i) T(*(firstElementPtr+i));
                    }
                    new (tempArrayPtr+index) T(value);
                    for (int i=index+1; i<sizeOfArray; i++)
                    {
                        std::cout << "--+__" << std::endl;
                        new (tempArrayPtr+i) T(*(firstElementPtr+(i-1)));
                    }
                    delete [] firstElementPtr;
                    firstElementPtr = tempArrayPtr;
                }
            } 
            
        }
        
    }

    void push_back(T const newValue)
    {
        int availableMemorySize = (sizeOfAllocatedMemory - sizeOfArray) * sizeof(T);
        int neededMemory = sizeof(T);
        if (availableMemorySize >= neededMemory)
        {
            new (firstElementPtr + sizeOfArray) T(newValue);
            ++sizeOfArray;
        }
        else 
        {
            int newArraySize = sizeOfArray + 1;
            int newAllocatedMemorySize = sizeOfArray + (int)((float)sizeOfArray * reserveCoef);
            T* tempArrayPtr = (T*) malloc(sizeof(T) * newAllocatedMemorySize);
            if (tempArrayPtr != 0) {
                sizeOfArray = newArraySize;
                for (int i=0; i<sizeOfArray-1; i++)
                {
                    new(tempArrayPtr + i) T(firstElementPtr[i]);
                }
                new(tempArrayPtr + (sizeOfArray - 1)) T(newValue);
                delete[] firstElementPtr;
                firstElementPtr = tempArrayPtr;
                sizeOfAllocatedMemory = newAllocatedMemorySize;
            }
            else {
                std::cout << "Memory was not allocated";
                exit(1);
            }
        }
    }

    void erase(int index)
    {
        T tempValue = *(firstElementPtr + sizeOfArray-1);
        for (int i = sizeOfArray-2; i>=index; i--)
        {
            
            T currentTemp = *(firstElementPtr+i);
            *(firstElementPtr+i) = tempValue;
            tempValue = currentTemp;
        }
        sizeOfArray--;
    }

    int size() const
    {
        return sizeOfArray;
    };
private:
    int sizeOfArray;
    int sizeOfAllocatedMemory;
    T* firstElementPtr;
    float reserveCoef;
};

template <typename T>
std::ostream& operator<< (std::ostream& stream, const DynamicArray<T> &dArr) 
{
    for (int i = 0; i < dArr.sizeOfArray; i++)
    {
        stream << dArr[i];
        if (i != dArr.sizeOfArray - 1) 
        {
            stream << ", ";
        }
        else 
        {
            stream << "\n";
        }
    }
    return stream;
}
