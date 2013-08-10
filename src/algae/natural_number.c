#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <algae/natural_number.h>

/*
    ℕ : 1 → ★

    zero : 1 → ℕ
    successor : ℕ → ℕ

    [zero, successor] : 1 + ℕ → ℕ

 */
#define ALGAE_NATURAL_NUMBER_MAGIC 0xa42f875c
struct algae_natural_number {
    uint32_t magic;

    enum {
        ALGAE_NATURAL_NUMBER_ZERO_CONSTRUCTOR,
        ALGAE_NATURAL_NUMBER_SUCCESSOR_CONSTRUCTOR
    } constructor;
    union {
        struct { } zero;
        struct { algae_natural_number_t const * n; } successor;
    } data;
};
#define ALGAE_NATURAL_NUMBER_VALIDATE(this) do {            \
    assert((this) != NULL);                                 \
    assert((this)->magic == ALGAE_NATURAL_NUMBER_MAGIC);    \
} while (0x00)

algae_natural_number_t const *
algae_natural_number_zero_introduction(void)
{

    algae_natural_number_t *n = NULL;


    n = calloc(1, sizeof(algae_natural_number_t));
    assert(n != NULL);

    memset(n, 0x00, sizeof(algae_natural_number_t));
    n->magic = ALGAE_NATURAL_NUMBER_MAGIC;

    n->constructor = ALGAE_NATURAL_NUMBER_ZERO_CONSTRUCTOR;


    ALGAE_NATURAL_NUMBER_VALIDATE(n);

    return n;
}

algae_natural_number_t const *
algae_natural_number_successor_introduction(
    algae_natural_number_t const * const m)
{

    algae_natural_number_t *n = NULL;

    ALGAE_NATURAL_NUMBER_VALIDATE(m);


    n = calloc(1, sizeof(algae_natural_number_t));
    assert(n != NULL);

    memset(n , 0x00, sizeof(algae_natural_number_t));
    n->magic = ALGAE_NATURAL_NUMBER_MAGIC;

    n->constructor = ALGAE_NATURAL_NUMBER_SUCCESSOR_CONSTRUCTOR;
    n->data.successor.n = m;


    ALGAE_NATURAL_NUMBER_VALIDATE(n);

    return n;
}

void const *
algae_natural_number_elimination(
    algae_natural_number_t const * const n,
    algae_natural_number_zero_callback_t const zero_cb,
    algae_natural_number_successor_callback_t const successor_cb)
{

    ALGAE_NATURAL_NUMBER_VALIDATE(n);


    assert(zero_cb != NULL);
    assert(successor_cb != NULL);

    switch (n->constructor) {
        case ALGAE_NATURAL_NUMBER_ZERO_CONSTRUCTOR:

            return zero_cb();

        case ALGAE_NATURAL_NUMBER_SUCCESSOR_CONSTRUCTOR:

            return successor_cb(n->data.successor.n);

        default:
            abort(); /* not reached */
    }
    
    abort(); /* not reached */
}
