#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int errno;

int main()
{
        int i;
        unsigned char *epwmss1;
        unsigned char val;

        int fd = open("/dev/mem",O_RDWR|O_SYNC);
        if(fd < 0)
                {
                printf("Can't open /dev/mem\n");
                return 1;
                }
        epwmss1 = (unsigned char *) mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x44e000cc);
        if(epwmss1 == NULL)
                {
                printf("Can't mmap\n");
                return 1;
                }
        else
                printf("0x2", epwmss1);
        close(fd);

        return 0;
}
