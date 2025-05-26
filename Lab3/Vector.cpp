#include <cmath>
#include <stdexcept>
#include "Sequence.cpp"

template <typename T>
class Vector : public ArraySequence<T>
{
public:
    Vector() : ArraySequence<T>() {}
    Vector(T* items, int count) : ArraySequence<T>(items, count) {}


    Vector<T> operator+(const Vector<T>& other) const
    {
        if (this->GetLength() != other.GetLength()) throw std::invalid_argument("Vectors must be of the same length");
        Vector<T> result;
        for (int i = 0; i < this->GetLength(); i++) result.AppendInPlace(this->Get(i) + other.Get(i));
        return result;
    }


    Vector<T> operator*(const T scalar) const
    {
        Vector<T> result;
        for (int i = 0; i < this->GetLength(); i++) result.AppendInPlace(this->Get(i) * scalar);
        return result;
    }


    T Dot(const Vector<T>& other) const
    {
        if (this->GetLength() != other.GetLength()) throw std::invalid_argument("Vectors must be of the same length");
        T sum = T();
        for (int i = 0; i < this->GetLength(); ++i)
            sum += this->Get(i) * other.Get(i);
        return sum;
    }


    double Norm() const
    {
        T sum = T();
        for (int i = 0; i < this->GetLength(); ++i) sum += this->Get(i) * this->Get(i);
        return std::sqrt(static_cast<double>(sum));
    }
};
