#include "MyString.h"

String *CreateString(unsigned int length, const char *initial_value) 
{
    String *str = (String *)malloc(sizeof(String));
    
    str->data = (char *)malloc((length + 1) * sizeof(char));
    
    str->length = length;
    strncpy(str->data, initial_value, length);
    str->data[length] = '\0'; // Гарантируем завершающий нулевой символ

    return str;
}

void StringShow(const String *str)
{
    if (str && str->data) 
    {
        printf("String: %s, Length: %u\n", str->data, str->length);
    }
    else printf("Error_Anvar\n");
}

void Stringfree(String *str)
{
    if (str) 
    {
        free(str->data);
        free(str);
    }
}
