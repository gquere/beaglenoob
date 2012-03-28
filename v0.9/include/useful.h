#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


void strreverse(char* begin, char* end);
void itoa(int value, char* str, int base);
void sleep_ns(long ns);
void sleep_us(long us);
void sleep_ms(long ms);
