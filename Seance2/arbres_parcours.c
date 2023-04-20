/**
 * @file arbres_parcours.c
 * @brief fichier d'implementation du module pour le parcours d'arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_parcours.h"


/** getNbFils_ou_Freres
 * @brief calculer le nombre de fils ou freres d'un point a partir du pointeur du debut de la liste
 * @param [in] ptCell pointeur vers le 1er frere
 * @return le nombre de fils ou freres
 */

int getNbFils_ou_Freres(cell_lvlh_t * ptCell)
{
    cell_lvlh_t * cour = ptCell;
    int           nb   = 0;

    while (cour)
    {
        nb++;
        cour = cour->lh;
    }

    return nb;
}



/** printPostfixee
 * @brief parcours en profondeur postfixee
 * @param [in] file le flux de sortie
 * @param [in] racine la racine de l'arborescence
 */

void printPostfixee(FILE * stream, cell_lvlh_t * racine)
{
    pile_t * p            = initPile(NB_ELTPREF_MAX);
    cell_lvlh_t * cell    = racine;
    int         stop      = 0;
    int         code;
    int         nbRacines = getNbFils_ou_Freres(racine);
    eltType_pile elt;
    elt.cour = cell;

    while (!stop)
    {
        while (elt.cour != NULL)
        {
            elt.nb_Fils_ou_Freres = getNbFils_ou_Freres(elt.cour->lv);
            empiler(p, &elt, &code);
            elt.cour = elt.cour->lv;
        }

        if (!estVidePile(p))
        {
            depiler(p, &elt, &code);
            fprintf(stream, "(%c,%d) ", elt.cour->val, elt.nb_Fils_ou_Freres);
            elt.cour = elt.cour->lh;
        }else{
            stop = 1;
        }
    }

    fprintf(stream, "%d\n", nbRacines);
    
    libererPile(&p);
}
