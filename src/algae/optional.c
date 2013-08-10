/*
    Copyright © 2013 Anthony de Almeida Lopes
 */
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <algae/optional.h>

/*
    Optional : α → ★

    nothing : 1 → Optional α
    some : α → Optional α

    [nothing, some] : 1 + α → Optional α
 */
#define ALGAE_OPTIONAL_MAGIC 0xffe0650b
struct algae_optional {
    uint32_t magic;

    enum {
        ALGAE_OPTIONAL_CONSTRUCTOR_NOTHING,
        ALGAE_OPTIONAL_CONSTRUCTOR_SOME
    } constructor;
    union {
        struct { } nothing;
        struct { void const * x; } some;
    } data;
};
#define ALGAE_OPTIONAL_VALIDATE(this) do {          \
    assert((this) != NULL);                         \
    assert((this)->magic == ALGAE_OPTIONAL_MAGIC);  \
} while (0x00);

algae_optional_t const *
algae_optional_nothing_introduction(void)
{

    algae_optional_t * opt = NULL;


    opt = calloc(0x01, sizeof(algae_optional_t));
    assert(opt != NULL);

    memset(opt, 0x00, sizeof(algae_optional_t));
    opt->magic = ALGAE_OPTIONAL_MAGIC;

    opt->constructor = ALGAE_OPTIONAL_CONSTRUCTOR_NOTHING;


    ALGAE_OPTIONAL_VALIDATE(opt);

    return opt;
}

algae_optional_t const *
algae_optional_some_introduction(
    void const * const x)
{

    algae_optional_t * opt = NULL;


    assert(x != NULL);

    opt = calloc(1, sizeof(algae_optional_t));
    assert(opt != NULL);

    memset(opt, 0x00, sizeof(algae_optional_t));
    opt->magic = ALGAE_OPTIONAL_MAGIC;

    opt->constructor = ALGAE_OPTIONAL_CONSTRUCTOR_SOME;
    opt->data.some.x = x;


    ALGAE_OPTIONAL_VALIDATE(opt);

    return opt;
}

void const *
algae_optional_elimination(
    algae_optional_t const * const opt,
    algae_optional_nothing_callback_t const nothing_cb,
    algae_optional_some_callback_t const some_cb)
{

    ALGAE_OPTIONAL_VALIDATE(opt);

    assert(nothing_cb != NULL);
    assert(some_cb != NULL);


    switch (opt->constructor) {
        case ALGAE_OPTIONAL_CONSTRUCTOR_NOTHING:

            return nothing_cb();

        case ALGAE_OPTIONAL_CONSTRUCTOR_SOME:

            return some_cb(opt->data.some.x);

        default:
            abort(); /* not reached */
    }

    abort(); /* not reached */
}
