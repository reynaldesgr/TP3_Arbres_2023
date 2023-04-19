CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =

#repertoire des fichiers d'unitests teZZt.[ch]
DIRUTEST = ../

#repertoire des fichiers communs : eltPile.[ch], eltsArbre.h pile.[ch]
DIRCOMM = ../

#liste des fichiers source
SRC = $(wildcard $(DIRCOMM)*.c *.c)

HEADERS = $(wildcard $(DIRCOMM)*.h *.h)

#liste des fichiers objets
OBJ = $(SRC:%.c=%.o)

arbres_construct_main: $(OBJ) $(HEADERS)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	
arbres_construct.o: arbres_construct.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

pile.o: pile.c pile.h
	$(CC) $(CFLAGS) -c $< -o $@

$(DIRUTEST)teZZt.o: $(DIRUTEST)teZZt.c $(DIRUTEST)teZZt.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean reclean

clean:
	rm -f $(OBJ)

reclean:
	rm -f $(OBJ) arbres_construct_main
