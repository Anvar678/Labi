#include <stdexcept>
#include <functional>
#include <algorithm>

template <typename T>
class DynamicArray
{
private:
    T* data = nullptr;
    int capacity = 0;
    int size = 0;

    void reallocate(int new_capacity)
    {
        if (new_capacity < size) new_capacity = size;
        if (new_capacity == capacity) return;

        T* new_data = new T[new_capacity];
        for (int i = 0; i < size; i++) new_data[i] = std::move(data[i]);

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    // Конструкторы
    DynamicArray() : data(new T[1]), capacity(1), size(0) {}

    DynamicArray(int initial_size): capacity(initial_size > 0 ? initial_size : 1), size(initial_size)
    {
        data = new T[capacity];
        for (int i = 0; i < size; i++) data[i] = T();
    }

    // Копирующий конструктор
    DynamicArray(const DynamicArray& other)
        : capacity(other.capacity), size(other.size)
    {
        data = new T[capacity];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
    }

    // Оператор присваивания
    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this != &other)
        {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        return *this;
    }

    // Деструктор
    ~DynamicArray()
    {
        delete[] data;
    }

    // Метод Reserve - резервирует память без изменения размера
    void Reserve(int new_capacity)
    {
        if (new_capacity > capacity) reallocate(new_capacity);
    }

    // Методы доступа
    T Get(int index) const
    {
        if (!data || index < 0 || index >= size) throw std::out_of_range("Index out of range or array not initialized");
        return data[index];
    }

    void Set(int index, T value)
    {
        if (!data || index < 0 || index >= size) throw std::out_of_range("Index out of range or array not initialized");
        data[index] = value;
    }

    // Методы управления размером
    void Resize(int new_size)
    {
        if (new_size < 0) throw std::invalid_argument("Size cannot be negative");
        if (new_size > capacity) reallocate(std::max(new_size, capacity * 2));
        size = new_size;
    }

    void Append(T item)
    {
        if (size >= capacity) reallocate(capacity == 0 ? 1 : capacity * 2);
        data[size++] = item;
    }

    int GetSize() const { return size; }
    int GetCapacity() const { return capacity; }

    // Простой сортировщик пузырьком
    void SortInPlace(const std::function<bool(const T&, const T&)>& comparator = [](const T& a, const T& b) { return a < b; })
    {
        for (int i = 0; i < GetSize(); ++i)
        {
            for (int j = 0; j < GetSize() - i - 1; ++j)
            {
                if (!comparator(Get(j), Get(j + 1)))
                {
                    T tmp = Get(j);
                    Set(j, Get(j + 1));
                    Set(j + 1, tmp);
                }
            }
        }
    }
};
