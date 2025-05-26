#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

typedef struct _string
{
    char *data;         // указатель на начало строки в памяти
    unsigned int length; // длина строки
} String;

String *CreateString(unsigned int length, const char *initial_value);
void StringShow(const String *str);
void Stringfree(String *str);

#endif