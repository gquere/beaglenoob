#include "lcd.h"

int databits[] = {db7, db6, db5, db4, db3, db2, db1, db0};

/*
Write data directly on the pins to the LCD display, on 8 bits
*/
/*void lcd_write_data(int decvalue)
{
    int i = 0;
    int k = 128;
    
    printf("VALUE : %d\n", decvalue);
    while(decvalue > 0)
        {
        if(decvalue - k >= 0)
            {
            gpio_write(databits[i], HIGH);
            printf("%d HIGH\n", i);
            decvalue -= k;
            }
        else
            gpio_write(databits[i], LOW);
        i++;
        k=k/2;
        }
    printf("\n\n");
}*/


void lcd_write_data(int decvalue)
{
    if(decvalue - 128 >= 0)
        {
        gpio_write(db7, HIGH);
        decvalue -= 128;
        }
    else gpio_write(db7, LOW);
    if(decvalue - 64 >= 0)
        {
        gpio_write(db6, HIGH);
        decvalue -= 64;
        }
    else gpio_write(db6, LOW);
    if(decvalue - 32 >= 0)
        {
        gpio_write(db5, HIGH);
        decvalue -= 32;
        }
    else gpio_write(db5, LOW);
    if(decvalue - 16 >= 0)
        {
        gpio_write(db4, HIGH);
        decvalue -= 16;
        }
    else gpio_write(db4, LOW);
    if(decvalue - 8 >= 0)
        {
        gpio_write(db3, HIGH);
        decvalue -= 8;
        }
    else gpio_write(db3, LOW);
    if(decvalue - 4 >= 0)
        {
        gpio_write(db2, HIGH);
        decvalue -= 4;
        }
    else gpio_write(db2, LOW);
    if(decvalue - 2 >= 0)
        {
        gpio_write(db1, HIGH);
        decvalue -= 2;
        }
    else gpio_write(db1, LOW);
    if(decvalue - 1 >= 0)
        {
        gpio_write(db0, HIGH);
        decvalue -= 1;
        }
    else gpio_write(db0, LOW);
}

/*
This function writes a command to the LCD controller, by setting the appropriate
pins (e, rs), sending data characterising the command to run (such as clear screen)
signaling the new command (pin e)to be read in ~450ns and giving time to the 
system to react (5 ms) to the command given
*/
void lcd_write_sequence_command(int decvalue)
{
    gpio_write(e, LOW);
    gpio_write(rs, LOW);
    lcd_write_data(decvalue);
    gpio_write(e, HIGH);
    sleep_ns(450);
    gpio_write(e, LOW);
    sleep_ms(5);
}

/*
Quite similarly, this function writes data to the LCD controller, except rs is 
set HIGH this time and the time to wait for the system to react is 200 µs
*/
void lcd_write_sequence_data(int decvalue)
{
    gpio_write(e, LOW);
    gpio_write(rs, HIGH);
    lcd_write_data(decvalue);
    gpio_write(e, HIGH);
    sleep_ns(450);
    gpio_write(e, LOW);
    sleep_us(200);
}

/*
The init. of the lcd is based mostly on a series of commands that need to be sent
in somewhat precise timings. Check the datasheet to know what command (5,8,1,6,12)
does what.
*/
void lcd_init(void)
{
    sleep_ms(20);
    lcd_write_data(48);
    gpio_write(rs, LOW);
    sleep_ms(5);
    
    lcd_write_data(48);
    gpio_write(rs, LOW);
    sleep_us(200);
    
    lcd_write_data(48);
    gpio_write(rs, LOW);
    sleep_us(200);
    
    lcd_write_sequence_command(5);    // 5= 1line, 56=2lines
    lcd_write_sequence_command(8);
    lcd_write_sequence_command(1);
    lcd_write_sequence_command(6);
    lcd_write_sequence_command(12);
}
