
#include "Person.h"

Person* createPerson(String *first_name, String *last_name, 
    unsigned int day, unsigned int month, unsigned int year)
{
    Person *p = (Person*)malloc(sizeof(Person));
    if (!p) return NULL;


    p->first_name = first_name;
    p->last_name = last_name;

    p->day = day;
    p->month = month;
    p->year = year;

    return p;
}

// Функция для получения информации
char* get_information(Person* chel, unsigned int information_id)
{
    //static чтобы буфер не пересоздавался каждый раз когда вызываем функцию
    static char buffer[12]; // Буфер для хранения чисел в виде строки 12 байт

    if (information_id == 1) return chel->first_name->data;
    if (information_id == 2) return chel->last_name->data;
    
    // Конвертируем числа в строку
    if (information_id == 3) 
    { 
        snprintf(buffer, sizeof(buffer), "%u", chel->day); 
        return buffer; 
    }

    if (information_id == 4) 
    { 
        snprintf(buffer, sizeof(buffer), "%u", chel->month); 
        return buffer; 
    }

    if (information_id == 5) 
    { 
        snprintf(buffer, sizeof(buffer), "%u", chel->year); 
        return buffer; 
    }

    return NULL; // Если идентификатор неправильный

    /*
    snprintf это как printf только результат пишется в буер
    buffer указатель на буфер куда запишем строку
    sizeof(buffer) размер буфера 
    "%u" это как в printf
    chel->day аргумент который я ставлю в %u

    */
}

// Функция освобождения памяти
void Person_free(Person *chel)
{
    if (chel) {
        Stringfree(chel->first_name);
        Stringfree(chel->last_name);
        free(chel); // Освобождаем саму структуру
    }
}