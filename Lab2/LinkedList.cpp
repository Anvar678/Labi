#include "LinkedList.h"

template <typename T>
void LinkedList<T>::cheker_empty(int size)
{
    if (size <= 0)
    {
        std::cerr << "Arrasy is empty or size below zero" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

template <typename T>
void LinkedList<T>::cheker_index_list(int ind, int size)
{
    if (ind < 0 || ind >= size)
    {
        std::cerr << "Index out of range" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}


template <typename T>
LinkedList<T>::LinkedList()
{
    //???
    value = T(); //конструктор по умолчанию   
    pointer_next = nullptr;
    size = 0;
}

template <typename T>
LinkedList<T>::LinkedList(T* arr, int count)
{
    cheker_empty(count);

    // »нициализируем головной узел(все остальные идут за ним башка->n1->n2->...)
    size = count;
    value = arr[0];
    pointer_next = nullptr;

    // “екущий узел
    LinkedList<T>* current = this;

    for (int i = 1; i < count; i++)
    {
        LinkedList<T>* newNode = new LinkedList<T>();
        newNode->value = arr[i];
        newNode->pointer_next = nullptr;
        newNode->size = 0; // у других узлов size не нужен

        //прив€ка
        current->pointer_next = newNode;
        current = newNode;
    }
}


template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copylist)
{
    if (copylist.size == 0)
    {
        value = T(); //вызываю конструктор по умолчанию дл€ T, чтобы инициализировать его временным объектом
        pointer_next = nullptr;
        size = 0;
        return;
    }

    size = copylist.size;
    value = copylist.value;
    pointer_next = nullptr;

    // ѕо цепочке, начина€ со второго узла
    LinkedList<T>* current_source = copylist.pointer_next;
    LinkedList<T>* current_target = this;

    while (current_source != nullptr)
    {
        LinkedList<T>* newNode = new LinkedList<T>();
        newNode->value = current_source->value;
        newNode->pointer_next = nullptr;
        newNode->size = 0;

        //прив€зка
        current_target->pointer_next = newNode;

        current_target = newNode;
        current_source = current_source->pointer_next;
    }
}

template <typename T>
T LinkedList<T>::GetFirst()
{
    cheker_empty(size);
    return value;
}

template <typename T>
T LinkedList<T>::GetLast()
{
    cheker_empty(size);
    LinkedList<T>* current = this;
    while (current->pointer_next != nullptr)
    {
        current = current->pointer_next;
    }
    return current->value;
}

template <typename T>
T LinkedList<T>::Get(int ind)
{
    cheker_index_list(ind, size);
    LinkedList<T>* current = this;
    for (int i = 0; i < ind; i++)
    {
        current = current->pointer_next;
    }
    return current->value;
}

template <typename T>
LinkedList<T>* LinkedList<T>::GetSubList(int startindex, int endindex)
{
    if (startindex < 0 || endindex < 0 || startindex > endindex || endindex >= size) 
    {
        std::cerr << "Invalid index" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    //иду от головы к стартиндексу
    LinkedList<T>* current = this;
    for (int i = 0; i < startindex; i++) 
    {
        current = current->pointer_next;
    }

    LinkedList<T>* subList = new LinkedList<T>();
    for (int i = startindex; i <= endindex; i++) 
    {
        subList->Append(current->value);
        current = current->pointer_next;
    }
    return subList;
}

template <typename T>
int LinkedList<T>::GetSize()
{
    cheker_empty(size);
    return size;
}

template <typename T>
void LinkedList<T>::Append(T elem)
{
    // ≈сли список пустой, то запалн€ю башку
    if (size == 0)
    {
        value = elem;
        pointer_next = nullptr;
        size = 1;
        return;
    }

    LinkedList<T>* current = this;
    while (current->pointer_next != nullptr)
    {
        current = current->pointer_next;
    }

    LinkedList<T>* newNode = new LinkedList<T>();
    newNode->value = elem;
    newNode->pointer_next = nullptr;
    newNode->size = 0;

    // ѕрив€зываем
    current->pointer_next = newNode;

    // ”величиваем size в головном узле (то есть в this)
    this->size++;
}


template <typename T>
void LinkedList<T>::Prepend(T elem)
{

    //башка
    if (size == 0)
    {
        value = elem;
        pointer_next = nullptr;
        size = 1;
        return;
    }

    // теперь башка на второй позиции.
    /*
    h->n1->n2
    n'=h

    n'->n1->n2
    h ->^

    h->n'->n1->n2
    
    */
    LinkedList<T>* newNode = new LinkedList<T>();
    newNode->value = this->value;             
    newNode->pointer_next = this->pointer_next;
    newNode->size = 0;

    // Ѕашка получает новые зн-€
    this->value = elem;
    this->pointer_next = newNode;
    this->size++;
}

template <typename T>
void LinkedList<T>::InsertAt(T elem, int index)
{
    if (index == 0)
    {
        Prepend(elem);
        return;
    }
    if (index == size)
    {
        Append(elem);
        return;
    }

    cheker_index_list(index, size);

    /*
    2
    h->n1->n2->n3->n4
    current=n2

    n'
    h->n1->n2->n3->n4
             n'^

    h->n1->n2->n'->n3->n4
             
    */

    LinkedList<T>* current = this;
    for (int i = 0; i < index - 1; i++)
    {
        current = current->pointer_next;
    }

    // Ќовый узел 
    LinkedList<T>* newNode = new LinkedList<T>();
    newNode->value = elem;
    newNode->pointer_next = current->pointer_next;
    newNode->size = 0;

    // ¬ставл€ем его в цепочку(n2->n')
    current->pointer_next = newNode;

    this->size++;
}

template <typename T>
void LinkedList<T>::Show()
{
    LinkedList<T> *current = this;

    std::cout << "\n";
    while (current->pointer_next!=nullptr)
    {
        std::cout << current->value<<"->";
        current = current->pointer_next;
    }
    std::cout << current->value << " ";
    std::cout << "\n";
}


template <typename T>
LinkedList<T>::~LinkedList()
{
    delete pointer_next;
    pointer_next = nullptr;
}
