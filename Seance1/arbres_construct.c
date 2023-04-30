/**
 * @file arbres_construct.c
 * @brief fichier d'implementation du programme pour la construction d'une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"

//static int index = 0;


/** lirePref_fromFileName
 * @brief lire le fichier contenant la representation prefixee de l'arborescence
 * @param [in] fileName le nom du fichier contenant la representation prefixee
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref l'adresse memoire contenant le nombre des elements du tabEltPref
 * @return le nombre de racines
 */
int lirePref_fromFileName(char * fileName, eltPrefPostFixee_t * tabEltPref, int * nbEltsPref)
{
    FILE * file   = fopen(fileName, "r");
    int index     = 0;
    int nbRacines = 0;

    if (file)
    {
        fscanf(file, "%d ", &nbRacines);

        while(!feof(file))
        {
            (*nbEltsPref)++;
            fscanf(file, "%c %d%*c ", &tabEltPref[index].val, &tabEltPref[index].nbFils);
            index++;
        }
    }

    fclose(file);

    return nbRacines;
}

/** printTabEltPref
 * @brief afficher les elements de la representation prefixee sur un flux de sortie
 * @param file : le flux de sortie
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref le nombre des elements du tabEltPref
 */
void printTabEltPref(FILE * file, eltPrefPostFixee_t * tabEltPref, int nbEltsPref)
{
    int index = 0;

    if (file)
    {
        while (index < nbEltsPref)
        {
            fprintf(file, "(%c,%d)", tabEltPref[index].val, tabEltPref[index].nbFils);
            index++;

            if (index == nbEltsPref){
                fprintf(file, "\n");
            }
            else
            {
                fprintf(file, " ");
            }
        }
    }
}

/** allocPoint
 * @brief creer et initialiser un nouveau point de l'arborescence
 * @param [in] val la valeur du point
 * @return l'adresse du nouveau point 
 */

cell_lvlh_t * allocPoint(int val)
{
    cell_lvlh_t * new_cell;

    if ((new_cell = malloc(sizeof(cell_lvlh_t))) != NULL)
    {
        new_cell->val = val;
        new_cell->lh  = NULL;
        new_cell->lv  = NULL;
    }

    return new_cell;
}



/** prefl2lvlh
 * @brief construire un arbre avec lvlh a partir de representation prefixee
 * @param [in] tabEltPref tableau des elements de la representation prefixee
 * @param [in] nbRacines nombre de racines de l'arborescence
 * @return : 
 *     - NULL si l'arbre resultant est vide
 *     - l'adresse de la racine de l'arbre sinon
*/


// Iteratif (Pile)

cell_lvlh_t * pref2lvlh(eltPrefPostFixee_t * tabEltPref, int nbRacines)
{
    cell_lvlh_t * cell;
    cell_lvlh_t ** cell_lt;

    pile_t * p          = initPile(NB_ELTPREF_MAX);
    int stop            = 0;
    int index           = 0;
    int code;

    eltType_pile elt;
    eltType_pile elt_lt;

    elt.cour = allocPoint(tabEltPref[index].val);
    elt.prec = NULL;
    elt.nb_Fils_ou_Freres = tabEltPref[index].nbFils;
    empiler(p, &elt, &code);
    index++;


    cell_lvlh_t * root = elt.cour;

    while (!stop)
    {
        while (nbRacines != 0 && elt.nb_Fils_ou_Freres)
        {
            elt.prec = elt.cour;
            cell     = allocPoint(tabEltPref[index].val);
            elt.cour = cell;
            elt.nb_Fils_ou_Freres = tabEltPref[index].nbFils;

            if (elt.nb_Fils_ou_Freres)
            {
                empiler(p, &elt, &code);
            }
            index++;
        }
        
        if (!estVidePile(p))
        {
            depiler(p, &elt_lt, &code);

            cell = elt.cour;
            elt_lt.nb_Fils_ou_Freres--;

            if (elt_lt.cour->lv == NULL)
            {
                elt_lt.cour->lv = cell;

            }else{
                cell_lt = &elt_lt.cour->lv;
                while (*cell_lt){
                    cell_lt = &(*cell_lt)->lh;
                } 
                *cell_lt = cell;
            }

            if (elt_lt.nb_Fils_ou_Freres){
                empiler(p, &elt_lt, &code);
            }
            if (!estVidePile(p)){
                elt = elt_lt;
            }else if (nbRacines-- && nbRacines != 0){
                cell_lt = &elt_lt.cour;
                while (*cell_lt)
                {
                    cell_lt = &(*cell_lt)->lh;
                }
                elt.prec = NULL;
                elt.cour = allocPoint(tabEltPref[index].val);
                elt.nb_Fils_ou_Freres = tabEltPref[index].nbFils;
                *cell_lt = elt.cour;

                empiler(p, &elt, &code);
                index++;
            }
        }else{
            stop = 1;
        }
    }

    libererPile(&p);
    return root;
}


