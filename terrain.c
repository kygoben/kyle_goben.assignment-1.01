#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define R 21 // size of field
#define C 80
#define tR 8 // how much to grow out from "seed" terrain
#define tC 16

int max(int num1, int num2)
{
    return (num1 > num2) ? num1 : num2;
}

/**
 * Find minimum between two numbers.
 */
int min(int num1, int num2)
{
    return (num1 > num2) ? num2 : num1;
}

enum terrain_type
{
    NOT_SET = -1,
    TALL_GRASS = 1,
    CLEARING = 2,
    ROCKS = 3,
    TREES = 4,
    PATH = 5,
    CENTER = 6,
    MART = 7,
    BOULDERS = 8,
};
/**
Checks to see if the coord is in the map
*/
int inBounds(int r, int c)
{
    if (r < R && r > 0 && c < C && c > 0){
        return 1;
    }
    return 0;
}
/*
Prints the map
*/
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
                printf("%%");
                break;
            case TREES:
                printf("^");
                break;
            }
        }
        printf("\n");
    }
}
/*
Sets the entire map to NOT_SET values
*/
int mapNotSet(int map[R][C])
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
/*
Sets the borders to bouldersf
*/
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
/*
Randomizes exits on each side of the map
Does not allow exits on corners
*/
int paths_exits(int map[R][C])
{
    int tE = 1 + rand() % (C - 2);
    map[0][tE] = PATH;
    int bE = 1 + rand() % (C - 2);
    map[R - 1][bE] = PATH;

    int lE = 1 + rand() % (R - 2);
    map[lE][0] = PATH;
    int rE = 1 + rand() % (R - 2);
    map[rE][C - 1] = PATH;

    int r;
    r = 2 + rand() % (R - 4);

    for (int i = 0; i < r; i++)
    {
        map[i][tE] = PATH;
    }

    for (int i = min(tE, bE); i <= max(tE, bE); i++)
    {
        map[r][i] = PATH;
    }

    for (int i = R - 1; i >= r; i--)
    {
        map[i][bE] = PATH;
    }
    int c;
    c = 2 + rand() % (C - 4);

    for (int i = 0; i < c; i++)
    {
        map[lE][i] = PATH;
    }

    for (int i = min(lE, rE); i <= max(lE, rE); i++)
    {
        map[i][c] = PATH;
    }

    for (int i = C - 1; i >= c; i--)
    {
        map[rE][i] = PATH;
    }

    return 0;
}



/*
Randomly picks a unset location and makes a bubble of the given terrian
*/
int placeBubble(int map[R][C], int t, int tr, int tc)
{
    int r, c;
    do
    {
        r = rand() % 21;
        c = rand() % 80;
    } while (map[r][c] != NOT_SET);

    for (int i = r - tr; i < r + tr; i++)
    {
        for (int j = c - tc; j < c + tc; j++)
        {
            if (inBounds(i, j))
                map[i][j] = t;
        }
    }
    return 0;
}
/*
fills the remaining space of the map with clearing
*/
// int fill(int map[R][C])
// {
//     for (int i = 0; i < R; i++)
//     {
//         for (int j = 0; j < C; j++)
//         {
//             if (!unset(map, i, j))
//                 map[i][j] = CLEARING;
//         }
//     }
//     return 0;
// }
/*
places any terrian type randomly around the map
*/
// int scatter(int map[R][C], int t)
// {
//     int r, c;
//     for (int i = 0; i < 25; i++)
//     {
//         r = rand() % 21;
//         c = rand() % 80;
//         map[r][c] = t;
//     }
//     return 0;
// }
/*
generates all of the terrain for the map
*/
int tGen(int map[R][C])
{
    placeBubble(map, CLEARING, tR, tC);
    placeBubble(map, CLEARING, tR, tC);
    placeBubble(map, TALL_GRASS, tR, tC);
    placeBubble(map, TALL_GRASS, tR, tC);

    placeBubble(map, TREES, tR / 2, tC / 2);
    placeBubble(map, TREES, tR / 2, tC / 2);

    // scatter(map, ROCKS);
    // scatter(map, TREES);

    return 0;
}

/*
Checks to see if the space is ocupied with an important structure
*/
int importantStructure(int map[R][C], int r, int c)
{
    if (inBounds(r, c))
        if (map[r][c] == PATH || map[r][c] == MART || map[r][c] == CENTER)
        {

            return 1;
        }
    return 0;
}

/*
Finds the closest south path, if none exists it takes the closest north path
*/
int closestPath(int map[R][C], int r, int c, int *row)
{
    for (int i = r; i < R; i++)
    {
        if (map[i][c] == PATH)
        {
            *row = i;
            break;
        }
    }
    for (int i = r; i > 0; i--)
    {
        if (map[i][c] == PATH)
        {
            *row = i;
            break;
        }
    }

    return 0;
}

/*
places stations in groups of 4 around the map in unocupied space
places a N or S path from the station to the path
*/
int stations(int map[R][C], int type)
{
    int c, r;
    do
    {
        r = 1 + rand() % (R - 3);
        c = 1 + rand() % (C - 3);
    } while (importantStructure(map, r, c) || importantStructure(map, r, c + 1) || importantStructure(map, r + 1, c) || importantStructure(map, r + 1, c + 1));

    map[r][c] = type;
    map[r][c + 1] = type;
    map[r + 1][c] = type;
    map[r + 1][c + 1] = type;

    int row;
    closestPath(map, r, c, &row);
    if (row < r)
    {
        for (int i = r; i > row; i--)
        {
            if (!importantStructure(map, i, c))
                map[i][c] = PATH;
        }
    }
    if (row > r)
    {
        for (int i = r; i < row; i++)
        {
            if (!importantStructure(map, i, c))
                map[i][c] = PATH;
        }
    }

    return 0;
}
/*
builds the map
*/
int main(int argc, char const *argv[])
{


    int map[R][C];
    srand(time(NULL));

    mapNotSet(map);

    tGen(map);

    setBorders(map);

    paths_exits(map);

    stations(map, MART);

    stations(map, CENTER);

    // fill(map);

    mapPrint(map);

    return 0;
}
