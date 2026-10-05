#include "solver.h"

int main(void)
{
    int map = 0; // hashmap
    for(size_t i = 0; i < ARRAY_LENGTH; i++)
    {
        for(size_t j = 0; j < ARRAY_LENGTH; j++)
        {
            if(map_id(array[i][j], map) == -1)
            {
                int x = 0; //get them from mapping
                int y = 0;
                flip(i, j, x, y); //flip them visually
            }
        }
    }
    return 1;
}