/*
// pref2lvlh récursif

cell_lvlh_t * pref2lvlh(eltPrefPostFixee_t * tabEltPref, int nbRacines)
{
  cell_lvlh_t * cell = NULL;
  cell_lvlh_t * cell_lt = NULL;
  int nbFils = 0;

    if ((nbFils = tabEltPref[index].nbFils) != 0){
        cell = allocPoint(tabEltPref[index].val);
        index++;
        cell->lv = pref2lvlh(tabEltPref, 0);

        nbFils--;
        cell_lt = cell->lv;

        while (nbFils)
        {
            index++;
            cell_lt->lh = pref2lvlh(tabEltPref, 0);
            cell_lt = cell_lt->lh;
            nbFils--;
        }

        // si nbRacines > 0 : on se situe au niveau de la/des racines de la forêt
        if (nbRacines){
            index++;
            cell->lh = pref2lvlh(tabEltPref, nbRacines);
        }

    }else{
        cell = allocPoint(tabEltPref[index].val);
        cell->lv = NULL;
    }
  
  return cell;
}
*/


/* **** Fonctions annexes ***** */
// Affichage prefixe
void affichePrefArbre(cell_lvlh_t * root)
{
    if (root){
        printf("%c", root->val);
        affichePrefArbre(root->lv);
        affichePrefArbre(root->lh);
    }
    
}

// Affichage prefixe dans un flux de sortie
void affichePrefArbre_Fichier(FILE * file, cell_lvlh_t * root){
    if (root){
        fprintf(file, "%c ", root->val);
        affichePrefArbre_Fichier(file, root->lv);
        affichePrefArbre_Fichier(file, root->lh);
    }
}
/********************************/

/** libererArbre
 * @brief liberer les blocs memoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */


void libererArbre(cell_lvlh_t ** adrPtRacine)
{
    pile_t * p            = initPile(NB_ELTPREF_MAX);
    int stop            = 0;
    int index           = 0;
    int code;
    eltType_pile elt;
    cell_lvlh_t * elt_to_free;
    elt.cour = *adrPtRacine;


    if (*adrPtRacine)
    {
        while (!stop)
        {
            while (elt.cour->lv)
            {
                empiler(p, &elt, &code);
                elt.cour = elt.cour->lv;
            }

            while (elt.cour->lh)
            {
                empiler(p, &elt, &code);
                elt.cour = elt.cour->lh;
            }
            
            elt_to_free = elt.cour;
            if (elt.cour->lv){
                continue;
            }else if (!estVidePile(p)){
                    depiler(p, &elt, &code);
                    if (elt.cour->lh == elt_to_free){
                        elt.cour->lh = NULL;
                    }else if(elt.cour->lv == elt_to_free){
                        elt.cour->lv = NULL;
                    }
                    free(elt_to_free);
            }else{
                stop = 1;
            }

        }
    }

    free(elt_to_free);
    libererPile(&p);
}
