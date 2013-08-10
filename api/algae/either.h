#ifndef ALGAE_EITHER_H
#define ALGAE_EITHER_H

typedef struct algae_either
        algae_either_t;

typedef void const *
        (* algae_either_left_callback_t)(
            void const * const /* x */);

typedef void const *
        (* algae_either_right_callback_t)(
            void const * const /* y */);


algae_either_t const *
algae_either_left_introduction(void const * const /* x */);

algae_either_t const *
algae_either_right_introduction(void const * const /* y */);

void *
algae_either_eliminate(
    algae_either_t const * const /* etr */,
    algae_either_left_callback_t const /* left_cb */,
    algae_either_right_callback_t const /* right_cb */);

#endif /* ALGAE_EITHER_H */
