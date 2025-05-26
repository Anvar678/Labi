#include "DM.h"
#include "Complex.h"
#include "MyString.h"
#include "Person.h"
#include "Dm_elem.h"
#include "Type_info.h"


DM *create() 
{
    DM *dm = (DM*)malloc(sizeof(DM));
    if (!dm) return NULL;
    dm->count = 0;
    dm->data = NULL;
    return dm; 
}

void push_back(DM *dm, void *el, data_t type) //----------------
{
    if (!dm || !el) return;

    size_t size = type_info[type].size;
    dm->count++;
    dm->data = (DM_Element*)realloc(dm->data, dm->count * sizeof(DM_Element));
    if (!dm->data) return;
    dm->data[dm->count - 1].data = malloc(size); //лезем в указатель на элемент чтобы под него выделить память
    memcpy(dm->data[dm->count - 1].data, el, size);
    dm->data[dm->count - 1].type = type;
    dm->data[dm->count - 1].toString = type_info[type].toString;
}

void *get(DM *dm, unsigned int index, data_t type) 
{
    if (!dm || index >= dm->count || dm->data[index].type != type) 
    {
        return NULL;
    }
    return dm->data[index].data;
}

void freedm(DM *dm) 
{
    if (!dm) return;
    for (unsigned int i = 0; i < dm->count; i++) 
    {
        free(dm->data[i].data);
    }
    free(dm->data);
    free(dm);
}

void add(DM *dm, unsigned int index, void *el, data_t type) //----------------------
{
    if (!dm || !el || index > dm->count) return;

    size_t size = type_info[type].size;
    dm->count++;
    dm->data = (DM_Element*)realloc(dm->data, dm->count * sizeof(DM_Element));
    memmove(&dm->data[index + 1], &dm->data[index], (dm->count - index - 1) * sizeof(DM_Element));
    dm->data[index].data = malloc(size);
    memcpy(dm->data[index].data, el, size);
    dm->data[index].type = type;
    dm->data[index].toString = type_info[type].toString;
}

void dell(DM *dm, unsigned int index) 
{
    if (!dm || index >= dm->count) return;
    
    free(dm->data[index].data);
    memmove(&dm->data[index], &dm->data[index + 1], (dm->count - index - 1) * sizeof(DM_Element));
    dm->count--;
    dm->data = (DM_Element*)realloc(dm->data, dm->count * sizeof(DM_Element));
}
