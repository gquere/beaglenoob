#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <poll.h>
#include <fcntl.h>
#include "useful.h"


void gpio_init(int pin, int direction);
void gpio_write(int pin, int value);
int gpio_read(unsigned int pin);
void gpio_set_edge(unsigned int pin, char *edge);
int gpio_open_fd(unsigned int pin);