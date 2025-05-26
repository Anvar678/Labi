#include "DinamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"


template <typename T>
class ArraySequence : public Sequence<T>
{
protected:
    DM<T> arr;

public:
    ArraySequence()
    {
        arr.pointer = nullptr;
        arr.size = 0;
    }

    ArraySequence(T* items, int count)
    {
        DM<T> temp(count, items);
        arr = temp;
    }

    ArraySequence(const DM<T>& arr_inp)
    {
        DM<T> temp(arr_inp);
        arr = temp;
    }

    virtual T GetFirst() const override
    {
        return arr.GetIndex(0);
    }

    virtual T GetLast() const override
    {
        return arr.GetIndex(arr.size - 1);
    }

    virtual T Get(int index) const override
    {
        return arr.GetIndex(index);
    }

    virtual ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override
    {
        DM<T>* subArr = arr.GetSubArray(startIndex, endIndex);
        ArraySequence<T>* result = new ArraySequence<T>(*subArr);
        delete subArr;
        return result;
    }

    virtual int GetLength() const override
    {
        return arr.GetSize();
    }

    // ”ниверсальные мутабельные/иммутабельные операции
    virtual Sequence<T>* Append(T item) override
    {
        ArraySequence<T>* res = static_cast<ArraySequence<T>*>(this->instance());
        res->arr.pb(item);
        return res;
    }

    virtual Sequence<T>* Prepend(T item) override
    {
        ArraySequence<T>* res = static_cast<ArraySequence<T>*>(this->instance());
        res->arr.Prepend(item);
        return res;
    }

    virtual Sequence<T>* InsertAt(T item, int index) override
    {
        ArraySequence<T>* res = static_cast<ArraySequence<T>*>(this->instance());
        res->arr.Set(index, item);
        return res;
    }

    virtual Sequence<T>* Concat(Sequence<T>* list) override
    {
        ArraySequence<T>* res = static_cast<ArraySequence<T>*>(this->instance());
        for (int i = 0; i < list->GetLength(); i++)
        {
            res->arr.pb(list->Get(i));
        }
        return res;
    }

    virtual Sequence<T>* instance() = 0;

    virtual ~ArraySequence() {}
};


template <typename T>
class MutableArraySequence : public ArraySequence<T>
{
public:
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    MutableArraySequence(const DM<T>& arr_inp) : ArraySequence<T>(arr_inp) {}

    virtual Sequence<T>* instance() override
    {
        return this;
    }
};


template <typename T>
class ImMutableArraySequence : public ArraySequence<T>
{
public:
    ImMutableArraySequence() : ArraySequence<T>() {}
    ImMutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    ImMutableArraySequence(const DM<T>& arr_inp) : ArraySequence<T>(arr_inp) {}

    virtual Sequence<T>* instance() override
    {
        return copy_obj();
    }

private:
    ImMutableArraySequence* copy_obj() const
    {
        return new ImMutableArraySequence(*this);
    }
};


template <typename T>
class LinkedListSequence : public Sequence<T>
{
protected:
    LinkedList<T> linked_list_obj;

public:
    LinkedListSequence()
    {
        linked_list_obj.value = T();
        linked_list_obj.pointer_next = nullptr;
        linked_list_obj.size = 0;
    }

    LinkedListSequence(T* items, int count)
    {
        linked_list_obj = LinkedList<T>(items, count);
    }

    LinkedListSequence(const LinkedList<T>& list)
    {
        linked_list_obj = list;
    }

    virtual T GetFirst() const override
    {
        return linked_list_obj.GetFirst();
    }

    virtual T GetLast() const override
    {
        return linked_list_obj.GetLast();
    }

    virtual T Get(int index) const override
    {
        return linked_list_obj.Get(index);
    }

    virtual int GetLength() const override
    {
        return linked_list_obj.GetSize();
    }

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override
    {
        LinkedList<T> sublist = linked_list_obj.GetSubList(startIndex, endIndex);
        Sequence<T>* result = new LinkedListSequence<T>(sublist);
        return result;
    }

    // ”ниверсальные операции
    virtual Sequence<T>* Append(T item) override
    {
        LinkedListSequence<T>* res = static_cast<LinkedListSequence<T>*>(this->instance());
        res->linked_list_obj.Append(item);
        return res;
    }

    virtual Sequence<T>* Prepend(T item) override
    {
        LinkedListSequence<T>* res = static_cast<LinkedListSequence<T>*>(this->instance());
        res->linked_list_obj.Prepend(item);
        return res;
    }

    virtual Sequence<T>* InsertAt(T item, int index) override
    {
        LinkedListSequence<T>* res = static_cast<LinkedListSequence<T>*>(this->instance());
        res->linked_list_obj.InsertAt(item, index);
        return res;
    }

    virtual Sequence<T>* Concat(Sequence<T>* list) override
    {
        LinkedListSequence<T>* res = static_cast<LinkedListSequence<T>*>(this->instance());
        for (int i = 0; i < list->GetLength(); i++)
        {
            res->linked_list_obj.Append(list->Get(i));
        }
        return res;
    }

    virtual Sequence<T>* instance() = 0;

    virtual ~LinkedListSequence() {}
};


template <typename T>
class MutableLinkedListSequence : public LinkedListSequence<T>
{
public:
    MutableLinkedListSequence() : LinkedListSequence<T>() {}
    MutableLinkedListSequence(T* items, int count) : LinkedListSequence<T>(items, count) {}
    MutableLinkedListSequence(const LinkedList<T>& list) : LinkedListSequence<T>(list) {}

    virtual Sequence<T>* instance() override
    {
        return this;
    }
};


template <typename T>
class ImMutableLinkedListSequence : public LinkedListSequence<T>
{
public:
    ImMutableLinkedListSequence() : LinkedListSequence<T>() {}
    ImMutableLinkedListSequence(T* items, int count) : LinkedListSequence<T>(items, count) {}
    ImMutableLinkedListSequence(const LinkedList<T>& list) : LinkedListSequence<T>(list) {}

    virtual Sequence<T>* instance() override
    {
        return copy_obj();
    }

private:
    ImMutableLinkedListSequence* copy_obj() const
    {
        return new ImMutableLinkedListSequence(*this);
    }
};