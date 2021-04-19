#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool array_lenth(int number, char * charArray)
{
    int n = log10(number) + 1;
    
    if (n > sizeof(charArray))
    {
        return false;
    }
    else
    {
        return true;
    }
    
}

void print_array(char * Array)
{
    for (int i = 0; i < sizeof(Array); i++)
    {
        printf("%c", Array[i]);
    }
    
    printf("\n");
}

void clear_stream(FILE *in)
{
    int ch;
    
    clearerr(in);
    
    do
        ch = getc(in);
    while (ch != '\n' && ch != EOF);
    
    clearerr(in);
}

void display_welcome()
{
    printf("##########################################\n");
    printf("### Binevenido al sistema de busqueda. ###\n");
    printf("##########################################\n\n");
}

char * input_source_ID(char * sourceid, int sourceidN)
{
    bool exit = false;

    while (exit == false)
    {
        printf("\nPor favor, ingrese la ID de origen: ");

        if (scanf("%d", &sourceidN) != 1)
        {
            clear_stream(stdin);
            printf("La ID ingresada no es valida. \n\n");
            fflush(stdout);
        }
        else if (array_lenth(sourceidN, sourceid) == false)
        {
            printf("El tamaño del id no es el correcto.\n");
        }
        else
        {
            sprintf(sourceid, "%1d", sourceidN);
            exit = true;
        }
    }

    exit = false;

    return sourceid;
}

char * input_desnity_ID(char * destid, int destidN)
{
    bool exit = false;

    while (exit == false)
    {
        printf("\nPor favor, ingrese la ID de destino: ");

        if (scanf("%d", &destidN) != 1)
        {
            clear_stream(stdin);
            printf("La ID ingresada no es valida. \n\n");
            fflush(stdout);
        }
        else if (array_lenth(destidN, destid) == false)
        {
            printf("El tamaño del ID no es el correcto.\n");
        }
        else
        {
            sprintf(destid, "%1d", destidN);
            exit = true;
        }
    }

    exit = false;

    return destid;
}

char * input_daytime(char * daytime, int daytimeN)
{
    bool exit = false;

    while (exit == false)
    {
        printf("\nPor favor, ingrese La hora en que desea coger el transporte, en formato 24h. ");

        if ((scanf("%d", &daytimeN) != 1) && daytimeN < 0 && daytimeN > 24)
        {
            clear_stream(stdin);
            printf("La hora ingresada no es valida. \n\n");
            fflush(stdout);
        }
        else if (array_lenth(daytimeN, daytime) == false)
        {
            printf("El tamaño del id no es el correcto.\n");
        }
        else
        {
            sprintf(daytime, "%1d", daytimeN);
            exit = true;
        }
    }

    exit = false;

    return daytime;
}

void output_mean_time(int mean_travel_time)
{
    printf("La hora promedio del viaje es: %d", mean_travel_time);
}

int main(int argc, char const *argv[])
{
    bool exit = false;

    int sourceidN = 0;
    int destidN = 0;
    int daytimeN = 0;
    int mean_travel_timeN = 0;

    char sourceid[5];
    char destid[5];
    char daytime[2];
    char mean_travel_time[10];


    print_array(input_source_ID(sourceid, sourceidN));
    print_array(input_desnity_ID(destid, destidN));
    print_array(input_daytime(daytime, daytimeN));

    //Aca va la funcion de busqueda:

    //output_mean_time(mean_travel_time);

    return 0;
}
