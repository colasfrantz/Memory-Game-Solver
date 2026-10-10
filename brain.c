#include "brain.h"

void brain_init(Brain *b, int n_pairs)
{
    if (n_pairs < 1 || 2 * n_pairs > MAX_CARDS)
        n_pairs = MAX_PAIRS;
    memset(b, 0, sizeof *b); // all of b's will be set to 0s
    b->n_pairs = n_pairs;
    b->n_cards = 2 * n_pairs;
    b->pairs_removed = 0;
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

void brain_observe(Brain *b, int pos, int value)
{
    assert(b->state[pos] != POS_REMOVED);
    if(b->state[pos] == POS_UNKNOWN)
    {
        b->state[pos] = POS_SEEN;
        b->value_at[pos] = value;
        //La retirer des positions inconnues
        int idx  = b->index_in_unknown[pos];            
        int last = b->unknown[b->unknown_count - 1];    

        b->unknown[idx] = last;                         
        b->index_in_unknown[last] = idx;                
        b->unknown_count--;
        //oui oui baguette
        if(b->seen_count[value] == 0)
        {
            b->seen_pos[value][0] = pos;
        }
        else
        {
            b->seen_pos[value][1] = pos;
        }
        b->seen_count[value] += 1;
        
        if(b->seen_count[value] == 1)
        {
            b->nb_unseen_values -= 1;
            b->nb_singles += 1;
        }
        else if(b->seen_count[value] == 2)
        {
            b->nb_singles -= 1;
            b->known_pairs[b->known_pairs_count] = value;
            b->known_pairs_count += 1;
        }
    }
}
void brain_remove_pair(Brain *b, int value)
{
    assert(b->seen_count[value] == 2);
    int pos_a = b->seen_pos[value][0];
    int pos_b = b->seen_pos[value][1];
    assert(b->state[pos_a] != POS_REMOVED)
    b->state[pos_a] = POS_REMOVED;
    b->state[pos_b] = POS_REMOVED;
    for (int i = 0; i < b->known_pairs_count; i++)
    {
        if (b->known_pairs[i] == value)
        {
            b->known_pairs[i] = b->known_pairs[b->known_pairs_count - 1];
            b->known_pairs_count--;
            break;
        }
    }
    b->pairs_removed += 1;
}


bool brain_has_known_pair(const Brain *b)
{
    return b->known_pairs_count > 0;
}

bool brain_pop_known_pair(Brain *b, int *pos_a, int *pos_b)
{
    if (b->known_pairs_count == 0)
        return false;

    b->known_pairs_count--;
    int value = b->known_pairs[b->known_pairs_count];

    *pos_a = b->seen_pos[value][0];
    *pos_b = b->seen_pos[value][1];
    return true;
}

int  brain_find_twin(const Brain *b, int pos, int value)
{
    for (int i = 0; i < 2; i++)
    {
        int p = b->seen_pos[value][i];
        if (p != NO_POS && p != pos)
            return p;
    }
    return NO_POS;
}
int  brain_random_unknown(const Brain *b, int exclude)
{
    int n = b->unknown_count;
    bool excluded_is_unknown = (exclude >= 0 && exclude < b->n_cards && b->state[exclude] == POS_UNKNOWN);
    int candidates = excluded_is_unknown ? n - 1 : n;
    if (candidates <= 0)
        return NO_POS;
    int r = rand() % candidates;
    if (excluded_is_unknown && r >= b->index_in_unknown[exclude])
        r++;
    return b->unknown[r];
}
bool brain_game_over(const Brain *b)
{
    return b->pairs_removed == b->n_pairs;
}