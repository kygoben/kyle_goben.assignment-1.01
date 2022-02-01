#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define R 21
#define C 80

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

int check(int r, int c)
{
    if (r < R && r > 0 && c < C && c > 0)
    {

        return 1;
    }
    return 0;
}

void mapPrint(int map[R][C])
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
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
                printf("^");
                break;
            }
        }
        printf("\n");
    }
}
int initializeMap(int map[R][C])
{

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            map[i][j] = NOT_SET;
        }
    }
    return 0;
}

int setBorders(int map[R][C])
{

    for (int i = 0; i < R; i += R - 1)
    {
        for (int j = 0; j < C; j++)
        {
            map[i][j] = BOULDERS;
        }
    }

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j += 79)
        {
            map[i][j] = BOULDERS;
        }
    }
    return 0;
}

int exits(int map[R][C])
{

    int topExit = rand() % C;
    map[0][topExit] = PATH;
    int bottomExit = rand() % C;
    map[R - 1][bottomExit] = PATH;

    int leftExit = rand() % R;
    map[leftExit][0] = PATH;
    int rightExit = rand() % R;
    map[rightExit][C - 1] = PATH;

    return 0;
}

int tallGrass(int map[R][C])
{
    int r = rand() % 21;
    int c = rand() % 80;

    for (int i = r - 5; i < r + 5; i++)
    {
        for (int j = c - 9; j < c + 9; j++)
        {
            if (check(i, j))
                map[i][j] = TALL_GRASS;
        }
    }

    r = rand() % 21;
    c = rand() % 80;

    for (int i = r - 5; i < r + 5; i++)
    {
        for (int j = c - 9; j < c + 9; j++)
        {
            if (check(i, j))
                map[i][j] = TALL_GRASS;
        }
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    int map[R][C];
    srand(time(NULL));

    initializeMap(map);

    tallGrass(map);

    setBorders(map);

    exits(map); //need to change so that the corner is not an option

    mapPrint(map);

    return 0;
}
