#ifndef _SAUVEGARDE_H_
#define _SAUVEGARDE_H_

#include "types.h"
#include "menu.h"

/* Fonction pour sauvegarder une partie */
void sauvegarder_partie(Jeu *jeu);

/* Fonction pour trier les scores */
void trier_scores(char *fichier);

/* Fonction pour sauvegarder un score */
void sauvegarder_score(Jeu *jeu, char *chemin);

/* Fonction pour effectuer la sauvegarde finale */
int sauvegarde_finale(char *chemin_sauvegarde_temp, char *chemin_sauvegarde_def);

/* Fonction pour charger une partie */
int charger_partie(Jeu *jeu);

/* Fonction pour charger une partie depuis un slot */
int charger_jeu(void);

void affecter_scores(int *tab);

int slot_est_vide(int slot);

/* Fonction pour initialiser les slots de sauvegarde */
void initialiser_slots_sauvegarde(void);

#endif /* _SAUVEGARDE_H_ */
