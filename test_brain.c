#include <stdio.h>
#include <assert.h>
#include "brain.h"

//rechecker si tous les tests sont suffisants
static void check_invariants(const Brain *b)
{
    int unknown = 0, singles = 0, unseen = 0;
    for (int p = 0; p < b->n_cards; p++)
        if (b->state[p] == POS_UNKNOWN) {
            unknown++;
            assert(b->unknown[b->index_in_unknown[p]] == p);
        }
    assert(unknown == b->unknown_count);
    for (int i = 0; i < b->unknown_count; i++)
        assert(b->state[b->unknown[i]] == POS_UNKNOWN);
    for (int v = 1; v <= b->n_pairs; v++) {
        if (b->seen_count[v] == 0) unseen++;
        if (b->seen_count[v] == 1) singles++;
    }
    assert(singles == b->nb_singles);
    assert(unseen == b->nb_unseen_values);
}

static void test_init(void)
{
    Brain b; brain_init(&b, 4);
    assert(b.n_cards == 8 && b.unknown_count == 8);
    assert(b.nb_unseen_values == 4 && b.nb_singles == 0);
    assert(!brain_has_known_pair(&b));
    assert(!brain_game_over(&b));          
    check_invariants(&b);
}

static void test_observe(void)
{
    Brain b; brain_init(&b, 2);
    brain_observe(&b, 0, 1); check_invariants(&b);
    assert(b.unknown_count == 3 && b.nb_singles == 1 && b.nb_unseen_values == 1);
    brain_observe(&b, 1, 2); check_invariants(&b);
    brain_observe(&b, 2, 1); check_invariants(&b);
    assert(b.known_pairs_count == 1 && b.nb_singles == 1);
    brain_observe(&b, 3, 2); check_invariants(&b);
    assert(b.known_pairs_count == 2 && b.unknown_count == 0);
    brain_observe(&b, 3, 2);               
    assert(b.known_pairs_count == 2);
}

static void test_find_twin(void)
{
    Brain b; brain_init(&b, 3);
    brain_observe(&b, 0, 3);
    assert(brain_find_twin(&b, 0, 3) == NO_POS);
    brain_observe(&b, 5, 3);
    assert(brain_find_twin(&b, 5, 3) == 0);
    assert(brain_find_twin(&b, 0, 3) == 5);
}

static void test_ghost_pair(void)
{
    Brain b; brain_init(&b, 2);
    brain_observe(&b, 0, 1); brain_observe(&b, 2, 1);
    brain_remove_pair(&b, 1);
    assert(b.known_pairs_count == 0);

    Brain c; brain_init(&c, 2);
    brain_observe(&c, 0, 1); brain_observe(&c, 1, 2); brain_observe(&c, 2, 1);
    int a, d;
    assert(brain_pop_known_pair(&c, &a, &d) && a == 0 && d == 2);
    brain_remove_pair(&c, 1);
    assert(c.known_pairs_count == 0);
    assert(!brain_pop_known_pair(&c, &a, &d));
}

static void test_random_unknown(void)
{
    Brain b; brain_init(&b, 3);
    brain_observe(&b, 0, 1); brain_observe(&b, 5, 2);
    for (int i = 0; i < 10000; i++) {
        int p = brain_random_unknown(&b, 3);   
        assert(p != NO_POS && p != 3 && b.state[p] == POS_UNKNOWN);
        p = brain_random_unknown(&b, 0);      
        assert(p != NO_POS && b.state[p] == POS_UNKNOWN);
    }
}

static void test_game_over(void)
{
    Brain b; brain_init(&b, 1);
    brain_observe(&b, 0, 1); brain_observe(&b, 1, 1);
    assert(!brain_game_over(&b));
    brain_remove_pair(&b, 1);
    assert(brain_game_over(&b));
}

int main(void)
{
    test_init(); test_observe(); test_find_twin();
    test_ghost_pair(); test_random_unknown(); test_game_over();
    printf("Tous les tests passent.\n");
    return 0;
}