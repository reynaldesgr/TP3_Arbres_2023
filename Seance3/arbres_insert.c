/**
 * @file arbres_insert.c
 * @brief fichier d'implementation du module pour l'insertion de valeur dans une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_insert.h"

// Rajout
#include "../Seance1/arbres_construct.h"



/** rechercher_v
 * @brief rechercher un point de valeur v
 * @param [in] racine pointeur vers la racine de l'arborescence 
 * @return 
 *   - l'adresse du point contenant v si v existe dans l'arborescence
 *   - NULL, sinon
 */

cell_lvlh_t * rechercher_v(cell_lvlh_t * root, char v){
    
    pile_t * p = initPile(NB_ELTPREF_MAX); // Initialisation de la pile

    // Declaration element de type pile
    eltType_pile elt;

    // On commence par la racine
    elt.cour = root;

    int code;

    // Tant que le noeud courant existe et que sa valeur != v
    while (elt.cour && elt.cour->val != v)
    {
        empiler(p, &elt, &code); // On empile
        elt.cour = elt.cour->lv; // Deplacement vertical pour effectuer le parcours en profondeur

        while (elt.cour == NULL && !estVidePile(p)){
            elt = *(depiler(p, &code));
            elt.cour = elt.cour->lh; // Deplacement horizontal
        } 
    }

    // Liberation de la memoire utilise par la pile
    libererPile(&p);

    return elt.cour;
}

/** rechercherPrecFilsTries
 * @brief rechercher le double prec de w dans une liste de fils
 * @param [in] adrPere l'adresse du pere
 * @param [in] w la valeur a inserer
 * @return l'adresse du pointeur prec apres lequel w doit etre inseree
 */

cell_lvlh_t ** rechercherPrecFilsTries(cell_lvlh_t * adrPere, char w)
{
    cell_lvlh_t ** pprec; // Pointeur prec apres lequel w sera inseree
    
    pprec = &(adrPere->lv); // Deplacement vertical a partir de l'adresse du pere

    while (*pprec != NULL && (*pprec)->val < w)  // Tant que le pointeur prec a une valeur inferieur a w
    {
        pprec = &(*pprec)->lh; // Deplacement horizontal (parcours des fils/freres)
    }

    return pprec;
}

/** insererTrie
 * @brief inserer une valeur w dans les fils d'un point de valeur v
 * @param [in, out] racine la racine de l'arborescence
 * @param [in] v la valeur d'un point auquel on va inserer la valeur w en fils
 * @param [in] w la valeur a inserer
 * @return 1 - insertion realisee; 0 - insertion n'a pas ete realisee
 */

int insererTrie(cell_lvlh_t * racine, char v, char w)
{
    cell_lvlh_t * pere = rechercher_v(racine, v); // Chercher la valeur v a partir de laquelle doit etre ajoute w
    
    int realisation = 0;

    // Si la valeur v (pere) existe 
    if (pere != NULL)
    {
        cell_lvlh_t ** pprec = rechercherPrecFilsTries(pere, w); // Chercher une place parmi les fils de pere ou doit etre inserer w 
        cell_lvlh_t * nouv = allocPoint(w); // Allocation nouveau point de valeur w

        if (nouv != NULL)       // Si allocation reussie, initialisation de w et chainage avec pprec
        {
            nouv->val = w;
            nouv->lv = NULL;
            nouv->lh = *pprec;
            *pprec = nouv;
            realisation = 1;
        }
    }
    return realisation;
}
