#include "board.h"

void board_init(Board *bd, int n_pairs, unsigned seed)
{
    /*
    Vérifie que 2 * n_pairs <= BOARD_MAX_CARDS.
    Appelle srand(seed) : une graine fixée rend la partie reproductible, y compris les choix aléatoires de brain_random_unknown, qui utilise le même rand().
    Remplis value[i] = i / 2 + 1 : tu obtiens 1, 1, 2, 2, 3, 3...
    Mélange avec Fisher-Yates : pour i allant de n_cards - 1 jusqu’à 1, tire j = rand() % (i + 1) et échange value[i] et value[j].
    Mets removed[] à false et pairs_found à 0.

    Attention à la boucle : j doit être tiré dans [0, i] inclus. Un tirage dans [0, i-1] donne un mélange biaisé, et ce bug ne se voit pas à l’œil nu.
    */
   return;
}

int  board_flip(const Board *bd, int pos)
{
    /*Vérifie par assert que pos est valide et que la carte n’est pas déjà retirée, puis renvoie value[pos]. Elle est const : retourner une carte ne change pas le plateau. Le nombre de tours se compte dans le moteur, pas ici.*/
    return -1;
}            

void board_remove_pair(Board *bd, int pos_a, int pos_b)
{
    /*assert que les deux positions sont différentes, non retirées, et que value[pos_a] == value[pos_b]. Puis marque les deux removed et incrémente pairs_found. Cette fonction est le garde-fou du moteur : si le moteur valide une fausse paire, le programme s’arrête tout de suite au lieu de produire des statistiques fausses.*/
} 

bool board_is_over(const Board *bd)
{
    return bd->pairs_found == bd->n_pairs;
}
