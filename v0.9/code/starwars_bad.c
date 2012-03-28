#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>

#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

int fd;
FILE *gpio_export, *gpio_unexport, *gpio_direction, *gpio_value, *pwm_mux;
int pid[2];


void beep(freq, duration)
{
    uint i = 0;
	long time_btwn_flips = (40*1000/freq);
	long time_to_play = (long)(duration*40*40)/time_btwn_flips/3;

	while(i<time_to_play)
		{
		if(i%2) fprintf(gpio_value, "0");
		else fprintf(gpio_value, "1");
		fflush(gpio_value);
		usleep(time_btwn_flips);
		i++;
		}
    fprintf(gpio_value, "0");
    fflush(gpio_value);
	usleep(100*1000);
}

int main(int argc, char** argv[])
{
    pwm_mux = fopen("/sys/kernel/debug/omap_mux/gpmc_a2", "w");
    if(pwm_mux == NULL)
		{
		printf("mux open failed\n");
		exit(1);
		}
    fprintf(pwm_mux, "7");                                                      // pwm is mux mode 6
    fclose(pwm_mux);
	//sched_setscheduler(1, SCHED_FIFO, NULL);

	gpio_export = fopen("/sys/class/gpio/export", "w");
	if(gpio_export == NULL)
		{
		printf("gpio export open failed\n");
		exit(errno);
		}
	fprintf(gpio_export, "50");
	fclose(gpio_export);

	gpio_direction = fopen("/sys/class/gpio/gpio50/direction", "w");
	fprintf(gpio_direction, "out");
	fclose(gpio_direction);

	gpio_value = fopen("/sys/class/gpio/gpio50/value", "w");
	if(gpio_value == NULL)
		{
		printf("gpio value open failed\n");
        exit(1);
		}
	
	beep(a, 500);
    	beep(a, 500);
    	beep(a, 500);
    	beep(f, 350);
    	beep(cH, 150);  
    	beep(a, 500);
    	beep(f, 350);
    	beep(cH, 150);
    	beep(a, 650);
 
	usleep(150*1000);
	//end of first bit   

	beep(eH, 500);
	beep(eH, 500);
	beep(eH, 500);   
	beep(fH, 350);
	beep(cH, 150);
	beep(gS, 500);
	beep(f, 350);
	beep(cH, 150);
	beep(a, 650);

	usleep(150*1000);
	//end of second bit...  

	beep(aH, 500);
	beep(a, 300);
	beep(a, 150);
	beep(aH, 400);
	beep(gSH, 200);
	beep(gH, 200); 
	beep(fSH, 125);
	beep(fH, 125);    
	beep(fSH, 250);

	usleep(250*1000);

	beep(aS, 250); 
	beep(dSH, 400); 
	beep(dH, 200);  
	beep(cSH, 200);  
	beep(cH, 125);  
	beep(b, 125);  
	beep(cH, 250);  

	usleep(250*1000);

	beep(f, 125);  
	beep(gS, 500);  
	beep(f, 375);  
	beep(a, 125);
	beep(cH, 500);
	beep(a, 375);  
	beep(cH, 125);
	beep(eH, 650);

	//end of third bit... (Though it doesn't play well)
	//let's repeat it

	beep(aH, 500);
	beep(a, 300);
	beep(a, 150);
	beep(aH, 400);
	beep(gSH, 200);
	beep(gH, 200);
	beep(fSH, 125);
	beep(fH, 125);    
	beep(fSH, 250);

	usleep(250*1000);

	beep(aS, 250);  
	beep(dSH, 400);  
	beep(dH, 200);  
	beep(cSH, 200);  
	beep(cH, 125);  
	beep(b, 125);  
	beep(cH, 250);      

	usleep(250*1000);

	beep(f, 250);  
	beep(gS, 500);  
	beep(f, 375);  
	beep(cH, 125);
	beep(a, 500);   
	beep(f, 375);   
	beep(cH, 125); 
	beep(a, 650);   
	//end of the song

	gpio_unexport = fopen("/sys/class/gpio/unexport", "w");
	fprintf(gpio_unexport, "70");

	fclose(gpio_value);
	fclose(gpio_unexport);

return 0;
}
