#include "brain.h"

void brain_init(Brain *b, int n_pairs)
{
    b = malloc(sizeof(struct Brain));
    if(!b)
    {
        return NULL;
    }
    if(n_pairs*2 > MAX_CARDS)
    {
        return NULL;
    }
    b->n_cards = n_pairs * 2;
    b->n_pairs = n_pairs;
    PosState s[MAX_CARDS] = {0};
    b->state = s;
    b->seen_count = ;
}
void brain_observe(Brain *b, int pos, int value);
void brain_remove_pair(Brain *b, int value);
bool brain_has_known_pair(const Brain *b);
bool brain_pop_known_pair(Brain *b, int *pos_a, int *pos_b);
int  brain_find_twin(const Brain *b, int pos, int value);
int  brain_random_unknown(const Brain *b, int exclude);
bool brain_game_over(const Brain *b);