/*
    Copyright © 2013 Anthony de Almeida Lopes
 */
#ifndef ALGAE_OPTIONAL_H
#define ALGAE_OPTIONAL_H

typedef struct algae_optional
        algae_optional_t;

typedef void const *
        (* algae_optional_nothing_callback_t)(void);

typedef void const *
        (* algae_optional_some_callback_t)(
            void const * const /* x */);


algae_optional_t const *
algae_optional_nothing_introduction(void);

algae_optional_t const *
algae_optional_some_introduction(
    void const * const /* x */);

void const *
algae_optional_elimination(
    algae_optional_t const * const /* opt */,
    algae_optional_nothing_callback_t const /* nothing_cb */,
    algae_optional_some_callback_t const /* some_cb */);

#endif /* ALGAE_OPTION_H */
