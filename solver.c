#include "solver.h"

int random_approach()
{
    int founded = 0;
    int iterations = 0; //test speed and number of iterations
    while(founded != ARRAY_LENGTH)
    {
        int r1 = Rnd(0, ARRAY_LENGTH);
        int r2 = Rnd(0, ARRAY_LENGTH);
        if(r1!=r2 && cards[r1]==cards[r2] && cards[r1].value== 0  && cards[r2].value== 0) //refacto array and do lazy eval if possible
        {
            cards[r1].value = 1;
            cards[r2].value = 1;
            founded = founded + 1;
        }
        // FLIP visualy r1
        // FLIP visualy r2
        iterations += 1;
    }
    return iterations;
}

int logic_approach()
{
    int map_length = ARRAY_LENGTH / 2;
    int map[map_length] = {-1};//create hashmap to store cards already seen (length == ARRAY_SIZE/2)
    int founded = 0;
    int i = 0;
    while(founded != ARRAY_LENGTH || i < ARRAY_LENGTH)
    {
        if(cards[i].value == 0) //hidden side card
        {
            //FLIP visualy cards[i]
            if(map[cards[i]] == -1) //not already founded
            {
                map[cards[i]] = i;
                cards[i].value = 1;

                //process cards[i+1] because we fliped a unknown card
                map[cards[i+1]] = i+1;
                cards[i+1].value = 1;
                //FLIP visualy cards[i+1]
                i++; 
            }
            else //already founded
            {
                if(cards[map[cards[i]]] == cards[i])
                {
                    cards[i].value = 1;
                    //FLIP visualy cards[map[cards[i]]]
                }
                else
                {
                    printf("error hashmap: mapped card != card[i]!\n");
                }
            }
        }
        i++;
    }
    return i;
}

int other_strat()
{
    return 1;
}



int main(void)
{
    //to do
}
