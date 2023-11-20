#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    struct timeval tv_start, tv_end;
    double time_passed;

    // Get the current time before the delay
    gettimeofday(&tv_start, NULL);
    printf("Start time: %ld.%06ld seconds\n", tv_start.tv_sec, tv_start.tv_usec);

    // Delay for 1 second
    usleep(5000000);

    // Get the current time after the delay
    gettimeofday(&tv_end, NULL);
    printf("End time: %ld.%06ld seconds\n", tv_end.tv_sec, tv_end.tv_usec);

    // Calculate the time passed in milliseconds
    time_passed = (tv_end.tv_sec - tv_start.tv_sec) + (tv_end.tv_usec - tv_start.tv_usec) / 1000000.0;
    printf("Time passed: %.6f seconds\n", time_passed);

    return 0;
}