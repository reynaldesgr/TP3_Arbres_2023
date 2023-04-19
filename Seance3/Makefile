CC = gcc-11
CFLAGS = -Wall -Wextra -g
LDFLAGS =

#repertoire des fichiers d'unitests teZZt.[ch]
DIRUTEST = ../../

#repertoire des fichiers communs : eltPile.[ch], eltsArbre.h pile.[ch]
DIRCOMM = ../

#liste des fichiers source
SRC = $(wildcard $(DIRCOMM)*.c *.c) $(DIRUTEST)teZZt.c ../Seance1/arbres_construct.c

HEADERS = $(wildcard $(DIRCOMM)*.h *.h) $(DIRUTEST)teZZt.h

#liste des fichiers objets
OBJ = $(SRC:%.c=%.o)

arbres_insert_main: $(OBJ) $(HEADERS)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	
arbres_insert.o: arbres_insert.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
	
../Seance1/arbres_construct.o: ../Seance1/arbres_construct.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

pile.o: pile.c pile.h
	$(CC) $(CFLAGS) -c $< -o $@

$(DIRUTEST)teZZt.o: $(DIRUTEST)teZZt.c $(DIRUTEST)teZZt.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean reclean

clean:
	rm -f $(OBJ)

reclean:
	rm -f $(OBJ) arbres_insert_main
