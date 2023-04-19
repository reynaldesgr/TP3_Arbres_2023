/**
 * @file arbres_construct.h
 * @brief fichier d'entete du module pour la construction d'arborescence
 */
#ifndef __ARBRE_CONSTRUCT_H__
#define __ARBRE_CONSTRUCT_H__

#include "../eltsArbre.h"

/** TO DO
 * @brief lire le fichier contenant la representation prefixee de l'arborescence
 * @param [in] fileName le nom du fichier contenant la representation prefixee
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref l'adresse memoire contenant le nombre des elements du tabEltPref
 * @return le nombre de racines
 */
int lirePref_fromFileName(char * fileName, eltPrefPostFixee_t * tabEltPref, int * nbEltsPref);

/** TO DO
 * @brief afficher les elements de la representation prefixee sur un flux de sortie
 * @param file : le flux de sortie
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref le nombre des elements du tabEltPref
 */
void printTabEltPref(FILE *, eltPrefPostFixee_t *, int);

/** TO DO
 * @brief creer et initialiser un nouveau point de l'arborescence
 * @param [in] val la valeur du point de type char
 * @return l'adresse du nouveau point 
 */
cell_lvlh_t * allocPoint(int);

/**
 * @brief construire un arbre avec lvlh a partir de representation prefixee
 * @param [in] tabEltPref tableau des elements de la representation prefixee
 * @param [in] nbRacines nombre de racines de l'arborescence
 * @return : 
 *     - NULL si l'arbre resultatnt est vide
 *     - l'adresse de la racine de l'arbre sinon
*/
cell_lvlh_t * pref2lvlh(eltPrefPostFixee_t * tabEltPref, int nbRacines);

/** TO DO
 * @brief liberer les blocs memoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */
// libererArbre();


void afficheArbre(cell_lvlh_t * root);


#endif