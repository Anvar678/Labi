#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MyString.h"
#include "DM.h"
#include "Complex.h"
#include "Person.h"
#include "Dm_elem.h"

void save_to_file(DM *arr, FILE *output) 
{
    for (int i = 0; i < arr->count; i++) 
    {
        DM_Element elem = arr->data[i];
        char* line = elem.toString(elem.data);
        fprintf(output, "%s\n", line);
        free(line);
    }
}

void *parse_data_by_type(FILE *input, char *type, data_t *parsed_type) 
{
    if (strcmp(type, "INT") == 0) 
    {
        int *value = malloc(sizeof(int));
        fscanf(input, "%d", value);
        *parsed_type = INT;
        return value;
    } 
    else if (strcmp(type, "CHAR") == 0) 
    {
        char *value = malloc(sizeof(char));
        fscanf(input, " %c", value);
        *parsed_type = CHAR;
        return value;
    } 
    else if (strcmp(type, "DOUBLE") == 0) 
    {
        double *value = malloc(sizeof(double));
        fscanf(input, "%lf", value);
        *parsed_type = DOUBLE;
        return value;
    } 
    else if (strcmp(type, "COMPLEX") == 0) 
    {
        double real, imag;
        fscanf(input, "%lf,%lf", &real, &imag);
        Complex *num = ComplexCreate(imag, real);
        *parsed_type = COMPLEX;
        return num;
    } 
    else if (strcmp(type, "STRING") == 0) 
    {
        int len;
        fscanf(input, "%d,", &len);
        char value[100];
        fscanf(input, "%99s", value);
        String *s = CreateString(len, value);
        *parsed_type = STRING;
        return s;
    } 
    else if (strcmp(type, "PERSON") == 0) 
    {
        char first[50], last[50];
        int day, month, year;
        fscanf(input, "%49[^,],%49[^,],%d,%d,%d", first, last, &day, &month, &year);
        String *first_name = CreateString(strlen(first), first);
        String *last_name = CreateString(strlen(last), last);
        Person *p = createPerson(first_name, last_name, day, month, year);
        *parsed_type = PERSON;
        return p;
    }
    return NULL;
}

int main() 
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    DM *arr = create();

    if (!input || !output) 
    {
        printf("Error opening file\n");
        return 1;
    }

    int count;
    fscanf(input, "%d", &count);  

    for (int i = 0; i < count; i++) 
    {
        char type[20];
        fscanf(input, " %[^,],", type);

        data_t perdt;
        void *data = parse_data_by_type(input, type, &perdt);
        if (!data) {
            printf("Error of var type\n");
            return 1;
        }

        push_back(arr, data, perdt);
    }

    unsigned int commands;
    fscanf(input, "%d", &commands);

    for (int i = 0; i < commands; i++) 
    {
        char cmd[20];
        fscanf(input, " %[^,],", cmd);

        if (strcmp(cmd, "p") == 0) {
            char type[20];
            fscanf(input, " %[^,],", type);

            data_t perdt;
            void *data = parse_data_by_type(input, type, &perdt);
            push_back(arr, data, perdt);

            printf("%s %s\n", cmd, type);
        } 
        else if (strcmp(cmd, "g") == 0) 
        {
            char type[20];
            int index;
            fscanf(input, "%[^,],%d", type, &index);
            printf("%s %s %d\n", cmd, type, index);
        } 
        else if (strcmp(cmd, "a") == 0) 
        {
            char type[20];
            fscanf(input, " %[^,],", type);

            data_t perdt;
            void *data = parse_data_by_type(input, type, &perdt);
            int index;
            fscanf(input, ",%d", &index);

            add(arr, index, data, perdt);
            printf("%s %s %d\n", cmd, type, index);
        } 
        else if (strcmp(cmd, "d") == 0) 
        {
            int index;
            fscanf(input, "%d", &index);
            dell(arr, index);
            printf("%s %d\n", cmd, index);
        } 
        else 
        {
            printf("Unknown command\n");
            return 1;
        }
    }

    save_to_file(arr, output);

    fclose(input);
    fclose(output);
    freedm(arr);

    return 0;
}
