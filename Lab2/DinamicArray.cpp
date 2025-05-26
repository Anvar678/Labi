#include "DinamicArray.h"

template <typename T>
void DM<T>::cheker_empty(int size)
{
    if (size<=0)
    {
        std::cerr << "Array is empty or size below zero" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

template <typename T>
void DM<T>::cheker_index_list(int ind, int size)
{
    if (ind < 0 || ind >= size)
    {
        std::cerr << "Index out of range" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}


template <typename T>
DM<T>::DM(int size_input)
{
    cheker_empty(size_input);
    pointer = new T[size_input];
    size = size_input;
}

template <typename T>
DM<T>::DM(int size_input, T* arr_input)
{
    cheker_empty(size_input);

    pointer = new T[size_input];
    size = 0;
    for (unsigned int i = 0; i < size_input; i++)
    {
        pb(arr_input[i]);
    }
}

template <typename T>
DM<T>::DM(const DM<T>& obj)
{
    size = obj.size;
    pointer = new T[size];
    for (unsigned int i = 0; i < size; i++)
    {
        pointer[i] = obj.pointer[i];
    }
}

template <typename T>
void DM<T>::Show()
{
    for (unsigned int i = 0; i < size; i++)
        std::cout << pointer[i] << " ";
    std::cout << "\n";
}

template <typename T>
unsigned int DM<T>::GetSize()
{
    cheker_empty(size);
    return size;
}

template <typename T>
T DM<T>::GetIndex(int ind)
{
    cheker_index_list(ind, size);
    return pointer[ind]; // автоматически разыменовывает указатель
}

template <typename T>
DM<T>* DM<T>::GetSubArray(int startIndex, int endIndex)
{
    if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= size)
    {
        std::cerr << "Invalid index" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int subSize = endIndex - startIndex + 1;
    T* buf = new T[subSize];
    for (int i =0; i < subSize; i++)
    {
        buf[i] = this->GetIndex(startIndex+i);
    }
    DM<T>* arr= new DM(subSize, buf);
    delete[] buf;
    return arr;
}

template <typename T>
void DM<T>::Set(int ind, T val)
{
    cheker_index_list(ind, size);
    pointer[ind] = val;
}

template <typename T>
void DM<T>::Resize(int newSize)
{
    cheker_empty(newSize);
    T* new_pointer = new T[newSize];
    unsigned int copyCount = (newSize < static_cast<int>(size)) ? newSize : size;
    for (unsigned int i = 0; i < copyCount; i++)
    {
        new_pointer[i] = pointer[i];
    }

    delete[] pointer;
    pointer = new_pointer;
    size = newSize;
}

template <typename T>
void DM<T>::Prepend(T val)
{
    this->Resize(this->size + 1);

    for (int i = this->size-1; i > 0; i--)
    {
        pointer[i] = pointer[i - 1];
    }
    pointer[0] = val;
    
}

template <typename T>
DM<T>* DM<T>::Concat(const DM<T>& s_arr)
{
    DM<T> f_arr = *this;
    int new_size = f_arr.size + s_arr.size;
    DM<T>* res=new DM<T>(new_size);

    for (int i = 0; i < f_arr.size; i++)
    {
        res->pointer[i] = f_arr.pointer[i];
    }

    for (int j = 0; j < s_arr.size; j++)
    {
        res->pointer[f_arr.size + j] = s_arr.pointer[j];
    }
    
    return res;
}

template <typename T>
DM<T>::~DM()
{
    delete[] pointer;
}

template <typename T>
void DM<T>::pb(T val)
{
    T* new_pointer = new T[size + 1];
    for (unsigned int i = 0; i < size; i++)
    {
        new_pointer[i] = pointer[i];
    }

    new_pointer[size] = val;
    delete[] pointer;
    pointer = new_pointer;
    size++;
}
