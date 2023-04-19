/**
 * @file eltArbre.h
 * @brief fichier d'entete pour les types de donnees d'une arborescence
 */
#ifndef __ELTSARBRE_H__
#define __ELTSARBRE_H__

/** TO DO
 * @def NB_ELTPREF_MAX
 * @brief definir le nombre d'elements (couple valeur-nombre_de_fils) maximum 
 *        dans une representation prefixee ou postfixee
 */
#define NB_ELTPREF_MAX 50

/** TO DO
 * @struct eltPrefPostFixee_t
 * @brief definir la SDD pour les elements de la representation prefixee ou postfixee
 * 2 champs :
 *   - val : la valeur d'un element de type char
 *   - nbFils : le nombre de fils d'un element
 */

typedef struct eltPrefPostFixee_t
{
    char val;
    int nbFils;
    
} eltPrefPostFixee_t;

/** TO DO
 * @struct cell_lvlh_t
 * @brief Definir la structure des points/cellules pour la representation d'une arborescence en lv et lh
 * 3 champs :
 *   - val : la valeur du point de l'arborescence de type char
 *   - lv : pointeur pour le lien vertical
 *   - lh : pointeur pour le lien horizontal
 */

typedef struct cell_lvlh_t
{
    char val;
    struct cell_lvlh_t * lv;
    struct cell_lvlh_t * lh;

} cell_lvlh_t;


#endif