/*
    Copyright © 2013 Anthony de Almeida Lopes
 */
#ifndef ALGAE_NUMBER_NATURAL_H
#define ALGAE_NUMBER_NATURAL_H

typedef struct algae_natural_number
        algae_natural_number_t;

typedef void const *
        (* algae_natural_number_zero_callback_t)(void);

typedef void const *
        (* algae_natural_number_successor_callback_t)(
            algae_natural_number_t const * const /* n */);

algae_natural_number_t const *
algae_natural_number_zero_introduction(void);

algae_natural_number_t const *
algae_natural_number_successor_introduction(
    algae_natural_number_t const * const /* n */);

void const *
algae_natural_number_elimination(
    algae_natural_number_t const * const /* n */,
    algae_natural_number_zero_callback_t const /* zero_cb */,
    algae_natural_number_successor_callback_t const /* successor_cb */);


#endif /* ALGAE_NUMBER_NATURAL_H */
