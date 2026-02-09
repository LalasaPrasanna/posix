#include <stdio.h>
#include <stdlib.h>
void crash(){
    int *ptr = NULL;
    *ptr = 2;
    printf("%d",*ptr); 
}
int main(){
    crash();
    return 0;
}