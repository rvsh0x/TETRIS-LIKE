#ifndef _TYPES_H_
#define _TYPES_H_

#define NB_LIGNES 20
#define NB_COLONNES 11
#define TAILLE 4
#define N 7

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    int minutes;
    int secondes;
} Temps;

typedef struct {
    int grille[NB_LIGNES][NB_COLONNES];
    int score;
    int est_finie; /* Indicateur de fin de partie */
    int en_pause; /* Indicateur de pause */
    Temps debut_partie; /* Temps de début de la partie */
} Jeu;

typedef struct {
    int forme[TAILLE][TAILLE]; /* Forme du tétrimino */
    int x; 
    int y; 
    SDL_Color couleur; /* Couleur du tétrimino */
} Tetrimino;

typedef Tetrimino TabTetri[N]; /* Tableau de tétriminos */

#endif /*_TYPES_H_*/
