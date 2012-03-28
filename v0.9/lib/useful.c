#include "useful.h"
#include <time.h>

/**
 * Ansi C "itoa" based on Kernighan & Ritchie's "Ansi C"
 * Credits : http://eecs.wsu.edu/~sshaikot/source_codes/itoa-func.c
 */

void strreverse(char* begin, char* end) 
{
    char aux;
	while(end>begin)
		aux=*end, *end--=*begin, *begin++=aux;
}
	
void itoa(int value, char* str, int base) 
{
	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char* wstr=str;
	
	int sign;
	// Validate base
	if (base<2 || base>35){ *wstr='\0'; return; }
	// Take care of sign
	if ((sign=value) < 0) value = -value;
	// Conversion. Number is reversed.
	do *wstr++ = num[value%base]; while(value/=base);
	if(sign<0) *wstr++='-';
	*wstr='\0';
	
	// Reverse string
	strreverse(str,wstr-1);
}

void sleep_ns(long ns)
{
    struct timespec time;
    time.tv_sec = 0;
    time.tv_nsec = ns;
    if(nanosleep(&time, NULL) == -1)
        printf("sleep fail\n");
}
    
void sleep_us(long us)
{
    int j=0;
    for(j=0; j<us; j++)
        sleep_ns(1000);
}

void sleep_ms(long ms)
{
    int j=0;
    for(j=0; j<ms; j++)
        sleep_us(1000);
}
