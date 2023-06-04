/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "../Seance1/arbres_construct.h"
#include "arbres_parcours.h"
#include "../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_PARCOURS)

TEST(nouvCell) {

	printf("\n* Test 1 : Création d'une nouvelle cellule...\n");

	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );

	// Liberation
	free(new);
}


TEST(getNbFils_ou_Freres) {

	printf("\n* Test 2 : getNbFils_ou_Freres \n");

	int nbRacines = 0;
	int nbEltsPref = 0;

	// Declaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	// Racine
	cell_lvlh_t *racine = NULL;
	
	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\ngetNbFils_ou_Freres :");
	printf("\033[0m\n");

	/// Recuperation du nombre de racine / Stockage de l'arbre dans tabEltPref
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);

	// Stockage de l'arbre en memoire (pref2lvlh)
	racine = pref2lvlh(tabEltPref, nbRacines);
	
	// Verification
	REQUIRE( NULL != racine );
	printf("A = %c\n", racine->val);
	CHECK( 2 == getNbFils_ou_Freres(racine) );     // 2 freres y compris lui-meme
	CHECK( 3 == getNbFils_ou_Freres(racine->lv) ); // 3 fils

	REQUIRE( NULL != racine->lv );
	printf("B = %c\n", racine->lv->val);
	CHECK( 3 == getNbFils_ou_Freres(racine->lv) );     // 3 freres y compris lui-meme
	CHECK( 2 == getNbFils_ou_Freres(racine->lv->lv) ); // 2 fils

	REQUIRE( NULL != racine->lv->lh );
	printf("D = %c\n", racine->lv->lh->val);
	CHECK( 0 == getNbFils_ou_Freres(racine->lv->lh->lv) ); // 0 fils

	REQUIRE( NULL != racine->lv->lh->lh );
	printf("H = %c\n", racine->lv->lh->lh->val);
	CHECK( 1 == getNbFils_ou_Freres(racine->lv->lh->lh->lv) ); // 1 fils

	// Fermeture du flux de sortie
	fclose(file);

	// Liberation
	libererArbre(&racine);
}


TEST(printPostfixee) {

	printf("\n * Test 3 : printPostfixe...\n");
	int nbRacines = 0;
	int nbEltsPref = 0;

	// Declaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	// Racine
	cell_lvlh_t *racine = NULL;
	
	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\nprintPostFixee :");
	printf("\033[0m\n");

	// Recuperer le nombre de racines / Stockage de l'arbre dans le tableau
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);

	// Stockage de l'arbre en mémoire
	racine = pref2lvlh(tabEltPref, nbRacines);

	// Afficher l'arbre dans le flux de sortie (<=> buffer)
	printPostfixee(file, racine);

	// Fermeture du flux
	fclose(file);

	// Vérification
	CHECK( 0 == strcmp(buffer,"(E,0) (J,0) (B,2) (D,0) (G,0) (H,1) (A,3) (K,0) (M,0) (T,0) (F,3) (I,0) (C,2) 2\n") );
	
	// Libération
	libererArbre(&racine);
}

printf("\n= Test parcours d'une arborescence sur différents cas =\n");

// Cas 1 : Arbre vide
TEST(CAS1)
{
	printf("\n* CAS 1 : Arbre vide \n");

	int nbRacines = 0;
	int nbEltsPref = 0;

	// Déclaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	
	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\nCas : Arbre vide :");
	printf("\033[0m\n");

	// Récuperer le nombre de racines / Stockage de l'arbre dans le tableau tabEltPref
	nbRacines = lirePref_fromFileName("./files/arbre_test1.txt", tabEltPref, &nbEltsPref);

	// Vérification
	CHECK(0 == nbRacines);

	fclose(file);
}

