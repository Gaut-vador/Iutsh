# Ces cibles ne sont pas des vrais fichiers
.PHONY: clean
# On désactive toutes les règles implicites
.SUFFIXES:
# Déclarations de constantes
CC = gcc
CFLAGS = -Werror -W -Wall
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

# compilation finale
main: $(OBJECTS)
	$(CC) -o $@ $^

# Règle générique : $< == le fichier .c compilé
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o
