#include <stdexcept>
#include "DynamicArray.cpp"

template <typename T>
class Sequence {
public:
    virtual ~Sequence() = default;


    virtual T GetFirst() const = 0;
    virtual T GetLast()  const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const = 0;


    virtual Sequence<T>* Append(T item) const = 0;
    virtual Sequence<T>* Prepend(T item) const = 0;
    virtual Sequence<T>* InsertAt(T item, int index) const = 0;
    virtual Sequence<T>* Concat(Sequence<T>* other) const = 0;
};

template <typename T>
class MutableSequence : public Sequence<T> 
{
public:
    virtual void AppendInPlace(T item) = 0;
    virtual void PrependInPlace(T item) = 0;
    virtual void InsertAtInPlace(T item, int index) = 0;
};

template <typename T>
class ArraySequence : public MutableSequence<T> 
{
public:
    ArraySequence() {}

    // Собираю массив через AppendInPlace
    ArraySequence(T* items, int count) 
    {
        for (int i = 0; i < count; i++) AppendInPlace(items[i]);
    }

    T GetFirst() const override 
    {
        if (array.GetSize() == 0) throw std::out_of_range("Sequence is empty");
        return array.Get(0);
    }

    T GetLast() const override 
    {
        if (array.GetSize() == 0) throw std::out_of_range("Sequence is empty");
        return array.Get(array.GetSize() - 1);
    }

    T Get(int index) const override 
    {
        return array.Get(index);
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override 
    {
        if (startIndex < 0 || endIndex >= array.GetSize() || startIndex > endIndex) throw std::out_of_range("Invalid indices");
        ArraySequence<T>* subseq = new ArraySequence<T>();
        for (int i = startIndex; i <= endIndex; i++) subseq->AppendInPlace(array.Get(i));
        return subseq;
    }

    int GetLength() const override 
    {
        return array.GetSize();
    }

    Sequence<T>* Append(T item) const override 
    {
        ArraySequence<T>* result = new ArraySequence<T>(*this);
        result->AppendInPlace(item);
        return result;
    }

    Sequence<T>* Prepend(T item) const override 
    {
        ArraySequence<T>* result = new ArraySequence<T>();
        result->AppendInPlace(item);
        for (int i = 0; i < array.GetSize(); ++i) result->AppendInPlace(array.Get(i));
        return result;
    }

    Sequence<T>* InsertAt(T item, int index) const override 
    {
        if (index < 0 || index > array.GetSize()) throw std::out_of_range("Index out of range");
        ArraySequence<T>* result = new ArraySequence<T>();
        for (int i = 0; i < index; i++) result->AppendInPlace(array.Get(i));
        result->AppendInPlace(item);
        for (int i = index; i < array.GetSize(); i++) result->AppendInPlace(array.Get(i));
        return result;
    }

    Sequence<T>* Concat(Sequence<T>* other) const override 
    {
        ArraySequence<T>* result = new ArraySequence<T>(*this);
        for (int i = 0; i < other->GetLength(); i++) result->AppendInPlace(other->Get(i));
        return result;
    }

    // Реализация MutableSequence
    void AppendInPlace(T item) override
    {
        array.Append(item);
    }

    void PrependInPlace(T item) override 
    {
        array.Resize(array.GetSize() + 1);
        for (int i = array.GetSize() - 1; i > 0; i--)
            array.Set(i, array.Get(i - 1));
        array.Set(0, item);
    }

    void InsertAtInPlace(T item, int index) override 
    {
        if (index < 0 || index > array.GetSize()) throw std::out_of_range("Index out of range");
        array.Append(item);
        for (int i = array.GetSize() - 1; i > index; i--) array.Set(i, array.Get(i - 1));
        array.Set(index, item);
    }

private:
    DynamicArray<T> array;
};
