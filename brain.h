#ifndef BRAIN_H
#define BRAIN_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>   
#include <assert.h>   

#define MAX_CARDS 64
#define MAX_PAIRS (MAX_CARDS / 2)
#define NO_POS    (-1)

typedef enum {
    POS_UNKNOWN,
    POS_SEEN,      // seen but not won
    POS_REMOVED    // won
} PosState;

// The "brain" of the solver : only what have been see
typedef struct {
    int n_cards;
    int n_pairs;

    // by position
    PosState state[MAX_CARDS]; //array of states
    int value_at[MAX_CARDS];  //array of values (only valid if state != POS_UNKNOWN)

    // by values (indexes 1..n_pairs) : where did we see it 
    int seen_pos[MAX_PAIRS + 1][2];        // NO_POS if not
    int seen_count[MAX_PAIRS + 1];         // 0, 1 or 2

    // pairs wich pos are known, to play in priority
    int known_pairs[MAX_PAIRS];            //values
    int known_pairs_count;

    // unknown positions
    int unknown[MAX_CARDS];
    int unknown_count;
    int index_in_unknown[MAX_CARDS];       //position -> index in unknown[]

    // counters 
    int nb_singles;                        // seen values 1 time
    int nb_unseen_values;                  // unseen values
    int pairs_removed;
} Brain;

// Initialisation
void brain_init(Brain *b, int n_pairs);

// Update : called by engine, not by strat
void brain_observe(Brain *b, int pos, int value);   // a card is just flipped
void brain_remove_pair(Brain *b, int value);        // party is won

// Requests
bool brain_has_known_pair(const Brain *b);
bool brain_pop_known_pair(Brain *b, int *pos_a, int *pos_b);
int  brain_find_twin(const Brain *b, int pos, int value);  // pair seen, else NO_POS
int  brain_random_unknown(const Brain *b, int exclude);    // random unknown pos
bool brain_game_over(const Brain *b);

// Shared Interface of all strats
typedef struct {
    const char *name;
    int (*choose_first)(const Brain *b);
    int (*choose_second)(const Brain *b, int first_pos, int first_value);
} Strategy;

#endif /* BRAIN_H */


