/**
 * @file arbres_construct.c
 * @brief fichier d'implementation du programme pour la construction d'une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"

static int index = 0;

/**
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

    return nbRacines;
}

/** TO DO
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

/** TO DO
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

/** TO DO
 * @brief construire un arbre avec lvlh a partir de representation prefixee
 * @param [in] tabEltPref tableau des elements de la representation prefixee
 * @param [in] nbRacines nombre de racines de l'arborescence
 * @return : 
 *     - NULL si l'arbre resultatnt est vide
 *     - l'adresse de la racine de l'arbre sinon
*/

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

// Affichage prefixe
void afficheArbre(cell_lvlh_t * root)
{
    if (root){
        printf("%c", root->val);
        afficheArbre(root->lv);
        afficheArbre(root->lh);
    }
    
}

/** TO DO
 * @brief liberer les blocs memoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */
void libererArbre(cell_lvlh_t ** adrPtRacine)
{
    cell_lvlh_t * cour;

    if (*adrPtRacine)
    {
        cour = *adrPtRacine;
        if (cour->lv){
            libererArbre(&cour->lv);
        }
        
        free(cour);

        if(cour->lh){
            libererArbre(&cour->lh);
        }
    }
}
