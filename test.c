#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "gpio.h"

int main(int argc, char **argv){

    GPIO io;

    if(input(argc, argv, &io))
        return EXIT_FAILURE; 

    if(exportpin(&io))
        return EXIT_FAILURE;

    if(direction(&io))
        return EXIT_FAILURE;

    while(1)
    {
        usleep(10000);
        if(toggle(&io))
        return EXIT_FAILURE; 
    }

    if(unexport(&io))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;    
}
