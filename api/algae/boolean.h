/*
    Copyright © 2013 Anthony de Almeida Lopes
 */
#ifndef ALGAE_BOOLEAN_H
#define ALGAE_BOOLEAN_H

typedef struct algae_boolean
        algae_boolean_t;

typedef void const *
        (* algae_boolean_false_callback_t)(void);

typedef void const *
        (* algae_boolean_true_callback_t)(void);

algae_boolean_t const *
algae_boolean_false_introduction(void);

algae_boolean_t const *
algae_boolean_true_introduction(void);

void const *
algae_boolean_elimination(
    algae_boolean_t const * const /* b */,
    algae_boolean_false_callback_t const /* false_cb */,
    algae_boolean_true_callback_t const /* true_cb */);

algae_boolean_t const *
algae_boolean_not(
    algae_boolean_t const * const /* b */);


#endif /* ALGAE_BOOLEAN_H */
