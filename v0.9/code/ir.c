/* This program polls a GPIO pin in order to reconstruct a IR code
 * The gpio pin has to be exported first, then can be polled onto
 * We use open(2), read(2) and close(2) instead of fopen(3), fgets(3) because it's a special file
 * For buffering reasons, it needs to be closed after each read (which is valid for writing, quid reading ?)
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>
#include "gpio.h"
#include "useful.h"

#define IR_PIN 64+8                      // gpio2_8                                  
#define MAX_BUF 64
#define NB_MSG 3

double ir_commands[NB_MSG][30] = {
{0.000948, 0.000860, 0.001808, 0.000834, 0.000951, 0.001736, 0.001807, 0.000858, 0.000927, 0.000857, 0.000917, 0.000877, 0.000927, 0.000833, 0.000955, 0.000853, 0.000928, 0.000856, 0.000927, 0.000831, 0.000953, 0.001700, 0.000925},
{0.000937, 0.000827, 0.000954, 0.000835, 0.001840, 0.001704, 0.001840, 0.000833, 0.000953, 0.000829, 0.000955, 0.000839, 0.000955, 0.000829, 0.000956, 0.000828, 0.000956, 0.000828, 0.000959, 0.001700, 0.001839},
{0.000953, 0.000826, 0.001843, 0.000826, 0.000978, 0.001681, 0.001844, 0.000825, 0.000960, 0.000824, 0.000960, 0.000834, 0.000961, 0.000824, 0.000963, 0.000821, 0.000960, 0.000824, 0.000960, 0.001696, 0.000960, 0.000827, 0.000908}
};
double message[50] = {0.0};
double translation_message[50] = {0.0};

void compare_signals(void)
{
    int i = 0, j=0 , same=1;
    
    memset((void*) translation_message, 0.0, sizeof(translation_message));
    while(message[i] != 0.0 && message[i+1]-message[i] < 0.01)
        {
        translation_message[i] = message[i+1]-message[i];
        i++;
        }
    
    for(j=0; j<NB_MSG; j++)
        {
        //printf("TESTING %d\n\n", j);
        same = 1;
        for(i=1; i<25; i++)
            {
            if((translation_message[i] > ir_commands[j][i]+0.0001 || translation_message[i] < ir_commands[j][i]-0.0001) && i != 2 && i != 4)
              {
              same = 0;  
              //printf("Failed to acknowledge %lf vs %lf\n", translation_message[i], ir_commands[j][i]);
              goto next_msg;
              }
            else
              {
              //printf("Acknowledge %lf vs %lf\n", translation_message[i], ir_commands[j][i]);
              }
            if(translation_message[i+1] == 0.0 && same)                          
                 {
                 printf("RECOGNIZED %d\n", j);
                 goto out;                                            
                 }
              next_msg:;                     
            }
        }
    out:;
    if(same == 0)
       {
       printf("Couldn't recognize : \n{");
       i=0;
       while(translation_message[i] != 0.0)
           {
           if(i==0) printf("%lf", translation_message[i]);
           else printf(", %lf", translation_message[i]);
           i++;
           }
    printf("}");
       }
       
}



int main()
{
    double t1, t2;
    double timeout1, timeout2, origin, compare, tmp;
    
    struct timeval time;
    struct pollfd fdset;
    char *buf[MAX_BUF];
    int gpio_fd, rc;
    int i = 0, j = 0, start = 1;
    FILE* mux;
    
    gpio_init(IR_PIN, 0);                // init the GPIO pin for IR
    gpio_set_edge(IR_PIN, "both");       // setting the edge to both means interrupt for any change of state
    gpio_fd = gpio_open_fd(IR_PIN);      // open the pin file descriptor
    
    
    while(1)
        {
        /*gettimeofday(&time, NULL);
        message[i] = time.tv_sec+(time.tv_usec/1000000.0);
        timeout2 = time.tv_sec+(time.tv_usec/1000000.0);*/
        memset((void*) &fdset, 0, sizeof(fdset));
        fdset.fd = gpio_fd;
        fdset.events = POLLPRI;
        
        if(start)
            sleep(1);
    
        rc = poll(&fdset, 1, 500);
        if(rc < 0)
            {
            printf("Poll failed\n");
            exit(1);
            }
        if(rc == 0)
            printf(".");
        if((fdset.revents & POLLPRI) && i<50)                                    // in case of interrupt (change of state)
            {
            (void) read(fdset.fd, buf, MAX_BUF);                                 
            gettimeofday(&time, NULL);
            message[i] = time.tv_sec+(time.tv_usec/1000000.0);                   // record the time 
            if(start)                                                            // if start (first value), record time of origin
                {
                origin = time.tv_sec+(time.tv_usec/1000000.0);
                start = 0;
                }
            //printf("%lf\n", message[i] - message[i-1]);
            i++;
            }
            
        gettimeofday(&time, NULL);
        compare = time.tv_sec+(time.tv_usec/1000000.0);
        if(compare - origin > 1 && !start)                                       // detect idle => save code
            {
            //printf("stop\n");
            if(message[3] != 0)                                                  // random test to verify there is proper data to show
                {
               // printf("proper message : \n");
               // printf("{");
                for(j=1; j<49; j++)
                    {
                    if(message[j] != 0)
                        {
                        tmp = message[j+1] - message[j];
                        if(j> 1 && tmp > 0.01) 
                            goto out;
                    //    printf("%lf, ", tmp);
                        }
                    }
              //  printf("}\n");
                }
            out: 
            compare_signals();
            memset((void*) message, 0, sizeof(message));
            start = 1;
            i = 0;
            }  
        //if(i >= 50)
        //    i=0;
          /*if(message[i] - message[i-1] > 0.01)//escape condition
            {
            for(i=1; i<50; i++)
                {
                printf("%lf\n", message[i] - message[i-1]);
                }
            printf("\n");   
            memset((void*) message, 0, sizeof(message));
            i = 0;
            //sleep(1);
            gettimeofday(&time, NULL);
            timeout1 = time.tv_sec+(time.tv_usec/1000000.0);
            printf("1\n");
            i = 0;
            }*/
        fflush(stdout);
        }
    
    close(gpio_fd);
    return 0;
}
