/*
    Copyright © 2013 Anthony de Almeida Lopes
 */
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <algae/boolean.h>
#include <algae/list.h>

/*
    @note
        In Haskell,

            takeWhile               :: (a -> Bool) -> [a] -> [a]
            takeWhile _ []          =  []
            takeWhile p (x:xs) 
                        | p x       =  x : takeWhile p xs
                        | otherwise =  []
    @note
        Using eliminators,

            takeWhile : (A → Boolean) → (List A) → (List A)
            takeWhile p xs =
                List-elimination xs
                    (nil)
                    (λ x ys .
                        (Boolean-elimination (p x)
                            (nil)
                            (link x ys)
                        )
                    )
 */

/** Returns the longest prefix of `xs` such that each element satisfies the predicate `p`
 */
algae_list_t const *
algae_list_take_while(
    algae_list_t const * const xs,
    algae_boolean_t const * (* const p)(void const * const /* x */)
) {

    void const *
    on_xs_nil(void)
    {
        return algae_list_nil_introduction();
    }

    void const *
    on_xs_link(
        void const * const x,
        algae_list_t const * const ys)
    {
        void const *
        on_predicate_unsatisfied(void)
        {
            return algae_list_nil_introduction();
        }

        void const *
        on_predicate_satisfied(void)
        {
            return algae_list_link_introduction(
                       x,
                       ys
                   );
        }

        assert(x != NULL);
        assert(ys != NULL);

        return algae_boolean_elimination(
                   p(x),
                   on_predicate_unsatisfied,
                   on_predicate_satisfied
               );
    }

    assert(xs != NULL);
    assert(p != NULL);

    return algae_list_elimination(
               xs,
               on_xs_nil,
               on_xs_link
           );
}
