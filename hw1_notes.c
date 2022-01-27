

//80x21 region
//each terrain type, put random dots and seed them
//grow those points out
//iterate through and make them bigger and bigger, until they intersect
//this requires a queue
//paths can be along the terrain differences

//4 to 1 scale for the space, must grow/favor top to bottom when growing

//other option: easier
//plant the seeds but them give them a set size (square)
//overlaps just choose a size
//give them a set radius to just make that terrian
//paths are random strait lines, with one bend
//fill in the empty spaces with a terrian type

//paths must lign up tile to tile, for entrances and exits

//tiles are brought together with (doubly) linked list


//enum terrain_type{
//all the terrain types
//}

//struct
//room
//position size




struct foo
{
    int i;
    float f;
    char a[80];
};

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void swap(int *x, int *y);

int main(int argc, char const *argv[])
{
    struct foo f;

    f.i = 10;
    f.f = 3.14;
    strcpy(f.a, "String");


    srand(time(NULL));

    printf("%d\n", rand());
    printf("%d\n", rand());
    printf("%d\n", rand());
    printf("%d\n", rand());
    printf("%d\n", rand());
    printf("%d\n", rand());
    printf("%d\n", rand());

    printf("%d\n", rand() % 10 + 1);

    printf("%f\n", rand() / ((float)RAND_MAX));

    //             pointers
    // swap function

    int x, y;

    x = 0;
    y = 1;

    printf("%d, %d\n", x, y);
    swap(&x, &y);
    printf("%d, %d\n", x, y);

    return 0;
}

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}