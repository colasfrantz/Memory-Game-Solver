#include <stdio.h>
#include <assert.h>
#include "board.h"

static void test_each_value_twice(void)
{
    Board bd; board_init(&bd, 8, 42);
    int count[9] = {0};
    for (int p = 0; p < bd.n_cards; p++) {
        int v = board_flip(&bd, p);
        assert(v >= 1 && v <= 8);
        count[v]++;
    }
    for (int v = 1; v <= 8; v++)
        assert(count[v] == 2);
}

static void test_same_seed_same_board(void)
{
    Board a, b; board_init(&a, 8, 7); board_init(&b, 8, 7);
    for (int p = 0; p < a.n_cards; p++)
        assert(board_flip(&a, p) == board_flip(&b, p));
}

static void test_different_seed_differs(void)
{
    Board a, b; board_init(&a, 8, 1); board_init(&b, 8, 2);
    int diff = 0;
    for (int p = 0; p < a.n_cards; p++)
        if (board_flip(&a, p) != board_flip(&b, p)) diff++;
    assert(diff > 0);
}

static void test_shuffle_is_uniform(void)
{
    /* la position 0 doit recevoir chaque valeur à peu près aussi souvent */
    int count[5] = {0};
    for (unsigned seed = 0; seed < 20000; seed++) {
        Board bd; board_init(&bd, 4, seed);
        count[board_flip(&bd, 0)]++;
    }
    for (int v = 1; v <= 4; v++)
        assert(count[v] > 4000 && count[v] < 6000);   /* attendu : 5000 */
}

static void test_remove_and_over(void)
{
    Board bd; board_init(&bd, 2, 3);
    assert(!board_is_over(&bd));
    for (int v = 1; v <= 2; v++) {
        int a = -1, b = -1;
        for (int p = 0; p < bd.n_cards; p++)
            if (board_flip(&bd, p) == v && !bd.removed[p]) { if (a < 0) a = p; else b = p; }
        board_remove_pair(&bd, a, b);
    }
    assert(board_is_over(&bd) && bd.pairs_found == 2);
}

int main(void)
{
    test_each_value_twice(); test_same_seed_same_board();
    test_different_seed_differs(); test_shuffle_is_uniform();
    test_remove_and_over();
    printf("Tests board OK.\n");
    return 0;
}