#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct gpio {
    char *pin;
    char value[2];
    int fd;
}GPIO;

int input(int argc, char **argument, GPIO *p_io);
int exportpin(GPIO *p_io);
int direction(GPIO *p_io);
int toggle(GPIO *p_io);
int unexport(GPIO *p_io);


int input(int argc, char **argument, GPIO *p_io){
    
    if (argc != 3)
    {
        printf("Incorrect number of arguments entered!\n");
        exit(1);
    }

    p_io->pin = argument[1];

    if (strcasecmp(argument[2], "on") && strcasecmp(argument[2], "off")) 
    {
        printf("Invalid argument!\n");
        exit(1);
    }

    (!strcasecmp(argument[2],"on")) ? (strcpy(p_io->value, "1\0")) : (strcpy(p_io->value, "0\0"));

    return 0;
}

int exportpin(GPIO *p_io){

    if((p_io->fd = open("/sys/class/gpio/export", O_WRONLY)) == -1){
        printf("Unable to open /sys/class/gpio/export\n");
        return EXIT_FAILURE;
    }

    if((write(p_io->fd, p_io->pin, 2)) != 2){
        printf("Error writing to /sys/class/gpio/export\n");
        return EXIT_FAILURE;
    }
    
    close(p_io->fd);

    return EXIT_SUCCESS;
}

int direction(GPIO *p_io){
    
    if((p_io->fd = open("/sys/class/gpio/gpio24/direction", O_WRONLY)) == -1){
        printf("Unable to open /sys/class/gpio/gpio24/direction\n");
        return EXIT_FAILURE;
    }

    if ((write(p_io->fd, "out", 3) != 3)){
        printf("Error writing to /sys/class/gpio/gpio24/direction");
        return EXIT_FAILURE;
    }

    close(p_io->fd);

    return EXIT_SUCCESS;
}

int toggle(GPIO *p_io){
    
    if ((p_io->fd = open("/sys/class/gpio/gpio24/value", O_WRONLY)) == 1)
    {
        printf("Unable to open /sys/class/gpio/gpio24/value");
        return EXIT_FAILURE;
    }
    
    if((write(p_io->fd, p_io->value, 1)) != 1)
    {
        printf("Error writing to /sys/class/gpio/gpio24/value");
        return EXIT_FAILURE;
    }

    close(p_io->fd);
}

int unexport(GPIO *p_io){

    if ((p_io->fd = open("/sys/class/gpio/unexport", O_WRONLY)) == -1) {
        printf("Unable to open /sys/class/gpio/unexport");
        return EXIT_FAILURE;
    }

    if ((write(p_io->fd, p_io->pin, 2)) != 2) {
        printf("Error writing to /sys/class/gpio/unexport");
        return EXIT_FAILURE;
    }

    close(p_io->fd);

    return EXIT_SUCCESS;
}
