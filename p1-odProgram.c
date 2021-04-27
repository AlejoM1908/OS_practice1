#include <stdio.h>
#include "lib/app/process.c"

int main(void)
{
    setbuf(stdout, NULL);
    startProgram();
    return 0;
}
