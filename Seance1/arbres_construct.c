/**
 * @file arbres_construct.c
 * @brief fichier d'implementation du programme pour la construction d'une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"


/** lirePref_fromFileName
 * @brief lire le fichier contenant la representation prefixee de l'arborescence
 * @param [in] fileName le nom du fichier contenant la representation prefixee
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref l'adresse memoire contenant le nombre des elements du tabEltPref
 * @return le nombre de racines
 */

int lirePref_fromFileName(char * fileName, eltPrefPostFixee_t * tabEltPref, int * nbEltsPref)
{
    FILE * file   = fopen(fileName, "r"); // Ouverture du fichier en mode lecture

    int index     = 0;  // Index du tableau
    int nbRacines = 0;  // Nombre de racines

    if (file) // Si le fichier existe
    {
        fscanf(file, "%d ", &nbRacines); // On recupere le 1er caractere du fichier <=> correspondant au nombre de racines

        while(!feof(file)) // Tant que la fin du fichier pas atteinte
        {
            (*nbEltsPref)++; // On compte les elements
            fscanf(file, "%c %d%*c ", &tabEltPref[index].val, &tabEltPref[index].nbFils); // On stocke la valeur du noeud et son nombre de fils
            index++; // Incrementation de index
        }
    }

    fclose(file); // Fermeture du fichier

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

    // Si le fichier existe
    if (file)
    {
        while (index < nbEltsPref) // Tant que tout les elements de tabEltPref ne sont pas parcourus
        {
            fprintf(file, "(%c,%d)", tabEltPref[index].val, tabEltPref[index].nbFils); // Affichage du noeud
            index++; // Incrementation de index

            if (index == nbEltsPref){ // Si affichage du dernier noeud => retour a la ligne
                fprintf(file, "\n");
            }
            else // Sinon => espace
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



/** pref2lvlh
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

    int index = 0; // Index de parcous du tableau (tabEltPref)
    int code; 

    // Initialisation de la pile
    pile_t * p = initPile(NB_ELTPREF_MAX);

    // Adresse vers la racine 
    cell_lvlh_t * adrTete = NULL;

    // Pointeur sur le prec
    cell_lvlh_t ** pprec  = &adrTete;

    cell_lvlh_t * nouv;

    eltType_pile elt;
    
    int nb_fouf = nbRacines;

    // Tant que le nombre de fils ou de freres non null OU pile non vide
    while (nb_fouf > 0 || !estVidePile(p))
    {
        if (nb_fouf > 0){   // Si le noeud possede des fils
            nouv = allocPoint(tabEltPref[index].val); // Allocation cellule arbre
            *pprec   = nouv;    // Chainage de la nouvelle cellule avec le precedent
            
            // Empiler nouv dans la pile en lui otant 1 fils
            elt.cour = nouv;
            elt.nb_Fils_ou_Freres = nb_fouf - 1;

            empiler(p, &elt, &code);

            // Faire pointer pprec sur le lv de nouv 
            // Cela permettra de faire le chainage avec ses futurs fils
            pprec = &nouv->lv;

            // Recuperer le nombre de fils de nouv dans tabEltPref
            nb_fouf = tabEltPref[index].nbFils;

            // Incrementation de index
            index++;

        }else{  // Si nb_fouf = 0 ==> elt.cour est une feuille
            if (!estVidePile(p)) 
            {
                // Recuperer le sommet de la pile 
                elt = *(depiler(p, &code));

                // Faire pointer pprec vers le frere de elt.cour pour continuer le chainage
                pprec = &elt.cour->lh;

                // Actualiser le nombre de fils/freres
                nb_fouf = elt.nb_Fils_ou_Freres;
            }
        }
    }

    // Liberation de la pile
    libererPile(&p);

    return adrTete;
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
    // Initialisation de la pile
    pile_t * p            = initPile(NB_ELTPREF_MAX);

    int stop            = 0;
    int code;

    eltType_pile elt;

    // Cellule parcourant les elements a liberer
    cell_lvlh_t * elt_to_free;

    elt.cour = *adrPtRacine;


    if (*adrPtRacine)
    {
        while (!stop)
        {
            // Deplacement vertical pour le parcours en profondeur (freres puis fils)
            while (elt.cour->lv)
            {
                empiler(p, &elt, &code);
                elt.cour = elt.cour->lv; // Deplacement vertical
            }
            // Deplacement horizontal
            while (elt.cour->lh)
            {
                empiler(p, &elt, &code);
                elt.cour = elt.cour->lh;
            }
            
            // Element a libere = element courant
            elt_to_free = elt.cour;
            if (elt.cour->lv){ // Si il existe encore des fils, on continue le parcour 
                continue;
            }else if (!estVidePile(p)){ // Si la pile est NON vide

                    elt = *(depiler(p, &code)); // Depiler

                    // Mise a NULL de lh et lv du noeud courant
                    if (elt.cour->lh == elt_to_free)
                    {
                        elt.cour->lh = NULL;
                        
                    }else if(elt.cour->lv == elt_to_free)
                    {
                        elt.cour->lv = NULL;
                    }

                    // Liberation du noeud courant
                    free(elt_to_free);
            }else{

                stop = 1;
            }

        }
    }

    // Liberation du pointeur sur la premiere racine
    free(elt_to_free);

    // Liberation de la pile
    libererPile(&p);
}
