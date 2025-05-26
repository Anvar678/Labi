#include "Type_info.h"

char* toString_INT(void* data) 
{
    int value = *(int*)data;
    char* result = malloc(50);
    snprintf(result, 50, "INT,%d", value);
    return result;
}

char* toString_DOUBLE(void* data) 
{
    double value = *(double*)data;
    char* result = malloc(50);
    snprintf(result, 50, "DOUBLE,%.2lf", value);
    return result;
}

char* toString_CHAR(void* data) 
{
    char value = *(char*)data;
    char* result = malloc(20);
    snprintf(result, 20, "CHAR,%c", value);
    return result;
}

char* toString_COMPLEX(void* data) 
{
    Complex* c = (Complex*)data;
    char* result = malloc(50);
    snprintf(result, 50, "COMPLEX,%.2lf,%.2lf", c->rational_part, c->complex_part);
    return result;
}

char* toString_STRING(void* data) 
{
    String* s = (String*)data;
    char* result = malloc(100 + s->length);
    snprintf(result, 100 + s->length, "STRING,%d,%s", s->length, s->data);
    return result;
}

char* toString_PERSON(void* data) 
{
    Person* p = (Person*)data;
    char* result = malloc(100);
    snprintf(result, 100, "PERSON,%s,%s,%d,%d,%d",
             p->first_name->data, p->last_name->data,
             p->day, p->month, p->year);
    return result;
}

/*
массив структур TypeInfo тут индексированная инициализация.
Под каждый тип данных ставим свой размер и указтель на свой
тустринг

*/
TypeInfo type_info[] = 
{
    [INT]     = { sizeof(int),       toString_INT },
    [DOUBLE]  = { sizeof(double),    toString_DOUBLE },
    [CHAR]    = { sizeof(char),      toString_CHAR },
    [COMPLEX] = { sizeof(Complex),   toString_COMPLEX },
    [STRING]  = { sizeof(String),    toString_STRING },
    [PERSON]  = { sizeof(Person),    toString_PERSON },
};
