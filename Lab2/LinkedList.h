#pragma once
#include <iostream> 

template <typename T>
class LinkedList
{
private:
    T value;                    
    LinkedList<T>* pointer_next;
    unsigned int size;

    void cheker_empty(int size);
    void cheker_index_list(int ind, int size);

public:

    LinkedList();
    LinkedList(T* arr, int count);
    LinkedList(const LinkedList<T>& copylist);

    T GetFirst();
    T GetLast();
    T Get(int index);
    LinkedList<T>* GetSubList(int startindex, int endindex);
    int GetSize();

    void Append(T elem);
    void Prepend(T elem);
    void InsertAt(T elem, int index);
    void Show();

    ~LinkedList();
};
