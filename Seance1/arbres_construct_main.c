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

	// Verification allocation (noeud avec la valeur A)
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

	// Verification premiere case
	CHECK( 'A' == tabEltPref[0].val );
	CHECK( 3 == tabEltPref[0].nbFils );

	// Verification seconde case
	CHECK( 'B' == tabEltPref[1].val );
	CHECK( 2 == tabEltPref[1].nbFils );

	// Verification case situe au milieu du tableau
	CHECK( 'C' == tabEltPref[7].val );
	CHECK( 2 == tabEltPref[7].nbFils );

	// Verification derniere case
	CHECK( 'I' == tabEltPref[nbEltsPref-1].val );
	CHECK( 0 == tabEltPref[nbEltsPref-1].nbFils );

	// Cas : Le fichier n'existe pas
	nbEltsPref = 0;
	nbRacines = lirePref_fromFileName("../not_exist.txt", tabEltPref, &nbEltsPref);
	CHECK( 0 == nbRacines );
	CHECK( 0 == nbEltsPref );
	
	//Cas : Le fichier est vide
	nbRacines = lirePref_fromFileName("../pref_ex_TP_vide.txt", tabEltPref, &nbEltsPref);
	CHECK ( 0 == nbRacines );
	CHECK( 0 == nbEltsPref );
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

	printTabEltPref(file, tabEltPref, nbEltsPref);
	fclose(file);

	// Verification
	CHECK( 0 == strcmp(buffer, "2 (A,3) (B,2) (E,0) (J,0) (D,0) (H,1) (G,0) (C,2) (F,3) (K,0) (M,0) (T,0) (I,0)\n") );


	// Cas ou le fichier n'existe pas, on verifie si le buffer est la chaine vide
	printf("\n> Cas 1 : Fichier inexistant... \n");
	char buffer2[1024];
	nbEltsPref = 0;
	FILE * file_2 = fmemopen(buffer2, 1024, "w");
	REQUIRE ( NULL != file_2 );

	// Lecture et recuperation du nombre de racines	
	nbRacines = lirePref_fromFileName("../not_exist.txt", tabEltPref, &nbEltsPref);

	printTabEltPref(file_2, tabEltPref, nbEltsPref);
	fclose(file_2);

	// Verification
	CHECK( 0 == strcmp(buffer2, "0 "));


	// Cas ou le fichier est vide, on verifie si le buffer est la chaine vide
	printf("\n> Cas 2 : Fichier vide... \n");
	nbEltsPref = 0;
	nbEltsPref = 0;
	char buffer3[1024];
	FILE * file_3 = fmemopen(buffer3, 1024, "w");
	REQUIRE ( NULL != file_3 );

	// Lecture et recuperation du nombre de racines
	nbRacines = lirePref_fromFileName("../pref_ex_TP_vide.txt", tabEltPref, &nbEltsPref);
	
	printTabEltPref(file_3, tabEltPref, nbEltsPref);

	fclose(file_3);

	// Verification
	CHECK( 0 == strcmp(buffer3, "0 "));
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
}

TEST(pref2lvlh_ex_TP_vide)
{
	printf("\n* Test 5 : pref2lvlh - Fichier vide... \n");
	int nbRacines = 0;
	int nbEltsPref = 0;

	// Declaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	// Buffer
	char buffer[1024];
	strcpy(buffer, "");

	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\npref2lvlh1_ex_TP_vide :");
	printf("\033[0m\n");

	// Recuperation du nombre de racines
	nbRacines = lirePref_fromFileName("../pref_ex_TP_vide.txt", tabEltPref, &nbEltsPref);

	// Verification racine nulle
	racine = pref2lvlh(tabEltPref, nbRacines);
	CHECK( NULL == racine );

	// Verification
	affichePrefArbre_Fichier(file, racine);
	fclose(file);
	
	CHECK (0 == strcmp(buffer, ""));
}

