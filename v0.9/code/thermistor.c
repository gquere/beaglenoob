/*
This C program returns the temperature in K read on the sensor after being transformed.
What we actually read is a voltage (value), which we convert to a resistance (R)
which then gives the temperature (temp).
Temp is calculated using Steinhart and Hart's law, with the coefficients given
in the datasheet.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "useful.h"
#include "gpio.h"

#define thermistor_pin ain4
#define MAX_BUF 64

double main(int argc, char *argv[])
{
    int fd_ad, tmp;
    double value;
    double R, Rref = 6800;
    double temp;
    char buf[MAX_BUF];

    fd_ad = open("/sys/devices/platform/tsc/ain4", O_RDONLY, S_IREAD);
    if(fd_ad < 0)
	{
	printf("Couldn't open /sys/devices/platform/tsc/ain4\n");
	exit(1);
	}
    if(read(fd_ad, buf, MAX_BUF) == -1)
	{
	printf("Couldn't read from /sys/devices/platform/tsc/ain4\n");
	exit(1);
	}
    else
	{
        tmp = atoi(buf);
        value = tmp;
        // calculate R from value
	R = (double)(value*1.8*22000.0)/(4096.0*(3.6-(double)(value*1.8)/4096.0));
        // calculate temp from R
	temp = 1.0/(0.003354016+0.0002569850*log(R/6800.0)+2.62013*pow(10, -6)*log(R/6800.0)*log(R/6800.0)+6.38309*pow(10, -8)*log(R/6800.0)*log(R/6800.0)*log(R/6800.0));
	}
    printf("%lf\n",temp); 
    close(fd_ad);
    return temp;
}
