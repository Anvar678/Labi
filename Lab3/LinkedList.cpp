#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList
{
public:
    struct Node
    {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };

    LinkedList() : head(nullptr), tail(nullptr), length(0) {}
    LinkedList(T* items, int count) : head(nullptr), tail(nullptr), length(0)
    {
        if (count < 0) throw std::invalid_argument("Count cannot be negative");
        for (int i = 0; i < count; ++i) Append(items[i]);
    }

    // Копирующий конструктор
    LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), length(0)
    {
        Node* cur = other.head;
        while (cur)
        {
            Append(cur->data);
            cur = cur->next;
        }
    }

    ~LinkedList()
    {
        while (head)
        {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    T GetFirst() const
    {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }

    T GetLast() const
    {
        if (!tail) throw std::runtime_error("List is empty");
        return tail->data;
    }

    T Get(int index) const
    {
        if (index < 0 || index >= length) throw std::out_of_range("Index out of range");
        Node* cur = head;
        for (int i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const
    {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex) throw std::out_of_range("Invalid indices");
        LinkedList<T>* sub = new LinkedList<T>();
        Node* cur = head;
        for (int i = 0; i < startIndex; ++i) cur = cur->next;
        for (int i = startIndex; i <= endIndex; ++i)
        {
            sub->Append(cur->data);
            cur = cur->next;
        }
        return sub;
    }

    int GetLength() const { return length; }

    void Prepend(T item)
    {
        Node* node = new Node(item);
        node->next = head;
        head = node;
        if (!tail) tail = head;
        length++;
    }

    void Append(T item)
    {
        Node* node = new Node(item);
        if (!head) head = tail = node;
        else
        {
            tail->next = node;
            tail = node;
        }
        length++;
    }

    void InsertAt(T item, int index)
    {
        if (index < 0 || index > length) throw std::out_of_range("Index out of range");
        if (index == 0) Prepend(item);
        else if (index == length) Append(item);
        else
        {
            Node* cur = head;
            for (int i = 0; i < index - 1; ++i) cur = cur->next;
            Node* node = new Node(item);
            node->next = cur->next;
            cur->next = node;
            length++;
        }
    }

    LinkedList<T>* Concat(LinkedList<T>* other) const
    {
        LinkedList<T>* res = new LinkedList<T>(*this);
        Node* cur = other->head;
        while (cur)
        {
            res->Append(cur->data);
            cur = cur->next;
        }
        return res;
    }

private:
    Node* head;
    Node* tail;
    int length;
};
