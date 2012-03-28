#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <fcntl.h>
#include "gpio.h"
#include "useful.h"

#define MAX_BUF 64

int main()
{
    struct pollfd fdset[2];
    char *buf[MAX_BUF];
    int gpio_fd, rc;
    
    gpio_init(70, 0);
    gpio_init(71, 1);
    gpio_set_edge(70, "rising");
    gpio_fd = gpio_open_fd(70);
    
    while(1)
        {
        memset((void*)fdset, 0, sizeof(fdset));
        fdset[0].fd = STDIN_FILENO;
        fdset[0].events = POLLIN;
        fdset[1].fd = gpio_fd;
        fdset[1].events = POLLPRI;
    
        rc = poll(fdset, 2, 3000);
        if(rc < 0)
            {
            printf("Poll failed\n");
            exit(1);
            }
        if(rc == 0)
            printf(".");
        if(fdset[1].revents & POLLPRI)
            {
            (void) read(fdset[1].fd, buf, MAX_BUF);
            printf("\npoll() GPIO %d interrupt", 70);
            }    
        if (fdset[0].revents & POLLIN) 
            {
			(void) read(fdset[0].fd, buf, 1);
			printf("\npoll() stdin read 0x%2.2X\n", (unsigned int) buf[0]);
		    }
        fflush(stdout);
        }
    
    close(gpio_fd);
    return 0;
}