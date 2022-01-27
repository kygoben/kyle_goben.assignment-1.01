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
                printf(".");
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
            map[i][j] = -1;
        }
    }

    srand(time(NULL));

    int vert = rand() % 21;
    int hors = rand() % 80;

    mapPrint(map);

    return 0;
}
