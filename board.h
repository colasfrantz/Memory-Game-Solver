#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define BOARD_MAX_CARDS 64   

typedef struct {
    int  n_pairs;
    int  n_cards;
    int  value[BOARD_MAX_CARDS];     
    bool removed[BOARD_MAX_CARDS];   
    int  pairs_found;
} Board;

void board_init(Board *bd, int n_pairs, unsigned seed);
int  board_flip(const Board *bd, int pos);                  
void board_remove_pair(Board *bd, int pos_a, int pos_b);    
bool board_is_over(const Board *bd);

#endif /* BOARD_H */