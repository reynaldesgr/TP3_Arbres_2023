/**
 * @file eltPile.h
 * @brief fichier d'entete pour la gestion du type des elements de pile
 */
#ifndef __ELTPILE_H__
#define __ELTPILE_H__

#include "eltsArbre.h"

/** Structure element pile : eltType_pile
 * @struct eltType_pile
 * @brief definir la SDD des elements de pile
 * 3 champs :
 *   - adrCell : l'adresse d'un point/cellule d'une arborescence
 *   - adrPrec : l'adresse du pointeur prec du point
 *   - nbFils_ou_Freres : le nombre de fils ou freres d'un point 
 */

typedef struct eltType_pile
{
    cell_lvlh_t * cour;
    cell_lvlh_t * prec;
    int nb_Fils_ou_Freres;
    
} eltType_pile;

/** copyElt()
 * @brief Copier la valeur d'un element dans un autre emplacement
 * @param [in] xxx l'adresse de l'element a copier
 * @param [in] xxx l'adresse de la destination
 */

void copyElt(eltType_pile * source, eltType_pile * destination);

#endif