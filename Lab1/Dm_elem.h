#ifndef DM_ELEM_H
#define DM_ELEM_H

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

typedef enum 
{
    INT,
    DOUBLE,
    CHAR,
    COMPLEX,
    STRING,
    PERSON
} data_t;

typedef struct _DM_Element
{
    void *data;            // указатель на элемент
    data_t type;           // тип элемента 
    char* (*toString)(void*); // указатель на функцию преобразования элемента в строку
    
} DM_Element;

#endif
