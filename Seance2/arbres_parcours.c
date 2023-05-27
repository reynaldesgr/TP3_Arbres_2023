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
    cell_lvlh_t * cour = ptCell;        // Pointeur vers la cellule courante
    int           nb   = 0;             // Nombre de fils ou freres

    while (cour)    // Si courant non null, on continue de compter
    {
        nb++;   
        cour = cour->lh;    // Deplacement horizontal 
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
    pile_t * p            = initPile(NB_ELTPREF_MAX); // Initialisation de la pile
    cell_lvlh_t * cell    = racine; 

    int         stop      = 0;
    int         code;

    int         nbRacines = getNbFils_ou_Freres(racine); // On recupere le nombre de racines

    // On construit un element de type pile stockant le noeud courant
    eltType_pile elt;
    elt.cour = cell;

    while (!stop)
    {
        while (elt.cour != NULL) // Si courant non null
        {
            elt.nb_Fils_ou_Freres = getNbFils_ou_Freres(elt.cour->lv); // On recupere son nombre de fils
            empiler(p, &elt, &code);    // Empiler le noeud courant avec son nombre de fils
            elt.cour = elt.cour->lv;   // Deplacement vertical pour le parcours en profondeur
        }

        if (!estVidePile(p))    // Si la pile est NON vide => courant null, on affiche le sommet de la pile
        {
            depiler(p, &elt, &code); 
            fprintf(stream, "(%c,%d) ", elt.cour->val, elt.nb_Fils_ou_Freres);
            elt.cour = elt.cour->lh; // Deplacement horizontal a partir du noeud au sommet de la pile
        }else{
            stop = 1;       // On a explore tout les noeuds => termine 
        }
    }

    fprintf(stream, "%d\n", nbRacines);

    libererPile(&p);
}
