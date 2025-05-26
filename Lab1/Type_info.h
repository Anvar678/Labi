#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include <stdio.h>
#include <stdlib.h>
#include "Dm_elem.h"
#include "Complex.h"
#include "MyString.h"
#include "Person.h"

/*
тута лежит размер типа данных, реализация функций toString 
он как бы нужен для универсальных операций с элементом

*/

typedef struct 
{
    size_t size;
    char* (*toString)(void*);

} TypeInfo;

char* toString_INT(void* data); 

char* toString_DOUBLE(void* data);

char* toString_CHAR(void* data); 

char* toString_COMPLEX(void* data); 

char* toString_STRING(void* data);

char* toString_PERSON(void* data); 

extern TypeInfo type_info[];

#endif
