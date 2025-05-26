#include <iostream>
#include "Vector.cpp"
#include "Complex.cpp"

using namespace std;

template <typename T>
void printVector(const Vector<T>& v)
{
    for (int i = 0; i < v.GetLength(); i++) cout << v.Get(i) << " ";
    cout << endl;
}

void printComplex(const Complex c)
{
    cout << c.Real() << " " << c.Imag()<<endl;
}

int main()
{
    Complex c1(1, 2);
    Complex c2(3, 4);
    printComplex(c2);
    Complex c3(5, 6);
    printComplex(c1 + c2);

    Complex items0[] = { c1, c2, c3 };
    double items1[] = { 1.0, 2.0, 3.0 };
    double items2[] = { 4.0, 5.0, 6.0 };

    Vector<Complex> v0(items0, 3);
    Vector<double> v1(items1, 3);
    Vector<double> v2(items2, 3);

    cout << "v1: "; 
    printVector(v1);
    cout << "v2: "; 
    printVector(v2);


    auto v3 = v1 + v2;
    cout << "v1 + v2: "; 
    printVector(v3);

    auto v4 = v1 * 2.0;
    cout << "v1 * 2: "; 
    printVector(v4);

    Complex items00[] = { c1, c2, c3 };
    Vector<Complex> v00(items00, 3);
    auto v5 = v0+v00;

    cout << "Dot(v1, v2): " << v1.Dot(v2) << endl;
    cout << "Norm(v1): " << v1.Norm() << endl;
    return 0;
}
