/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"
#include "../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_CONSTRUCT)

TEST(nouvCell) {
	printf("\n* Test 1 : Creation cellule... \n");
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );

	free(new);
}

TEST(lirePref_fromFileName_exTP) {
	printf("\n* Test 2 : Lecture de l'arbre prefixee et stockage en memoire...\n");
	int nbRacines = 0;
	int nbEltsPref = 0;

	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	// Recuperation du nombre de racine
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);

	printf("\033[34m\nlirePref_fromFileName_exTP :");
	printf("\033[0m\n");

	// Verification
	CHECK( 2 == nbRacines ); 
	CHECK( 13 == nbEltsPref );
	CHECK( 'A' == tabEltPref[0].val );
	CHECK( 3 == tabEltPref[0].nbFils );

	CHECK( 'B' == tabEltPref[1].val );
	CHECK( 2 == tabEltPref[1].nbFils );

	CHECK( 'C' == tabEltPref[7].val );
	CHECK( 2 == tabEltPref[7].nbFils );
	
	CHECK( 'I' == tabEltPref[nbEltsPref-1].val );
	CHECK( 0 == tabEltPref[nbEltsPref-1].nbFils );

	// Le fichier n'existe pas
	nbEltsPref = 0;
	nbRacines = lirePref_fromFileName("../not_exist.txt", tabEltPref, &nbEltsPref);
	CHECK( 0 == nbRacines );
	CHECK( 0 == nbEltsPref );
	
	// Le fichier est vide
	nbRacines = lirePref_fromFileName("../pref_ex_TP_vide.txt", tabEltPref, &nbEltsPref);
	CHECK ( 0 == nbRacines );
	CHECK( 0 == nbEltsPref );

	// Tout ou une partie du fichier est invalide
	nbRacines = lirePref_fromFileName("../pref_ex_TP_foo.txt", tabEltPref, &nbEltsPref);
	cell_lvlh_t * racine = pref2lvlh(tabEltPref, nbRacines);
	CHECK (nbRacines == 0);
	CHECK (NULL == racine);
}


TEST(printTabEltPref_exTP) {

	printf("\n* Test 3 : Affichage du tableau... \n");
	int nbRacines = 0;
	int nbEltsPref = 0;

	// Declaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[34m\nprintPref_exTP :");
	printf("\033[0m\n");

	// Recuperation du nombre de racines
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	fprintf(file, "%d ", nbRacines);

	// Affichage du tableau
	printTabEltPref(file, tabEltPref, nbEltsPref);
	fclose(file);

	// Verification
	CHECK( 0 == strcmp(buffer, "2 (A,3) (B,2) (E,0) (J,0) (D,0) (H,1) (G,0) (C,2) (F,3) (K,0) (M,0) (T,0) (I,0)\n") ); 
}

// Arbre :
// 2  (A,3)  (B,2)  (E,0)  (J,0)  (D,0)  (H,1) (G,0)  (C,2)  (F,3)  (K,0)  (M,0)  (T,0)  (I,0)

TEST(pref2lvlh1_exTP) {
	
	printf("\n* Test 4 : pref2lvlh - Stockage de l'arbre en mémoire... \n");
	int nbRacines = 0;
	int nbEltsPref = 0;

	// Declaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\npref2lvlh1_exTP :");
	printf("\033[0m\n");

	// Recuperation du nombre de racines
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);

	// Stockage de l'arbre en memoire (pref2lvlh)
	racine = pref2lvlh(tabEltPref, nbRacines);
	
	// Affichage de l'arbre dans le flux de sortie : file
	affichePrefArbre_Fichier(file, racine);

	// Fermeture du fichier
	fclose(file);
	
	// Verification
	CHECK (0 == strcmp(buffer, "A B E J D H G C F K M T I "));
	
	// Liberation de l'arbre
	libererArbre(&racine);

	CHECK(NULL == racine);

	nbRacines = lirePref_fromFileName("../pref_ex_TP_foo.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);
	CHECK (0 == nbRacines);
	CHECK (NULL == racine);
}

END_TEST_GROUP(ARBRE_CONSTRUCT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_CONSTRUCT);
	return EXIT_SUCCESS;
}
