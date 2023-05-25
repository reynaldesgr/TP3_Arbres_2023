/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
// Rajout
#include "../Seance2/arbres_parcours.h"
#include "../Seance1/arbres_construct.h"
#include "arbres_insert.h"
#include "../teZZt.h"



BEGIN_TEST_GROUP(ARBRE_INSERT)

TEST(nouvCell) {
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );

	free(new);
}


TEST(rechercher_v) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	cell_lvlh_t *pere = NULL;

	printf("\033[35m\nrechercher_v :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	pere = rechercher_v(racine, 'X');   // valeur inexistante
	CHECK( NULL == pere );

	pere = rechercher_v(racine, 'A');   // valeur a la racine
	REQUIRE( NULL != pere );
	CHECK( 'A' == pere->val );

// autres tests a ajouter

	libererArbre(&racine);
}


TEST(rechercherPrecFilsTries) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	cell_lvlh_t *pere = NULL;
	cell_lvlh_t **pprec = NULL;

	printf("\033[34m\nrechercherPrecFilsTries :");
	printf("\033[0m\n");
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	pere = rechercher_v(racine, 'F');

	REQUIRE( NULL != pere );
	CHECK( 'F' == pere->val );

	pprec = rechercherPrecFilsTries(pere, 'A');
	REQUIRE( NULL != *pprec );
	CHECK( 'K' == (*pprec)->val );

// autres tests a ajouter

	// Insertion en fin de la liste des fils de F
	pprec = rechercherPrecFilsTries(pere, 'U');
	REQUIRE(NULL == *pprec);

	libererArbre(&racine);
}

TEST(insererTrie) {
	int nbRacines  = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t * racine = NULL;

	int realisation;

	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE (NULL != file);

	printf("\033[34m\nrechercherPrecFilsTries :");
	printf("\033[0m\n");
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	// Cas 1 : insertion en fin de lien horizontal LH
	printf("\n* Cas 1 : Insertion en fin de lien horizontal... \n");
	realisation = insererTrie(racine, 'B', 'Z');
	printPostfixee(stdout, racine);

	// Vérification Cas 1
	printPostfixee(file, racine);
	CHECK(1 == realisation);
	fclose(file);
	CHECK(0 == strcmp(buffer, "(E,0) (J,0) (Z,0) (B,3) (D,0) (G,0) (H,1) (A,3) (K,0) (M,0) (T,0) (F,3) (I,0) (C,2) 2\n"));
	//-------------------------------------------------------------------------------------------------------------------------

	// Cas 2 : insertion en début de lien horizontal LH
	printf("\n* Cas 2 : Insertion en début de lien horizontal... \n");
	file = fmemopen(buffer, 1024, "w");
	realisation = insererTrie(racine, 'E', 'P');

	// Vérification Cas 2
	CHECK(1 == realisation);
	printPostfixee(file, racine);
	fclose(file);
	CHECK(0 == strcmp(buffer, "(P,0) (E,1) (J,0) (Z,0) (B,3) (D,0) (G,0) (H,1) (A,3) (K,0) (M,0) (T,0) (F,3) (I,0) (C,2) 2\n"));

	//-------------------------------------------------------------------------------------------------------------------------
	// Cas 3 : insertion entre 2 noeuds d'un lien horizontal LH
	printf("\n* Cas 3 : Insertion entre 2 noeuds... \n");
	file = fmemopen(buffer, 1024, "w");
	realisation = insererTrie(racine, 'F',  'L');
	printPostfixee(stdout, racine);

	// Vérification Cas 3
	printPostfixee(file, racine);
	CHECK(1 == realisation);
	fclose(file);
	CHECK(0 == strcmp(buffer, "(P,0) (E,1) (J,0) (Z,0) (B,3) (D,0) (G,0) (H,1) (A,3) (K,0) (L,0) (M,0) (T,0) (F,4) (I,0) (C,2) 2\n"));

	//-------------------------------------------------------------------------------------------------------------------------
	// Cas 4 : insertion à partir d'un noeud inexistant
	printf("\n* Cas 4 : Insertion à partir d'un noeud inexistant... \n");
	realisation = insererTrie(racine, '9', 'T');
	printPostfixee(stdout, racine);

	// Vérification Cas 4
	printPostfixee(file, racine);
	CHECK(0 == realisation);
	fclose(file);
	// L'arbre reste inchangé 
	CHECK(0 == strcmp(buffer, "(P,0) (E,1) (J,0) (Z,0) (B,3) (D,0) (G,0) (H,1) (A,3) (K,0) (L,0) (M,0) (T,0) (F,4) (I,0) (C,2) 2\n"));

	// Libération
	libererArbre(&racine);
}

END_TEST_GROUP(ARBRE_INSERT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_INSERT);
	return EXIT_SUCCESS;
}
