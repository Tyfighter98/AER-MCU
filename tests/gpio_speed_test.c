#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pigpio.h>
#include <time.h>
#include <string.h>

/*
 * GPIO Speed Test
 *
 * Description: This program is designed to test the speed at which we
 * sample the GPIO on the raspberry pi
 * 
 * Compile Command: gcc -o gpio_speed.out gpio_speed_test.c -lpigpio 
*/
int main() {
	if (!(gpioInitialise() < 0)) {
		FILE *f = fopen("../test_results/speed_test.txt", "w");
		if (f == NULL) {
			printf("Error reading file!\n");
			exit(1);
		}
		time_t rawtime;
		struct tm * timeinfo;
		int data;
		char *timestamp;
		while (1) {
			time (&rawtime);
			timeinfo = localtime (&rawtime);
			timestamp = asctime (timeinfo);
			timestamp[strlen(timestamp) - 1] = 0;
			data = gpioRead(2);
			//printf("[%s] GPIO 2: %d\n", timestamp, data);
			fprintf(f,"[%s] GPIO 2: %d\n", timestamp, data);
		}
	}
	return 0;
}

