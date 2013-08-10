#ifndef ALGAE_PRODUCT_H
#define ALGAE_PRODUCT_H

typedef struct algae_product
        algae_product_t;

typedef void const *
        (* algae_product_pair_callback_t)(
            void const * const /* x */,
            void const * const /* y */);

algae_product_t const *
algae_product_pair_introduction(
    void const * const /* x */,
    void const * const /* y */);

void const *
algae_product_elimination(
    algae_product_t const * const /* p */,
    algae_product_pair_callback_t const /* pair_cb */);

#endif /* ALGAE_PRODUCT_H */