// Cas 2 : Parcours d'un arbre ne contenant que des liens horizontaux (pas de lien verticaux LV)
TEST(CAS2)
{
	printf("\n* CAS 2 : Parcours d'un arbre ne contenant que des liens horizontaux...\n");

	int nbRacines = 0;
	int nbEltsPref = 0;

	// Déclaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	// Racine
	cell_lvlh_t *racine = NULL;
	
	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\nCas : Arbre avec seulement des liens LH : ");
	printf("\033[0m\n");

	// Récupérer le nombre de racines / Stockage de l'arbre dans le tableau
	nbRacines = lirePref_fromFileName("./files/arbre_test2.txt", tabEltPref, &nbEltsPref);
	CHECK(3 == nbRacines);

	// Affichage du tableau sur stdout
	printTabEltPref(stdout, tabEltPref, nbEltsPref);

	// Stockage de l'arbre en mémoire / Récuperation de la racine
	racine = pref2lvlh(tabEltPref, nbRacines);

	// Affichage de l'arbre sur stdout + buffer
	printPostfixee(stdout, racine);
	printPostfixee(file, racine);

	fclose(file);

	CHECK( 0 == strcmp(buffer, "(A,0) (C,0) (D,0) 3\n"));
	libererArbre(&racine);
}


// Cas 3 : Parcours d'un arbre ne contenant que des liens verticaux (pas de lien verticaux LH)
TEST(CAS3)
{
	printf("\n* CAS 3 : Parcours d'un arbre ne contenant que des liens horizontaux...\n");

	int nbRacines = 0;
	int nbEltsPref = 0;

	// Déclaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	// Racine
	cell_lvlh_t *racine = NULL;
	
	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\nCas : Arbre avec seulement des liens LV : ");
	printf("\033[0m\n");

	// Récupérer le nombre de racines / Stockage de l'arbre dans le tableau
	nbRacines = lirePref_fromFileName("./files/arbre_test3.txt", tabEltPref, &nbEltsPref);
	CHECK(1 == nbRacines);

	// Affichage du tableau sur stdout
	printTabEltPref(stdout, tabEltPref, nbEltsPref);

	// Stockage de l'arbre en mémoire / Récuperation de la racine
	racine = pref2lvlh(tabEltPref, nbRacines);

	// Affichage de l'arbre sur stdout + buffer
	printPostfixee(stdout, racine);
	printPostfixee(file, racine);

	fclose(file);

	CHECK( 0 == strcmp(buffer, "(Z,0) (V,1) (U,1) (T,1) (R,1) (E,1) (Z,1) (B,1) (A,1) 1\n"));
	libererArbre(&racine);
}

// Cas 4 : Arbre avec 1 seul element
TEST(CAS4)
{
	printf("\n* CAS 3 : Parcours d'un arbre ne contenant que 1 seul element...\n");

	int nbRacines = 0;
	int nbEltsPref = 0;

	// Déclaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	// Racine
	cell_lvlh_t *racine = NULL;
	
	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\nCas : Arbre avec un seul/unique element : ");
	printf("\033[0m\n");

	// Récupérer le nombre de racines / Stockage de l'arbre dans le tableau
	nbRacines = lirePref_fromFileName("./files/arbre_1elem.txt", tabEltPref, &nbEltsPref);
	CHECK(1 == nbRacines);

	// Affichage du tableau sur stdout
	printTabEltPref(stdout, tabEltPref, nbEltsPref);

	// Stockage de l'arbre en mémoire / Récuperation de la racine
	racine = pref2lvlh(tabEltPref, nbRacines);

	// Affichage de l'arbre sur stdout + buffer
	printPostfixee(stdout, racine);
	printPostfixee(file, racine);

	fclose(file);

	CHECK( 0 == strcmp(buffer, "(A,0) 1\n"));
	libererArbre(&racine);
}

END_TEST_GROUP(ARBRE_PARCOURS)

int main(void) {
	RUN_TEST_GROUP(ARBRE_PARCOURS);
	return EXIT_SUCCESS;
}
