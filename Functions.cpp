#include "Functions.h"

char* printf(char* specifier, char* str) {
    char tmp[(sizeof(specifier)/sizeof(char))+(sizeof(str)/sizeof(char))];
    sprintf(tmp, specifier, str);
    return tmp;
}

char* printf(char* specifier, char car) {
    char tmp[(sizeof(specifier)/sizeof(char))];
    sprintf(tmp, specifier, str);
    return tmp;
}

char* printf(char* specifier, int number) {

}

char* printf(char* specifier, float number);
char* printf(char* specifier, long long int number);
