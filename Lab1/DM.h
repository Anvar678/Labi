#ifndef DM_H
#define DM_H

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#include "Dm_elem.h"

typedef struct _Dinam_Massive
{
    unsigned int count; // количество элементов
    DM_Element *data; // указатель на динамический массив элементов
} DM;


DM *create();

void push_back(DM *dm, void *el, data_t type);

void *get(DM *dm, unsigned int index, data_t type);

void freedm(DM *dm);

void add(DM *dm, unsigned int index, void *el, data_t type);

void dell(DM *dm, unsigned int index);

#endif
