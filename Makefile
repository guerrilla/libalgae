#
#    Copyright © 2013 Anthony de Almeida Lopes
#
PROGRAM=test

#
# C Compilation
#
SOURCES=
SOURCES+=src/algae/boolean.c
SOURCES+=src/algae/natural_number.c
SOURCES+=src/algae/optional.c
SOURCES+=src/algae/either.c
SOURCES+=src/algae/list/take_while.c
SOURCES+=src/algae/list.c
#SOURCES+=src/tests.c

CFLAGS=
CFLAGS+=-Wall -W -Werror -Wno-unused -Wswitch-default -Wswitch-enum -Wunused-value
CFLAGS+=-Iapi/ -Isrc/

CC=gcc

#
# Linking
#
OBJECTS=$(SOURCES:.c=.o)

LDFLAGS=

LD=gcc

#
# Rules
#
$(PROGRAM): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROGRAM) $(LDFLAGS)

.c.o: $<
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm `find src -name \*.o`
	rm -f $(PROGRAM)
