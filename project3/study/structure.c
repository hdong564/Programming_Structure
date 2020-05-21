#include <stdio.h>
#include <string.h>

int main(){

    struct Point2D {
        // put elements of structure point2D
        double x;
        double y;
    }; // need ; after declaring struct
        /* --------defined structure point2D----*/
    struct Point2D p1;
    p1.x = 4.0;
    p1.y = 2.2;
    struct Point2D *p2;
    p2 = &p1; // -> p2 is Point2D type pointer

    (*p2).x = 3.0;
    (*p2).y = 4.4;
    // value of pointer -> structure point2D
    /*---------same as ------*/
    p2 -> x = 3.0;
    p2 -> y = 4.4;
    printf("%lf\n", p2->x);
    printf("%lu", sizeof(p1));


    // make new definition of type 
    // int, double, float etc =-- are built in typedef
    typedef struct Point2D point2;
    point2 origin = {0,0};
    /* Dynamic Memory Management*/
    return 0;
}


