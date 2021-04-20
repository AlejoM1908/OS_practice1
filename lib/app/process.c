#include <stdlib.h>

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
    if (processId == 0)
        childrenFunction(childrenPipes[1], parentPipes[0]);
    else
        parentFunction(parentPipes[1], childrenPipes[0]);
}

/**
 * The function childrenFunction is used to generate a new process that will search
 * for the average travel time into the document
 * @param pipeWrite where the process will send info to the other process
 * @param pipeRead where the process will read info from the other process
*/
void childrenFunction(int pipeWrite, int pipeRead){
    
}

/**
 * The function parentFunction is used to call the console application and send the
 * required data to the children process
 * @param pipeWrite where the process will send info to the other process
 * @param pipeRead where the process will read info from the other process
*/
void parentFunction(int pipeWrite, int pipeRead){

}

/**
 * The function checkErrors is used to verify if the fork and pipes where created
 * correctlly
 * @param processId is the id of the fork
 * @param pipesPointers is the array of both pipes
*/
void checkErrors(int processId, int pipesPointers[2]){
    for (int i=0; i<2; i++){
        if (pipesPointers[i] < 0){
            perror("Error en la generación de la pipe %d",i);
            exit(EXIT_FAILURE);
        }
    }

    if (processId == -1){
        perror("Error en la generación del fork");
        exit(EXIT_FAILURE);
    }
}