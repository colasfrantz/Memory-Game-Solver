#include "board.h"

void board_init(Board *bd, int n_pairs, unsigned seed)
{
    assert(n_pairs >= 1 && 2 * n_pairs <= BOARD_MAX_CARDS);
    
    memset(bd, 0, sizeof *bd);
    bd->n_pairs = n_pairs;
    bd->n_cards = 2 * n_pairs;

    srand(seed); 
    for (int i = 0; i < bd->n_cards; i++)
        bd->value[i] = i / 2 + 1;

    /* Mélange de Fisher-Yates */
    for (int i = bd->n_cards - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);     /* j dans [0, i] inclus */
        int tmp = bd->value[i];
        bd->value[i] = bd->value[j];
        bd->value[j] = tmp;
    }
    return;
}

int  board_flip(const Board *bd, int pos)
{
    /*Vérifie par assert que pos est valide et que la carte n’est pas déjà retirée, puis renvoie value[pos]. Elle est const : retourner une carte ne change pas le plateau. Le nombre de tours se compte dans le moteur, pas ici.*/
    assert(pos >= 0 && pos < bd->n_cards);
    assert(!bd->removed[pos]);
    return bd->value[pos];
}            

void board_remove_pair(Board *bd, int pos_a, int pos_b)
{
    /*assert que les deux positions sont différentes, non retirées, et que value[pos_a] == value[pos_b]. Puis marque les deux removed et incrémente pairs_found. Cette fonction est le garde-fou du moteur : si le moteur valide une fausse paire, le programme s’arrête tout de suite au lieu de produire des statistiques fausses.*/
    assert(pos_a >= 0 && pos_a < bd->n_cards);
    assert(pos_b >= 0 && pos_b < bd->n_cards);
    assert(pos_a != pos_b);
    assert(!bd->removed[pos_a] && !bd->removed[pos_b]);
    assert(bd->value[pos_a] == bd->value[pos_b]);

    bd->removed[pos_a] = true;
    bd->removed[pos_b] = true;
    bd->pairs_found++;
} 

bool board_is_over(const Board *bd)
{
    return bd->pairs_found == bd->n_pairs;
}
