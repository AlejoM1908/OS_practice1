#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "Console_outputs.c"
#include "../Structures/hash_table.c"

/**
 * The function checkErrors is used to verify if the fork and pipes where created
 * correctlly
 * @param processId is the id of the fork
 * @param pipesPointers is the array of both pipes
*/
void checkErrors(int processId, int pipesPointers[2]){
    for (int i=0; i<2; i++){
        if (pipesPointers[i] < 0){
            // Generating the corresponding error message for pipe error
            char message[] = "Error en la generación de la pipe ";
            strcat(message, (char*) &i);
            perror(message);
            exit(EXIT_FAILURE);
        }
    }

    // Generating the corresponding error message for the fork
    if (processId == -1){
        perror("Error en la generación del fork");
        exit(EXIT_FAILURE);
    }
}

void loadHash(HashTable* hash){
    FILE* file = fopen("lib/data/hashData.txt", "r");
    int key;
    long int data;
    char buffer[20];
    char* token;

    if (file == NULL){
        perror("No se pudo encontrar el archivo del hash para fopen");
        exit(EXIT_FAILURE);
    }

    while(fgets(buffer, 20, file) != NULL){
        token = strtok(buffer,",");
        key = atoi(token);
        token = strtok(NULL,",");
        data = (long int) atoi(token);

        if (!exist(hash,key)){
            insert(hash, key, data);
        }
    }
}

/**
 * The function searchInFile is used to search the file pointer in the HashTable and
 * find the mean travel time in the file
 * @param table is the Hash Table to make process faster
 * @param source is the id of the sorce zone of the travel
 * @param dest is the id of the destination zone of the travel
 * @param hour is the hour of the day where the travel start
 * @return the mean time for the given data
*/
int searchInFile(HashTable* table, int source, int dest, int hour){
    FILE* file = fopen("lib/data/data.txt", "r");
    int check, src, dst, time, mean_time;
    char buffer[30];
    char* token;

    if (file == NULL){
        perror("No se pudo encontrar el archivo para fopen");
        exit(EXIT_FAILURE);
    }

    if (!exist(table,source)){
        perror("No se encontro el id de destino en la Hash Table");
        exit(EXIT_FAILURE);
    }

    long int pointer = get(table, source);

    if (pointer < 0) return -1;

    check = fseek(file, pointer, SEEK_SET);

    if (check < 0){
        perror("No se pudo desplazar el puntero con fseek");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, 30, file) != NULL){
        token = strtok(buffer,",");
        src = atoi(token);
        token = strtok(NULL,",");
        dst = atoi(token);
        token = strtok(NULL,",");
        time = atoi(token);
        token = strtok(NULL,",");
        mean_time = atoi(token);

        if (src != source) return -1;
        else if (dst == dest && time == hour) return mean_time;
    }
}

/**
 * The function childrenFunction is used to generate a new process that will search
 * for the average travel time into the document
 * @param pipeWrite where the process will send info to the other process
 * @param pipeRead where the process will read info from the other process
*/
void childrenFunction(int pipeWrite, int pipeRead){
    // Allocating the needed memory
    HashTable* table = initHash();
    int source, destiny, time, check, data;
    bool exit = false;

    loadHash(table);
    printf("carga del hash -> %s", size(table));

    // Generaing a loop for keep the program runing until the user stops it
    while(!exit){
        // Receiving the data from the user to search
        read(pipeRead, &source, sizeof(int));
        read(pipeRead, &destiny, sizeof(int));
        read(pipeRead, &time, sizeof(int));

        // Searching for the data in the file
        data = searchInFile(table, source, destiny, time);

        // Sending mean time back to user
        write(pipeWrite, &data, sizeof(data));
        // Reading if the user stops the program
        read (pipeRead, &check, sizeof(int));

        if (check == -1)
            exit = true;
    }
}

/**
 * The function parentFunction is used to call the console application and send the
 * required data to the children process
 * @param pipeWrite where the process will send info to the other process
 * @param pipeRead where the process will read info from the other process
*/
void parentFunction(int pipeWrite, int pipeRead){
    // Allocating the needed memory
    bool exit = false;
    int data;
    
    display_welcome();

    // Generaing a loop for keep the program runing until the user stops it
    while (!exit){
        // Getting data from user and sending it to searching process
        data = input_source_ID();
        write(pipeWrite, &data, sizeof(data));
        data = input_destiny_ID();
        write(pipeWrite, &data, sizeof(data));
        data = input_daytime();
        write(pipeWrite, &data, sizeof(data));

        // Waiting for responce from the child process
        system("clear");
        printf("procesando, espere un momento ...\n");
        int time;
        read(pipeRead, &time, sizeof(int));

        // Printing the mean time founded or the notFound error
        system("clear");
        output_mean_time(time);

        // Asking if the user want to find another value
        exit = exitProgram();
        
        if (exit){
            data = -1;
            write(pipeWrite, &data, sizeof(data));
        }
        else{
            data = 0;
            write(pipeWrite, &data, sizeof(data));
        }
    }
}

/**
 * The function startProram is used to run the whole program, witch compose all
 * the code blocks, the processes and the pipes
*/
void startProgram(){
    // Creating all the memory for the forks and pipes
    int pipesPointers[2], parentPipes[2], childrenPipes[2];
    pid_t processId;
    
    // Creating pipes and forks
    pipesPointers[0] = pipe(parentPipes);
    pipesPointers[1] = pipe(childrenPipes);
    processId = fork();
    checkErrors(processId, pipesPointers);

    // Spliting the code that witch process will execute
    if (processId == 0){
        close(childrenPipes[0]);
        close(parentPipes[1]);
        childrenFunction(childrenPipes[1], parentPipes[0]);
    }
    else{
        close(childrenPipes[1]);
        close(parentPipes[0]);
        parentFunction(parentPipes[1], childrenPipes[0]);
    }
}
