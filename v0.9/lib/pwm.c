#include "pwm.h"

/* Initialize PWM : 
1/ mmap /dev/mem to have write access to system clock 
2/ enable system clock (0x0 = disabled, 0x02 = enabled)
3/ set correct pin MUX */

void pwm_init(void)
{
    FILE *pwm_mux;
    int i;
    volatile uint32_t *epwmss1;
    
    int fd = open("/dev/mem", O_RDWR);
    
    if(fd < 0)
        {
        printf("Can't open /dev/mem\n");
        exit(1);
        }

    epwmss1 = (volatile uint32_t *) mmap(NULL, LENGTH, PROT_READ|PROT_WRITE, MAP_SHARED, fd, START);
    if(epwmss1 == NULL)
        {
        printf("Can't mmap\n");
        exit(1);
        }
    else
    	{
		epwmss1[OFFSET_1 / sizeof(uint32_t)] = 0x2;
		}
    close(fd);
    
    pwm_mux = fopen("/sys/kernel/debug/omap_mux/gpmc_a2", "w");
    fprintf(pwm_mux, "6");                                                      // pwm is mux mode 6
    fclose(pwm_mux);
}

void pwm_start(void)
{
    FILE *pwm_run;
    pwm_run = fopen("/sys/class/pwm/ehrpwm.1:0/run", "w");
    fprintf(pwm_run, "1");
    fclose(pwm_run);
}

void pwm_stop(void)
{
    FILE *pwm_run;
    
    pwm_run = fopen("/sys/class/pwm/ehrpwm.1:0/run", "w");
    fprintf(pwm_run, "0");
    fclose(pwm_run);
}

void pwm_set_duty(int duty_percent)
{
    FILE *pwm_duty;
    
    pwm_duty = fopen("/sys/class/pwm/ehrpwm.1:0/duty_percent", "w"); 
    fprintf(pwm_duty, "%d", duty_percent);
    fclose(pwm_duty);
}

void pwm_set_period(int freq)
{
    FILE *pwm_period;
    
    pwm_period = fopen("/sys/class/pwm/ehrpwm.1:0/period_freq", "w");
    fprintf(pwm_period, "%d", freq);
    fclose(pwm_period);
}
