/*
    Copyright © 2013 Anthony de Almeida Lopes
 */
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <algae/boolean.h>

/*
    read this later: http://stackoverflow.com/questions/3870088/a-monad-is-just-a-monoid-in-the-category-of-endofunctors-whats-the-problem
*/

/*
    𝔹 : 1 → ★

    true  : 1 → 𝔹
    false : 1 → 𝔹

    [true, false] : 1 + 1 → 𝔹
 */
#define ALGAE_BOOLEAN_MAGIC 0x66068227
struct algae_boolean {
    uint32_t magic;

    enum {
        ALGAE_BOOLEAN_CONSTRUCTOR_FALSE,
        ALGAE_BOOLEAN_CONSTRUCTOR_TRUE
    } constructor;
    union {
        struct { } false;
        struct { } true;
    } data;
};
#define ALGAE_BOOLEAN_VALIDATE(this) do {                         \
    assert((this) != NULL);                                       \
    assert((this)->magic == ALGAE_BOOLEAN_MAGIC);                 \
    assert((this)->constructor == ALGAE_BOOLEAN_CONSTRUCTOR_FALSE \
        || (this)->constructor == ALGAE_BOOLEAN_CONSTRUCTOR_TRUE  \
          );                                                      \
} while (0)

algae_boolean_t const * 
algae_boolean_false_introduction(void)
{

    algae_boolean_t * b = NULL;


    b = calloc(1, sizeof(algae_boolean_t));
    assert(b != NULL);

    memset(b, 0x00, sizeof(algae_boolean_t));
    b->magic = ALGAE_BOOLEAN_MAGIC;

    b->constructor = ALGAE_BOOLEAN_CONSTRUCTOR_FALSE;


    ALGAE_BOOLEAN_VALIDATE(b);

    return b;   
}

algae_boolean_t const *
algae_boolean_true_introduction(void)
{

    algae_boolean_t *b = NULL;


    b = calloc(1, sizeof(algae_boolean_t));
    assert(b != NULL);

    memset(b, 0x00, sizeof(algae_boolean_t));
    b->magic = ALGAE_BOOLEAN_MAGIC;

    b->constructor = ALGAE_BOOLEAN_CONSTRUCTOR_TRUE;


    ALGAE_BOOLEAN_VALIDATE(b);

    return b;
}

void const *
algae_boolean_elimination(
    algae_boolean_t const * const b,
    algae_boolean_false_callback_t const false_cb,
    algae_boolean_true_callback_t const true_cb)
{

    ALGAE_BOOLEAN_VALIDATE(b);

    assert(false_cb != NULL);
    assert(true_cb != NULL);


    switch (b->constructor) {
        case ALGAE_BOOLEAN_CONSTRUCTOR_FALSE:

            return false_cb();

        case ALGAE_BOOLEAN_CONSTRUCTOR_TRUE:

            return true_cb();

        default:
            abort(); /* not reached */
    }

    abort(); /* not reached */
}

/*

    Library functions

*/

static void const * /*# algae_boolean_t */
algae_boolean_not_false(void);

static void const * /*# algae_boolean_t */
algae_boolean_not_true(void);

algae_boolean_t const *
algae_boolean_not(
    algae_boolean_t const * const b) {


    ALGAE_BOOLEAN_VALIDATE(b);

    return algae_boolean_elimination(b,
               algae_boolean_not_false,
               algae_boolean_not_true);
}

static void const * /*# algae_boolean_t */
algae_boolean_not_false(void) {

    return algae_boolean_true_introduction();
}

static void const * /*# algae_boolean_t */
algae_boolean_not_true(void) {

    return algae_boolean_false_introduction();
}
