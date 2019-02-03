/*Considere a definição apresentada do tipo struct hmstime e desenvolva a função sumtimes, que soma os
tempos dos ntimes elementos do array times e deixa o resultado, devidamente transformado, na instância de
struct hmstime referida por res.
Nota: use o comando man gettimeofday para obter a definição da estrutura timeval.
*/
#include <sys/time.h>
#include <stdio.h>
#include <stddef.h>

struct hmstime{
    unsigned short hours;
    unsigned char minutes;
    unsigned char seconds;
};


void sumtimes(struct hmstime *res, const struct timeval times[], size_t ntimes);

int main(){
    struct timeval t[]={
        {.tv_sec=400, .tv_usec=1200000},
        {.tv_sec=7000, .tv_usec=3400000},
        {.tv_sec=11000, .tv_usec=800000},
    };
    struct hmstime res;
    struct hmstime *resP = &res;
    sumtimes(resP, t, 3);
    printf("seconds:%d minutes:%d hours:%d\n", res.seconds, res.minutes, res.hours);
    return 1;
}

void sumtimes(struct hmstime *res, const struct timeval times[], size_t ntimes){
    int microseconds = 0;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    for (int i; i < ntimes; i++){
        microseconds += times[i].tv_usec;
        seconds += times[i].tv_sec;
    }
    if (microseconds > 1000000) seconds += microseconds/1000000;
    if (seconds>60) {
        minutes = seconds/60;
        seconds %= 60;
    }
    if (minutes>60) {
        hours = minutes/60;
        minutes %= 60;
    }
    res->hours = hours;
    res->minutes = minutes;
    res->seconds = seconds;
}
