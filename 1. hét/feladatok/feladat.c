#include "myheader.h"

int main(int argc, char *argv[]){
    int returnValue = 0;
    if (argc < 3){
        fprintf(stderr, "I need more arguments!\n");
        return returnValue;
    }
    char *string;
    char *value;
    string = (char*)malloc(strlen(argv[1])+strlen(argv[2])+2);
    strcpy(string, argv[1]);
    strcat(string, "=");
    strcat(string, argv[2]);
    putenv(string);
    free(string);
    value = getenv(argv[1]);
    int x = atoi(value);
    if (x == 0){
        returnValue = timeFunc();
        
    }else{
        returnValue = randomGen(x);
    }
    return returnValue;
}