#pragma once
#include <iostream>

template <typename T>
class DM
{
private:
    unsigned int size;
    T* pointer;
       
    void pb(T val);
    void cheker_empty(int size);
    void cheker_index_list(int ind, int size);

public:

    DM(int size_input);
    DM(int size_input, T* arr_input);
    /*
    const чтобы нельяз было изменить переданных объект в констуркторе
    передаю ссылку, чтобы компилятор не копировал объект лишний раз
    */
    DM(const DM<T>& obj);

    //Декомпозиция (то что не меняет объект)
    void Show();
    unsigned int GetSize();
    T GetIndex(int ind);
    DM<T>* GetSubArray(int startIndex, int endIndex);

    // Операции
    void Set(int ind, T val);
    void Resize(int newSize);
    void Prepend(T val);
    DM<T>* Concat(const DM<T>& s_arr);

    ~DM();
};



