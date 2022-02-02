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
                printf("%%"); // check piazza
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

int exits(int map[R][C], int *topExit, int *bottomExit, int *leftExit, int *rightExit)
{
    *topExit = 1 + rand() % (C - 2);
    map[0][*topExit] = PATH;
    *bottomExit = 1 + rand() % (C - 2);
    map[R - 1][*bottomExit] = PATH;

    *leftExit = 1 + rand() % (R - 2);
    map[*leftExit][0] = PATH;
    *rightExit = 1 + rand() % (R - 2);
    map[*rightExit][C - 1] = PATH;

    return 0;
}
int intersect(int map[R][C], int r, int c)
{
    if (map[r][c] != NOT_SET)
        return 1;
    return 0;
}

int placeBubble(int map[R][C], int t, int tr, int tc)
{
    int r, c;

    do
    {
        r = rand() % 21;
        c = rand() % 80;
    } while (intersect(map, r, c));

    for (int i = r - tr; i < r + tr; i++)
    {
        for (int j = c - tc; j < c + tc; j++)
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

int rocks(int map[R][C], int t)
{
    int r, c;
    for (int i = 0; i < 25; i++)
    {
        r = rand() % 21;
        c = rand() % 80;
        map[r][c] = t;
    }
    return 0;
}

int tGen(int map[R][C])
{
    placeBubble(map, CLEARING, tR, tC);
    placeBubble(map, CLEARING, tR, tC);
    placeBubble(map, TALL_GRASS, tR, tC);
    placeBubble(map, TALL_GRASS, tR, tC);

    placeBubble(map, TREES, tR / 2, tC / 2);
    placeBubble(map, TREES, tR / 2, tC / 2);
    fill(map);
    rocks(map, ROCKS);
    rocks(map, TREES);

    return 0;
}
int min(int *a, int *b)
{
    if (*a < *b)
        return 1;
    return 0;
}
int paths(int map[R][C], int *t, int *b, int *l, int *ro)
{
    int r;
    r = 1 + rand() % (R - 2);

    for (int i = 0; i < r; i++)
    {
        map[i][*t] = PATH;
    }
    if (*t < *b)
    {
        for (int i = *t; i < *b; i++)
            map[r][i] = PATH;
    }

    if (*t > *b)
    {
        for (int i = *t; i > *b; i--)
            map[r][i] = PATH;
    }

    for (int i = R - 1; i >= r; i--)
    {
        map[i][*b] = PATH;
    }

    int c;
    c = 1 + rand() % (C - 2);

    for (int i = 0; i < c; i++)
    {
        map[*l][i] = PATH;
    }

    if (*l < *ro)
    {
        for (int i = *l; i < *ro; i++)
            map[i][c] = PATH;
    }

    if (*l > *ro)
    {
        for (int i = *l; i > *ro; i--)
            map[i][c] = PATH;
    }

    for (int i = C - 1; i >= c; i--)
    {
        map[*ro][i] = PATH;
    }

    return 0;
}
int main(int argc, char const *argv[])
{

    int c, d;
    int t = 0, b = 0, l = 0, r = 0;

    int map[R][C];
    srand(time(NULL));

    initializeMap(map);

    tGen(map);

    setBorders(map);

    exits(map, &t, &b, &l, &r); // need to change so that the corner is not an option

    paths(map, &t, &b, &l, &r);

    mapPrint(map);

    return 0;
}
