/**
 * @file pile.c
 * @brief fichier d'implementation pour la gestion de pile
 */
 
#include <stdlib.h>
#include "pile.h"

/** initPile
 * @brief Initialiser une pile du type pile_t
 *   - allocation de memoire pour une structure pile_t et un tableau de taille elements
 * @param [in] taille taille de la pile
 * @return l'adresse de la structure
 */
pile_t * initPile(int t)
{
    pile_t * p = NULL;

    if (t)
    {
        p = (pile_t *) malloc(sizeof(pile_t));
        p->taille = t;
        p->sommet = -1;
        p->base = (eltType_pile *) malloc(t * sizeof(eltType_pile));
    }
    
    return p;
}


/** libererPile
 * @brief Liberer les memoires occupees par la pile
 * @param [in, out] adrPtPile l'adresse du pointeur de la structure pile_t
 */
void libererPile(pile_t ** adrPtPile)
{
    if (*adrPtPile)
    {
        free((*adrPtPile)->base);
        (*adrPtPile)->sommet = -1;
        free(*adrPtPile);
        *adrPtPile = NULL;
    }
}


/** estVidePile
 * @brief Verifier si la pile est vide (aucun element dans la "base")
 * @param [in] ptPile l'adresse de la structure pile_t
 * @return 1 - vide, ou 0 - non vide
 */
int estVidePile(pile_t * ptPile)
{
    return ptPile->sommet == - 1 ? 1 : 0;
}


/** empiler
 * @brief Entrer un element dans la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [in] ptVal l'adresse de la valeur a empiler
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
void empiler(pile_t * ptPile, eltType_pile * ptVal, int * code)
{
    if (ptPile && ptPile->sommet + 1 < ptPile->taille)
    {
        ptPile->sommet+=1;
        ptPile->base[ptPile->sommet] = *ptVal;
        *code = 0;
    }else
    {
        *code = 1;
    }

}


/** depiler
 * @brief Sortir un element de la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [out] ptRes l'adresse de l'element sorti
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
eltType_pile * depiler(pile_t * ptPile, int * code)
{
    eltType_pile * ptRes = NULL;
    
    if (ptPile && !estVidePile(ptPile))
    {
        ptRes = &ptPile->base[ptPile->sommet];
        ptPile->sommet -= 1;
        *code = 0;
    }
    else
    {
        *code = 1;
    }
    
    return ptRes;
}
