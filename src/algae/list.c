#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <algae/list.h>

/*
    List : α → ★

    nil : 1 → List α
    link : α × (List α) → List α

    [nil, link] : 1 + α × (List α) → List α
 */
#define ALGAE_LIST_MAGIC 0x10ae9fc7
struct algae_list {
    uint32_t magic;

    enum {
        ALGAE_LIST_NIL_CONSTRUCTOR,
        ALGAE_LIST_LINK_CONSTRUCTOR
    } constructor;
    union {
        struct { } nil;
        struct { void const * w;
                 algae_list_t const * ws;
               } link;
    } data;
};
#define ALGAE_LIST_VALIDATE(this) do {                          \
    assert((this) != NULL);                                     \
    assert((this)->magic == ALGAE_LIST_MAGIC);                  \
    assert((this)->constructor == ALGAE_LIST_NIL_CONSTRUCTOR    \
        || (this)->constructor == ALGAE_LIST_LINK_CONSTRUCTOR); \
} while (0x00);

algae_list_t const *
algae_list_nil_introduction(void) 
{

    algae_list_t * xs = NULL;


    xs = malloc(sizeof(algae_list_t));
    assert(xs != NULL);

    memset(xs, 0x00, sizeof(algae_list_t));
    xs->magic = ALGAE_LIST_MAGIC;

    xs->constructor = ALGAE_LIST_NIL_CONSTRUCTOR;


    ALGAE_LIST_VALIDATE(xs);

    return xs;
}

algae_list_t const *
algae_list_link_introduction(
    void const * const w,
    algae_list_t const * const ws)
{

    algae_list_t * xs = NULL;


    assert(w != NULL);
    assert(ws != NULL);


    xs = malloc(sizeof(algae_list_t));
    assert(xs != NULL);

    memset(xs, 0x00, sizeof(algae_list_t));
    xs->magic = ALGAE_LIST_MAGIC;

    xs->constructor = ALGAE_LIST_LINK_CONSTRUCTOR;
    xs->data.link.w = w;
    xs->data.link.ws = ws;

    ALGAE_LIST_VALIDATE(xs);

    return xs;
}

void const *
algae_list_elimination(
    algae_list_t const * const xs,
    algae_list_nil_callback_t const nil_cb,
    algae_list_link_callback_t const link_cb)
{

    ALGAE_LIST_VALIDATE(xs);


    assert(nil_cb != NULL);
    assert(link_cb != NULL);

    switch (xs->constructor) {
        /*
             e₀ : cRT (nil A).
             e₁ : (Π x : A .
                    (Π xs : List A .
                      (Π ⌊xs⌋ : cRT xs .
                        cRT (link A x xs)
                      )
                    )
                  ).

             A (nil A)       cRT e₀ e₁ ↦ e₀,
             A (link A x xs) cRT e₀ e₁ ↦ e₁ x xs (List-elimination A xs cRT e₀ e₁)
         */
        case ALGAE_LIST_NIL_CONSTRUCTOR:

            return nil_cb();

        case ALGAE_LIST_LINK_CONSTRUCTOR:

            return link_cb(algae_list_elimination(
                               xs->data.link.ws,
                               nil_cb,
                               link_cb),
                           xs->data.link.w);

        default:
            abort(); /* not reached */
    }

    abort(); /* not reached */
}

