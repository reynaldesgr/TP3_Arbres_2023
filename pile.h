/**
 * @file pile.h
 * @brief fichier d'entete pour la gestion de pile
 */
#ifndef __PILE_H__
#define __PILE_H__

#include "eltPile.h"

/**
 * @brief taille de la pile (au cas ou)
 * @def PILE_SZ
 */
#define PILE_SZ 256

/** TO DO
 * @struct pile_t
 * @brief definit la structure de donnees de la pile
 */
// TO DO
typedef struct pile
{
    int taille;
    int sommet;
    eltType_pile * base;

} pile_t;

/** TO DO
 * @brief Initialiser une pile du type pile_t
 *   - allocation de memoire pour une structure pile_t et un tableau de taille elements
 * @param [in] taille taille de la pile
 * @return l'adresse de la structure
 */
pile_t * initPile(int t);

/** TO DO
 * @brief Liberer les memoires occupees par la pile
 * @param [in, out] adrPtPile l'adresse du pointeur de la structure pile_t
 */
void libererPile(pile_t ** adrPtPile);

/** TO DO
 * @brief Verifier si la pile est vide (aucun element dans la "base")
 * @param [in] ptPile l'adresse de la structure pile_t
 * @return 1 - vide, ou 0 - non vide
 */
int estVidePile(pile_t * ptPile);

/** TO DO
 * @brief Entrer un element dans la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [in] ptVal l'adresse de la valeur a empiler
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
void empiler(pile_t * ptPile, eltType_pile * ptVal, int * code);

/** TO DO
 * @brief Sortir un element de la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [out] ptRes l'adresse de l'element sorti
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
void depiler(pile_t * ptPile, eltType_pile * ptRes, int * code);


#endif