#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum terrain_type
{
    NOT_SET = -1,
    PATH = 1,
    CENTER = 2,
    MART = 3,
    TALL_GRASS = 4,
    BOULDERS = 5,
    CLEARING = 6,
    ROCKS = 7,
    TREES = 8,
};

struct room
{
    int position;
    int size;
};

void mapPrint(int map[21][80])
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            switch ((map[i][j]))
            {

            case NOT_SET:
                printf("*");
                break;
            case PATH:
                printf("#");
                break;
            case CENTER:
                printf("C");
                break;
            case MART:
                printf("M");
                break;
            case TALL_GRASS:
                printf(",");
                break;
            case BOULDERS:
                printf("%%");
                break;
            case CLEARING:
                printf(":");
                break;
            case ROCKS:
                printf("?"); //check piazza
                break;
            case TREES:
                printf("\"");
                break;
            }
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    int map[21][80];

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            map[i][j] = NOT_SET;
        }
    }

    for (int i = 0; i < 21; i += 20)
    {
        for (int j = 0; j < 80; j++)
        {
            map[i][j] = BOULDERS;
        }
    }

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 80; j += 79)
        {
            map[i][j] = BOULDERS;
        }
    }

    srand(time(NULL));

    int topExit = rand() % 80;
    map[0][topExit] = PATH;
    int bottomExit = rand() % 80;
    map[20][bottomExit] = PATH;

    int leftExit = rand() % 20;
    map[leftExit][0] = PATH;
    int rightExit = rand() % 20;
    map[rightExit][79] = PATH;

    

    mapPrint(map);

    return 0;
}