TEST(pref2lvlh_fichier_inexistant)
{
	printf("\n* Test 5 : pref2lvlh - Fichier inexistant... \n");
	int nbRacines = 0;
	int nbEltsPref = 0;

	// Declaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	strcpy(buffer, "");

	REQUIRE ( NULL != file);

	printf("\033[35m\npref2lvlh_fichier_inexistant :");
	printf("\033[0m\n");

	// Recuperation du nombre de racines
	nbRacines = lirePref_fromFileName("../not_existing.txt", tabEltPref, &nbEltsPref);

	// Verification racine nulle
	racine = pref2lvlh(tabEltPref, nbRacines);
	CHECK( NULL == racine );

	affichePrefArbre_Fichier(file, racine);
	fclose(file);
	
	CHECK (0 == strcmp(buffer, ""));
}

TEST(pref2lvlh_fichier_avec_1_racine)
{
	printf("\n* Test 6 : pref2lvlh - Fichier avec 1 unique racine... \n");
	int nbRacines = 0;
	int nbEltsPref = 0;

	// Declaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	strcpy(buffer, "");

	REQUIRE ( NULL != file);

	printf("\033[35m\npref2lvlh_fichier_avec_1_racines :");
	printf("\033[0m\n");

	// Recuperation du nombre de racines
	nbRacines = lirePref_fromFileName("files/arbre_1racine.txt", tabEltPref, &nbEltsPref);

	// Stockage de l'arbre en memoire (pref2lvlh)
	racine = pref2lvlh(tabEltPref, nbRacines);
	CHECK( NULL != racine );

	affichePrefArbre_Fichier(file, racine);
	fclose(file);
	
	CHECK (0 == strcmp(buffer, "S "));

	// Liberation de l'arbre
	libererArbre(&racine);

	CHECK(NULL == racine);
}

TEST(pref2lvlh_fichier_avec_uniquement_des_liens_verticaux)
{
	printf("\n* Test 7 : pref2lvlh - Fichier avec uniquement des liens verticaux... \n");
	int nbRacines = 0;
	int nbEltsPref = 0;

	// Declaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	strcpy(buffer, "");

	REQUIRE ( NULL != file);

	printf("\033[35m\npref2lvlh_fichier_avec_uniquement_des_liens_verticaux :");
	printf("\033[0m\n");

	// Recuperation du nombre de racines
	nbRacines = lirePref_fromFileName("files/arbre_lv.txt", tabEltPref, &nbEltsPref);
	CHECK(nbRacines == 1);

	// Stockage de l'arbre en memoire (pref2lvlh)
	racine = pref2lvlh(tabEltPref, nbRacines);
	CHECK( NULL != racine );

	affichePrefArbre_Fichier(file, racine);
	fclose(file);
	
	CHECK (0 == strcmp(buffer, "A B Z E R T U V Z "));

	// Liberation de l'arbre
	libererArbre(&racine);

	CHECK(NULL == racine);
}

TEST(pref2lvlh_fichier_avec_uniquement_des_liens_horizontaux)
{
	printf("\n* Test 8 : pref2lvlh - Fichier avec uniquement des liens horizontaux... \n");
	int nbRacines = 0;
	int nbEltsPref = 0;

	// Declaration du tableau
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	// Buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	strcpy(buffer, "");

	REQUIRE ( NULL != file);

	printf("\033[35m\npref2lvlh_fichier_avec_uniquement_des_liens_horizontaux :");
	printf("\033[0m\n");

	// Recuperation du nombre de racines
	nbRacines = lirePref_fromFileName("files/arbre_lh.txt", tabEltPref, &nbEltsPref);
	CHECK(nbRacines == 9);
	
	// Stockage de l'arbre en memoire (pref2lvlh)
	racine = pref2lvlh(tabEltPref, nbRacines);
	CHECK( NULL != racine );

	affichePrefArbre_Fichier(file, racine);
	fclose(file);
	
	CHECK (0 == strcmp(buffer, "A B Z E R T U V Z "));

	// Liberation de l'arbre
	libererArbre(&racine);

	CHECK(NULL == racine);
}


END_TEST_GROUP(ARBRE_CONSTRUCT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_CONSTRUCT);
	return EXIT_SUCCESS;
}
