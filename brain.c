#include "brain.h"

void brain_init(Brain *b, int n_pairs)
{
    if (n_pairs < 1 || 2 * n_pairs > MAX_CARDS)
        n_pairs = MAX_PAIRS;
    memset(b, 0, sizeof *b); // all of b's will be set to 0s
    b->n_pairs = n_pairs;
    b->n_cards = 2 * n_pairs;
    for (int i = 0; i < b->n_cards; i++) {
        b->state[i] = POS_UNKNOWN;       
        b->value_at[i] = -1;             
        b->unknown[i] = i;
        b->index_in_unknown[i] = i;
    }
    b->unknown_count = b->n_cards;
    for (int v = 1; v <= b->n_pairs; v++) {
        b->seen_count[v] = 0;
        b->seen_pos[v][0] = NO_POS;
        b->seen_pos[v][1] = NO_POS;
    }
    b->known_pairs_count = 0;
    b->nb_singles = 0;
    b->nb_unseen_values = b->n_pairs;
}
void brain_observe(Brain *b, int pos, int value);
void brain_remove_pair(Brain *b, int value);
bool brain_has_known_pair(const Brain *b);
bool brain_pop_known_pair(Brain *b, int *pos_a, int *pos_b);
int  brain_find_twin(const Brain *b, int pos, int value);
int  brain_random_unknown(const Brain *b, int exclude);
bool brain_game_over(const Brain *b);