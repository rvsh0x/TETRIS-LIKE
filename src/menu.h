#ifndef _MENU_H_
#define _MENU_H_

#include "sauvegarde.h"
#include "jeu.h"
#include "affichage.h"


/* Fonction pour attendre une entrée clavier */
int attendre_entree(void);

/* Fonction pour lancer le menu principal */
int lancer_menu(void);

/* Fonction pour lancer le jeu */
int lancer_jeu(void);

/* Fonction pour afficher le menu de pause */
int menu_pause(Jeu *jeu);

int menu_sauvegarde(void);

int menu_mode(void);

int menu_chargement(void);

#endif /* _MENU_H_ */
