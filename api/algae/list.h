#ifndef ALGAE_LIST_H
#define ALGAE_LIST_H

typedef struct algae_list
        algae_list_t;

#include <algae/boolean.h>

typedef void const *
        (* algae_list_nil_callback_t)(void);

typedef void const *
        (* algae_list_link_callback_t)(
            void const * const /* x */,
            algae_list_t const * const /* ys */);


algae_list_t const *
algae_list_nil_introduction(void);

algae_list_t const *
algae_list_link_introduction(
    void const * const /* x */,
    algae_list_t const * const /* xs*/);

void const *
algae_list_elimination(
    algae_list_t const * const /* x */,
    algae_list_nil_callback_t const /* nil_cb */,
    algae_list_link_callback_t const /* link_cb */);

/*
    @section Library
 */
algae_list_t const *
algae_list_take_while(
    algae_list_t const * const /* xs */,
    algae_boolean_t const * (* const /* p */)(void const * const /* x */)
    );

algae_list_t const *
algae_list_drop_while(
    algae_list_t const * const /* xs */,
    algae_boolean_t const * (* const /* p */)(void const * const /* x */));


#if 0
/* catamorphism */ def fold[A1 >: A](z: A1)(op: (A1, A1) => A1): A1
list_reduce(...)

/* anamorphism */
list_generate(...)

/* hylomorphism */
list_map(...);
#endif

#endif /* ALGAE_LIST_H */
