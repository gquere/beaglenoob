#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define HIGH 1
#define LOW  0
#define db7  64+3
#define db6  64+4
#define db5  32+12
#define db4  26
#define db3  32+14
#define db2  64+1
#define db1  32+31
#define db0  32+5
#define e    32+1
#define rw   32+29
#define rs   64+24

// Write data to a LCD (pins db7...db0)
void lcd_write_data(int decvalue);
// Write a sequence which is a command (pins rs, e and lcd_write_data)
void lcd_write_sequence_command(int decvalue);
// Write a sequence which is data (pins rs, e and lcd_write_data)
void lcd_write_sequence_data(int decvalue);
// Initing the LCD makes use of the functions above
void lcd_init(void);
