#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
    nothing : 1 -> m A
    just : A -> m A

    @source @uri "http://www.haskell.org/haskellwiki/Monad_laws"

        m :: * -> *
        return :: a -> m a
        (>>=) :: m a -> (a -> m b) -> m b
        (>>) :: m a -> m b -> m b

        return x >>= f ≡ f x
        m >>= return ≡ m
        (m >>= f) >>= g ≡ m >>= (\x -> f x >>= g)
 */

/*
    use containerof? why would we need the address of the structure that contains
        the monad_t?
 */

/* @task make list monad */
typedef struct list list_t;

struct list { 
    enum {
        LIST_CTOR_NIL,
        LIST_CTOR_LINK
    } ctor;
    union {
        struct { } nil;
        struct { void *x;
                 list_t *xs; } link;
    } data;
};

typedef struct maybe maybe_t;

struct maybe {
    enum {
        MAYBE_CTOR_NOTHING,
        MAYBE_CTOR_JUST
    } ctor;
    union {
        struct { } nothing;
        struct { void const * x; } just;
    } data;
};

struct io {
    enum {
        IO_CTOR_OPEN_FILE,
        IO_CTOR_WRITE,
    } ctor;
    union {

    } data;
};

maybe_t * maybe_nothing(void) {

    maybe_t *m = NULL;

    m = malloc(sizeof(maybe_t));
    assert(m != NULL);

    memset(m, 0x0, sizeof(maybe_t));

    m->ctor = MAYBE_CTOR_NOTHING;

    return (m);
}

maybe_t * maybe_just(void const * const x) {

    maybe_t *m = NULL;

    m = malloc(sizeof(maybe_t));
    assert(m != NULL);

    memset(m, 0x00, sizeof(maybe_t));

    m->ctor = MAYBE_CTOR_JUST;
    m->data.just.x = x;

    return (m);
}

/*
    return :: a -> Maybe a
    return x = Just x
 */
maybe_t * maybe_monad_unit(void *x) {

    return (maybe_just(x));
}

/*
    (>>=) :: Maybe a -> (a -> Maybe b) -> Maybe b
    (Nothing) >>= f = Nothing
    (Just x)  >>= f = f x
 */
maybe_t * maybe_monad_bind(maybe_t const * const v,
                           maybe_t * (*f)(void const * const /* x */)
                          ) {

    assert(v != NULL);
    assert(f != NULL);

    switch (v->ctor) {
        case MAYBE_CTOR_NOTHING:
            goto nothing;

        case MAYBE_CTOR_JUST:
            goto just;

        default:
            abort(); /* not reached */
    }

nothing:
    return maybe_nothing();

just:
    return f(v->data.just.x);
}

void * real_add(void const * const x, void const * const y) {

    return (void *)((intptr_t)x + (intptr_t)y);
}

maybe_t * add(maybe_t * mx, maybe_t * my) {

    maybe_t * add_x(void const * const x) {

        maybe_t * add_x_y(void const * const y) {
            return (maybe_monad_unit(real_add(x, y)));
        }

        return (maybe_monad_bind(my, add_x_y));
    }

    return (maybe_monad_bind(mx, add_x));
};


int main(int argc, char *argv[]) {

    maybe_t *r35 = NULL,
            *r2n = NULL,
            *rn7 = NULL;

    r35 = add(maybe_just((void *)3),
              maybe_just((void *)5)
             );

    assert(r35 != NULL);
    assert(r35->ctor == MAYBE_CTOR_JUST);
    assert(r35->data.just.x == (void *)8);

    r2n = add(maybe_just((void *)2),
              maybe_nothing()
             );

    assert(r2n != NULL);
    assert(r2n->ctor == MAYBE_CTOR_NOTHING);

    rn7 = add(maybe_nothing(),
              maybe_just((void *)7)
             );

    assert(rn7 != NULL);
    assert(rn7->ctor == MAYBE_CTOR_NOTHING);
    
    printf("%08p\n", (intptr_t)argv & (~0x0fff) );

    return (0);
}
