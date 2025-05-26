#ifndef PERSON_H
#define PERSON_H

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#include "MyString.h"

typedef struct _Person
{
    String *first_name; //1
    String *last_name; //2
    unsigned int day; //3
    unsigned int month; //4
    unsigned int year; //5

    /*
    добавить размер типов, чтобы убрать свичи
    
    */

}Person;

Person* createPerson(String *first_name, String *last_name, 
    unsigned int day, unsigned int month, unsigned int year);

char* get_information(Person* chel, unsigned int information_id); 

void Person_free(Person *chel);

#endif