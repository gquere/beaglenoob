/*
This program interfaces a HD44780 controller via GPIO bitbanging, and therefore
uses the gpio library and the lcd library which contains the commands and timings
for such a controller. Here, numbers are simply written on the display, on one line.
It is to note that some pins need muxing because the way the LCD is wired in this
example pans along pins which are not natively configured as GPIO.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "gpio.h"
#include "useful.h"
#include "lcd.h"

#define DEBUG 1

// mode0 names for our pins
// tip : create a program which contains all the pins/modes names for transparent access
char mode0[][20]={"gpmc_ad7", "gpmc_ad3", "gpmc_oen_ren", "gpmc_wen", "gpmc_ad12", "gpmc_ad10",
        "gpmc_ad14", "gpmc_clk", "gpmc_csn2", "gpmc_ad5", "gpmc_ad1", "gpmc_csn0",
        "lcd_pclk", "lcd_hsync"};

void set_mux(void)
{
int i;
FILE* mux;
char source[64] = "/sys/kernel/debug/omap_mux/";

for(i=0; i<14; i++)
    {
    strcpy(source, "/sys/kernel/debug/omap_mux/");
    strcat(source, mode0[i]);
    mux = fopen(source, "w");
    if(mux == NULL)
        {
        printf("Failed to open mux");
        exit(1);
        }
    if( fprintf(mux, "7") < -1)
        {
        printf("Failed writing to mux");
        exit(1);
        }
    }
}

int main(void)
{
    int number = 48;    
    
    set_mux();
    gpio_init(db0, 1);
    gpio_init(db1, 1);
    gpio_init(db2, 1);
    gpio_init(db3, 1);
    gpio_init(db4, 1);
    gpio_init(db5, 1);
    gpio_init(db6, 1);
    gpio_init(db7, 1);
    gpio_init(rs,  1);
    gpio_init(rw,  1);
    gpio_init(e,   1);
    lcd_init();
    
    while(1)
        {
        sleep(1);
        lcd_write_sequence_data(number);
        number++;
        if(number > 48+10)
            {
            number = 48;
            lcd_write_sequence_command(1);
            }
        }
    
    return 0;
}

