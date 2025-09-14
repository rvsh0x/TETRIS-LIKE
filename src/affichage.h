
#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#define TAILLE_CELLULE 30  /*Taille des cellules en pixels*/
#define DECALAGE_GRILLE_X 475  /*Coordonnée X de la grille sur l'image de fond*/
#define DECALAGE_GRILLE_Y 100  /*Coordonnée Y de la grille sur l'image de fond*/
#define LARGEUR_FENETRE 1280
#define HAUTEUR_FENETRE 720

#include "types.h"

/* Variables globales SDL */
extern SDL_Window* window;
extern SDL_Renderer* renderer;
#include "sauvegarde.h"
#include "menu.h"

void initialiser_affichage(void);
void nettoyer_affichage(void);
void afficher_image(char *nom_fichier);
void dessiner_texte(int x, int y, char *texte, int taille_police, SDL_Color couleur);
void afficher_accueil(void);
void afficher_menu(void);
void afficher_aide_1(void);
void afficher_aide_2(void);
void afficher_jeu(Jeu *jeu, Tetrimino *tetrimino, Tetrimino *tetrimino_suivant);
void afficher_records(void);
void superposer_image(char *nom_fichier);
void afficher_grille(void);
void afficher_records(void);
void afficher_pause(void);
void afficher_sauvegardes(void);
void afficher_defaite(int score, int record);
void afficher_player_mode(void);
void afficher_ecrase(void);
void afficher_jeu_a_deux(Jeu *jeu, Tetrimino *tetrimino_a, Tetrimino *tetrimino_b, Tetrimino *tetrimino_suivant_a, Tetrimino *tetrimino_suivant_b);
void invalider_cache_slots(void);
#endif /* _AFFICHAGE_H_ */
