#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define R 21
#define C 80
#define tR 8
#define tC 16

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
                printf("%%"); //check piazza
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
int intersect(int map[R][C], int r, int c)
{
    if (map[r][c] != NOT_SET)
        return 1;
    return 0;
}

int placeBubble(int map[R][C], int t)
{
    int r, c;

    do
    {
        r = rand() % 21;
        c = rand() % 80;
    } while (intersect(map, r, c));

    for (int i = r - tR; i < r + tR; i++)
    {
        for (int j = c - tC; j < c + tC; j++)
        {
            if (check(i, j))
                map[i][j] = t;
        }
    }
    return 0;
}
int fill(int map[R][C])
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (!intersect(map, i, j))
                map[i][j] = CLEARING;
        }
    }
    return 0;
}

int rocks(int map[R][C]){
    int r,c;
    for(int i = 0; i<25;i++){
        r = rand() % 21;
        c = rand() % 80;
        map[r][c] = ROCKS;
    }
    return 0;
}

int tGen(int map[R][C])
{
    placeBubble(map, TALL_GRASS);
    placeBubble(map, TALL_GRASS);
    placeBubble(map, CLEARING);
    placeBubble(map, CLEARING);
    placeBubble(map, TREES);
    placeBubble(map, TREES);
    fill(map);

    rocks(map);

    // placeBubble(map, TALL_GRASS);
    // placeBubble(map, TALL_GRASS);
    // placeBubble(map, CLEARING);
    // placeBubble(map, CLEARING);
    // placeBubble(map, TREES);

    // placeBubble(map, TALL_GRASS);
    // placeBubble(map, TALL_GRASS);
    // placeBubble(map, CLEARING);
    // placeBubble(map, CLEARING);
    // placeBubble(map, TREES);

    return 0;
}

int main(int argc, char const *argv[])
{
    int map[R][C];
    srand(time(NULL));

    initializeMap(map);

    tGen(map);

    setBorders(map);

    exits(map); //need to change so that the corner is not an option

    mapPrint(map);

    return 0;
}
