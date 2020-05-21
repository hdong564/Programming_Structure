#include <stdlib.h>
#include <stdio.h>

int main(){
    int *p1;
    p1 = (int *)malloc(sizeof(int));
    printf("%lu", sizeof(p1) );
    // why,,,? 
    /*Pointer variable size is not depending on data typ
    e as pointer always stores the address of other varia
    ble which is always integer data type.*/
    return 0;
}