#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int timeFunc(){
    time_t act_time;
    struct tm *timenow;
    timenow = localtime(&act_time);
    printf("The time is: %d-%d-%d-%d:%d:%d\n", (*timenow).tm_year+1900, (*timenow).tm_mon, (*timenow).tm_mday, (*timenow).tm_hour, (*timenow).tm_min, (*timenow).tm_sec);
    return 1;
}

int randomGen(int x){
    int sum = 0;
    srand(time(NULL));
    for (int i=0; i < x; i++){
        sum += rand()%x;
    }
    return sum/x;
}

