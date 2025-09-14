#ifndef _JEU_H_
#define _JEU_H_

#include "types.h"

/* Déclarations des fonctions */
void charger_scores(Jeu *jeu);
void init_temps(Temps *temps); /* Initialiser le temps */
void init_jeu(Jeu *jeu);
void init_tab_tetri(TabTetri tab, SDL_Color couleurs[]);
void init_tetrimino(Tetrimino *a, int type, TabTetri tab, SDL_Color couleurs[]);
void deplacer_tetrimino(Tetrimino *a, int dx, int dy);
void pivoter_tetrimino(Tetrimino *a, int sens);
int verifier_collision(Jeu *jeu, Tetrimino *a);
void placer_tetrimino(Jeu *jeu, Tetrimino *a);
int verifier_ligne_complete(Jeu *jeu, int ligne);
void gerer_lignes_completes(Jeu *jeu);
void supprimer_ligne(Jeu *jeu, int ligne);
void calculer_score(Jeu *jeu, int lignes_completes);
void copier_tetrimino(Tetrimino *tetri_a, Tetrimino *tetri_b);
void mettre_a_jour_temps(Temps *temps); /* Mettre à jour le temps */
int jouer(Jeu *jeu);

void init_jeu_a_deux(Jeu *jeu);
int jouer_a_deux(Jeu *jeu);
int verifier_collision_tetri(Tetrimino *a, Tetrimino *b);



#endif /* _JEU_H_ */
