#ifndef COMPLEX_H
#define COMPLEX_H


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>


typedef struct _complex //внутреннее имя 
{
    double complex_part;
    double rational_part;

}Complex;

Complex *ComplexCreate(double complex_part, double rational_part);

Complex *ComplexSum(Complex *first_number, Complex *second_number);

Complex *ComplexMinus(Complex *first_number, Complex *second_number);

Complex *ComplexMultiplication(Complex *first_number, Complex *second_number);

Complex *ComplexDivision(Complex *first_number, Complex *second_number);

void ComplexShow(Complex *n);

void Complexfree(Complex* n);

#endif