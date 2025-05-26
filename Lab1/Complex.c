#include "Complex.h"

Complex *ComplexCreate(double complex_part, double rational_part)
{
    Complex *cn=(Complex*)malloc(sizeof(Complex));
    cn->complex_part=complex_part;
    cn->rational_part=rational_part;

    return cn;
}

Complex *ComplexSum(Complex *first_number, Complex *second_number)
{
    Complex *cn=ComplexCreate(first_number->complex_part+second_number->complex_part, 
                        second_number->rational_part+second_number->rational_part);
    
    return cn;
}

Complex *ComplexMinus(Complex *first_number, Complex *second_number)
{
    Complex *cn=ComplexCreate(first_number->complex_part-second_number->complex_part, 
        second_number->rational_part-second_number->rational_part);

    return cn;
}

Complex *ComplexMultiplication(Complex *first_number, Complex *second_number)
{
    Complex *cn=ComplexCreate( (first_number->rational_part*second_number->complex_part+second_number->rational_part*first_number->complex_part),
     (first_number->rational_part*second_number->rational_part+first_number->complex_part*second_number->complex_part) );

    return cn;

}

Complex *ComplexDivision(Complex *first_number, Complex *second_number)
{
    Complex *cn=ComplexCreate((first_number->complex_part*second_number->rational_part-first_number->rational_part*second_number->complex_part)/((second_number->complex_part)*(second_number->complex_part)+(second_number->rational_part)*(second_number->rational_part)),
     (first_number->rational_part*second_number->rational_part+first_number->complex_part*second_number->complex_part)/((second_number->complex_part)*(second_number->complex_part)+(second_number->rational_part)*(second_number->rational_part)));

    return cn;

}

void ComplexShow(Complex *n)
{
    double rational=n->rational_part;
    double complex=n->complex_part;
    printf("\n%lf + %lfi\n", complex, rational);

}

void Complexfree(Complex* n)
{
    free(n);
}
