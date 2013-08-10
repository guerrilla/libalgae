/*
    Copyright © 2013 Anthony de Almeida Lopes
 */
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <algae/either.h>

/*
    Either : α × β → ★
    left : α → Either (α, β)
    right : β → Either (α, β)

    [left, right] : α + β → Either (α, β)
 */
#define ALGAE_EITHER_MAGIC 0x5910a1be
struct algae_either {
    uint32_t magic;

    enum {
        ALGAE_EITHER_CONSTRUCTOR_LEFT,
        ALGAE_EITHER_CONSTRUCTOR_RIGHT
    } constructor;
    union {
        struct { void const * x; } left;
        struct { void const * y; } right;
    } data;
};
#define ALGAE_EITHER_VALIDATE(this) do {            \
    assert((this) != NULL);                         \
    assert((this)->magic == ALGAE_EITHER_MAGIC);    \
} while (0)

algae_either_t const *
algae_either_primary_introduction(
    void const * const x)
{

    algae_either_t * etr = NULL;


    assert(x != NULL);

    etr = calloc(1, sizeof(algae_either_t));
    assert(etr != NULL);

    memset(etr, 0x00, sizeof(algae_either_t));
    etr->magic = ALGAE_EITHER_MAGIC;

    etr->constructor = ALGAE_EITHER_CONSTRUCTOR_LEFT;
    etr->data.left.x = x;


    ALGAE_EITHER_VALIDATE(etr);

    return etr;
}

algae_either_t const *
algae_either_alternative_introduction(
    void const * const y)
{

    algae_either_t * etr = NULL;


    assert(y != NULL);

    etr = calloc(1, sizeof(algae_either_t));
    assert(etr != NULL);

    memset(etr, 0x00, sizeof(algae_either_t));
    etr->magic = ALGAE_EITHER_MAGIC;

    etr->constructor = ALGAE_EITHER_CONSTRUCTOR_RIGHT;
    etr->data.right.y = y;


    ALGAE_EITHER_VALIDATE(etr);

    return etr;
}

void const *
algae_either_elimination(
    algae_either_t const * const etr,
    algae_either_left_callback_t const left_cb,
    algae_either_right_callback_t const right_cb)
{

    ALGAE_EITHER_VALIDATE(etr);

    assert(left_cb != NULL);
    assert(right_cb != NULL);

    switch (etr->constructor) {
        case ALGAE_EITHER_CONSTRUCTOR_LEFT:

            return left_cb(etr->data.left.x);

        case ALGAE_EITHER_CONSTRUCTOR_RIGHT:

            return right_cb(etr->data.right.y);

        default:
            abort(); /* not reached */
    }

    abort(); /* not reached */
}
