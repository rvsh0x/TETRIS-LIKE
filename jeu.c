#ifndef _JEU_C_
#define _JEU_C_

#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"
#include <time.h>
#include "sauvegarde.h"
#include <SDL2/SDL.h>
#include "affichage.h"
#include "menu.h"


/* Fonction pour initialiser le temps */
void init_temps(Temps *temps) {
    temps->minutes = 0;
    temps->secondes = 0;
}

/* Fonction pour initialiser le jeu */
void init_jeu(Jeu *jeu) {
    int i, j;
    
    /* Initialiser la grille et les autres champs */
    for (i = 0; i < NB_LIGNES; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            jeu->grille[i][j] = 0;
        }
    }
    jeu->score = 0;
    jeu->est_finie = 0;
    jeu->en_pause = 0;
    init_temps(&jeu->debut_partie); /* Initialiser le temps de début de la partie */
}

/* Fonction pour initialiser les tétriminos */
void init_tab_tetri(TabTetri tab, SDL_Color couleurs[]) {
    int i, j;
    int i_forme[TAILLE][TAILLE] = {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    int o_forme[TAILLE][TAILLE] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };
    int t_forme[TAILLE][TAILLE] = {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    };
    int s_forme[TAILLE][TAILLE] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    };
    int z_forme[TAILLE][TAILLE] = {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };
    int j_forme[TAILLE][TAILLE] = {
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    };
    int l_forme[TAILLE][TAILLE] = {
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    };

    /* I */
    for (i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            tab[0].forme[i][j] = i_forme[i][j];
        }
    }
    couleurs[0].r = 0; couleurs[0].g = 255; couleurs[0].b = 255; couleurs[0].a = 255;

    /* O */
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            tab[1].forme[i][j] = o_forme[i][j];
        }
    }
    couleurs[1].r = 255; couleurs[1].g = 255; couleurs[1].b = 0; couleurs[1].a = 255;

    /* T */
    for (i=0 ; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            tab[2].forme[i][j] = t_forme[i][j];
        }
    }
    couleurs[2].r = 255; couleurs[2].g = 0; couleurs[2].b = 255; couleurs[2].a = 255;

    /* S */
    for (i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            tab[3].forme[i][j] = s_forme[i][j];
        }
    }
    couleurs[3].r = 0; couleurs[3].g = 255; couleurs[3].b = 0; couleurs[3].a = 255;

    /* Z */
    for (i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            tab[4].forme[i][j] = z_forme[i][j];
        }
    }
    couleurs[4].r = 255; couleurs[4].g = 0; couleurs[4].b = 0; couleurs[4].a = 255;

    /* J */
    for (i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            tab[5].forme[i][j] = j_forme[i][j];
        }
    }
    couleurs[5].r = 0; couleurs[5].g = 0; couleurs[5].b = 255; couleurs[5].a = 255;

    /* L */
    for (i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            tab[6].forme[i][j] = l_forme[i][j];
        }
    }
    couleurs[6].r = 255; couleurs[6].g = 165; couleurs[6].b = 0; couleurs[6].a = 255;
}

/* Fonction pour initialiser un tétrimino */
void init_tetrimino(Tetrimino *a, int type, TabTetri tab, SDL_Color couleurs[]) {
    int i, j;
    for (i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            a->forme[i][j] = tab[type].forme[i][j];
        }
    }
    /* Initialiser la position du tétrimino */
    a->x = NB_COLONNES / 2 - 2; /* 2 est la moitié de la taille du tétrimino */
    a->y = 0;
    a->couleur = couleurs[type]; /* Initialiser la couleur du tétrimino */
}

void init_tetrimino_a(Tetrimino *a, int type, TabTetri tab, SDL_Color couleurs[]) {
    int i, j;
    for (i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            a->forme[i][j] = tab[type].forme[i][j];
        }
    }
    /* Initialiser la position du tétrimino */
    a->x = 6; /* 2 est la moitié de la taille du tétrimino */
    a->y = 0;
    a->couleur = couleurs[type]; /* Initialiser la couleur du tétrimino */
}


void init_tetrimino_b(Tetrimino *a, int type, TabTetri tab, SDL_Color couleurs[]) {
    int i, j;
    for (i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            a->forme[i][j] = tab[type].forme[i][j];
        }
    }
    /* Initialiser la position du tétrimino */
    a->x = 1; 
    a->y = 0;
    a->couleur = couleurs[type]; /* Initialiser la couleur du tétrimino */
}

/* Fonction pour déplacer un tétrimino */
void deplacer_tetrimino(Tetrimino *a, int dx, int dy) {
    /* Déplacer le tétrimino en modifiant ses coordonnées */
    a->x += dx;
    a->y += dy;
}

/* Fonction pour pivoter un tétrimino */
void pivoter_tetrimino(Tetrimino *a, int sens) {
    int tmp[TAILLE][TAILLE]; /* tableau temporaire pour stocker les valeurs */
    int i, j;
    for (i=0; i<TAILLE; i++) {
        for (j = 0; j<TAILLE; j++) {
            if (sens == 1) { /* Sens horaire */
                tmp[j][TAILLE-1-i] = a->forme[i][j];
            } else { /* Sens inverse */
                tmp[TAILLE-1-j][i] = a->forme[i][j];
            }
        }
    }
    /* Copier les valeurs de tmp dans a->forme */
    for (i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            a->forme[i][j] = tmp[i][j];
        }
    }
}

/* Fonction pour vérifier les collisions */
int verifier_collision(Jeu *jeu, Tetrimino *a) {
    int i,j,new_x,new_y;
    for (i=0; i<TAILLE; i++) { /* Parcourir la forme du tétrimino */
        for (j=0; j<TAILLE; j++) {
            if (a->forme[i][j] != 0) { /* Si la case contient un bloc */
                new_x = a->x+j; /* Calculer les nouvelles coordonnées */
                new_y = a->y+i;
                if (new_x < 0 || new_x >= NB_COLONNES || new_y < 0 || new_y >= NB_LIGNES) {
                    return 1; /* Collision avec les bords de la grille */
                }
                if (jeu->grille[new_y][new_x] != 0) {
                    return 1; /* Collision avec une autre pièce */
                }
            }
        }
    }
    return 0; /* Pas de collision */
}

/* Fonction pour placer un tétrimino */
void placer_tetrimino(Jeu *jeu, Tetrimino *a) {
    int i, j, new_x, new_y;
    for (i=0; i<TAILLE; i++) { /* Parcourir la forme du tétrimino */
        for (j=0; j<TAILLE; j++) {
            if (a->forme[i][j] != 0) { /* Si la case contient un bloc */
                new_x = a->x+j; /* Calculer les nouvelles coordonnées */
                new_y = a->y+i;
                if (new_x >= 0 && new_x < NB_COLONNES && new_y >= 0 && new_y < NB_LIGNES) {
                    jeu->grille[new_y][new_x] = 1; /* Marquer la grille avec un bloc */
                }
            }
        }
    }
}

/* Fonction pour vérifier si une ligne est complète */
int verifier_ligne_complete(Jeu *jeu, int ligne) {
    int j;
    for (j=0; j<NB_COLONNES; j++) {
        if (jeu->grille[ligne][j] == 0) {
            return 0; /* La ligne n'est pas complète */
        }
    }
    return 1; /* La ligne est complète */
}

/* Fonction pour supprimer une ligne */
void supprimer_ligne(Jeu *jeu, int ligne) {
    int i,j;
    /* Supprimer la ligne en faisant descendre toutes les lignes au-dessus */
    for (i=ligne; i>0; i--) {
        for (j=0; j<NB_COLONNES; j++) {
            jeu->grille[i][j] = jeu->grille[i - 1][j];
        }
    }
    /* Vider la première ligne */
    for (j=0; j<NB_COLONNES; j++) {
        jeu->grille[0][j] = 0;
    }
}

/* Fonction pour gérer les lignes complètes */
void gerer_lignes_completes(Jeu *jeu) {
    int lignes_completes = 0;
    int i;
    for (i=0; i<NB_LIGNES; i++) {
        if (verifier_ligne_complete(jeu, i)) {
            supprimer_ligne(jeu, i);
            lignes_completes++;
        }
    }
    /* Mettre à jour le score en fonction du nombre de lignes complètes */
    calculer_score(jeu, lignes_completes);
}

/* Fonction pour calculer le score */
void calculer_score(Jeu *jeu, int lignes_completes) {
    jeu->score += lignes_completes * 10;
}

/* Fonction pour copier un tétrimino */
void copier_tetrimino(Tetrimino *tetri_a, Tetrimino *tetri_b) {
    int i,j;
    for (i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            tetri_b->forme[i][j] = tetri_a->forme[i][j];
        }
    }
    /* Initialiser la position du tétrimino */
    tetri_b->x = tetri_a->x;
    tetri_b->y = tetri_a->y;
}

/* Fonction pour mettre à jour le temps */
void mettre_a_jour_temps(Temps *temps) {
    temps->secondes++;
    if (temps->secondes >= 60) {
        temps->secondes = 0;
        temps->minutes++;
    }
}

int jouer(Jeu *jeu) {
    
    int quitter = 0;
    FILE *f;
    Tetrimino tetrimino;
    Tetrimino tetrimino_suivant;
    TabTetri tab_tetri;
    SDL_Color couleurs[7];
    int pause;
    Uint32 gravite_timer = 0;     /* Compte le temps écoulé pour la gravité */
    int vitesse_gravite = 400;    /* Temps (en ms) entre chaque descente automatique */
    int vitesse_descente = 10;    /* Temps (en ms) si le joueur appuie sur la flèche bas */
    int descente_rapide = 0;      /* Indique si le joueur activate la descente rapide */
    Uint32 temps_timer = 0;       /* Compte le temps écoulé pour le timer */
    int perdu = 0;
    int record;
    char record_txt[12];
    SDL_Event event;
    
    while (!quitter){

        init_tab_tetri(tab_tetri, couleurs);
        init_tetrimino(&tetrimino, rand() % 7, tab_tetri, couleurs);
        init_tetrimino(&tetrimino_suivant, rand() % 7, tab_tetri, couleurs);
    

        while (!jeu->est_finie){
        /* Gestion de la gravité */
        if (SDL_GetTicks() - gravite_timer >= (Uint32)(descente_rapide ? vitesse_descente : vitesse_gravite)) {
            gravite_timer = SDL_GetTicks();
            deplacer_tetrimino(&tetrimino, 0, 1);
            if (verifier_collision( jeu, &tetrimino)) {
                deplacer_tetrimino(&tetrimino, 0, -1);
                placer_tetrimino(jeu, &tetrimino);
                gerer_lignes_completes(jeu);
                jeu->score++;
                copier_tetrimino(&tetrimino_suivant, &tetrimino);
                init_tetrimino(&tetrimino_suivant, rand() % 7, tab_tetri, couleurs);
                if (verifier_collision(jeu, &tetrimino)) {
                    perdu = 1;
                    jeu->est_finie = 1;
                }
            }
        }

        /* Mettre à jour le timer toutes les secondes */
        if (SDL_GetTicks() - temps_timer >= 1000) {
            temps_timer = SDL_GetTicks();
            mettre_a_jour_temps(&jeu->debut_partie);
        }

        /* Gestion des événements clavier */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        deplacer_tetrimino(&tetrimino, -1, 0);
                        if (verifier_collision(jeu, &tetrimino)) {
                            deplacer_tetrimino(&tetrimino, 1, 0);
                        }
                        break;
                    case SDLK_RIGHT:
                        deplacer_tetrimino(&tetrimino, 1, 0);
                        if (verifier_collision(jeu, &tetrimino)) {
                            deplacer_tetrimino(&tetrimino, -1, 0);
                        }
                        break;
                    case SDLK_DOWN:
                        descente_rapide = 1;
                        break;
                    case SDLK_q:
                        pivoter_tetrimino(&tetrimino, -1);
                        if (verifier_collision(jeu, &tetrimino)) {
                            pivoter_tetrimino(&tetrimino, 1);
                        }
                        break;
                    case SDLK_d:
                        pivoter_tetrimino(&tetrimino, 1);
                        if (verifier_collision(jeu, &tetrimino)) {
                            pivoter_tetrimino(&tetrimino, -1);
                        }
                        break;
                    case SDLK_ESCAPE:
                        jeu->en_pause = 1;
                        pause = menu_pause(jeu);
                        if (pause == 0) {
                            jeu->est_finie = 1;
                            return 0;
                        }
                        if (pause == 2) {
                            jeu->est_finie = 1;
                        }
                        break;
                    default:
                        break;
                }
            } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
                /* Arrêter la descente rapide quand la touche bas est relâchée */
                descente_rapide = 0;
            }
        }

        /* Ajout d'un petit délai pour limiter l'usage CPU */
        afficher_jeu(jeu, &tetrimino, &tetrimino_suivant);
        SDL_Delay(20);
    }

    sauvegarder_score(jeu, "data/scores.txt");
                    
    if(perdu){

        f = fopen("data/scores.txt", "r");
        if (f == NULL) {
            perror("Erreur lors de l'ouverture du fichier");
            return -1;
        }

        fscanf(f, "%d", &record);
        fclose(f);

        sprintf(record_txt, "%d", record);

        afficher_defaite(jeu->score, record);
        attendre_entree();
    }
    /* Affichage de Game Over*/

    
    return 1;
    }
    return 1;
}




int jouer_a_deux(Jeu *jeu) {
    FILE *f;
    int quitter = 0;

    Tetrimino tetrimino_a;
    Tetrimino tetrimino_suivant_a;
    Tetrimino tetrimino_b;
    Tetrimino tetrimino_suivant_b;
    TabTetri tab_tetri;
    SDL_Color couleurs[7];
    int pause;
    Uint32 gravite_timer = 0;     /* Compte le temps écoulé pour la gravité */
    int vitesse_gravite = 400;    /* Temps (en ms) entre chaque descente automatique */
    int vitesse_descente = 10;    /* Temps (en ms) si le joueur appuie sur la flèche bas */
    int descente_rapide = 0;      /* Indique si le joueur active la descente rapide */
    Uint32 temps_timer = 0;       /* Compte le temps écoulé pour le timer */
    int perdu = 0;
    int record;
    char record_txt[12];
    SDL_Event event;
    
    while (!quitter){

        init_tab_tetri(tab_tetri, couleurs);
        init_tetrimino_a(&tetrimino_a, rand() % 7, tab_tetri, couleurs);
        init_tetrimino_b(&tetrimino_b, rand() % 7, tab_tetri, couleurs);
        init_tetrimino_a(&tetrimino_suivant_a, rand() % 7, tab_tetri, couleurs);
        init_tetrimino_b(&tetrimino_suivant_b, rand() % 7, tab_tetri, couleurs);
    

        while (!jeu->est_finie){
        /* Gestion de la gravité */
        if (SDL_GetTicks() - gravite_timer >= (Uint32)(descente_rapide ? vitesse_descente : vitesse_gravite)) {
            gravite_timer = SDL_GetTicks();
            deplacer_tetrimino(&tetrimino_a, 0, 1);
            deplacer_tetrimino(&tetrimino_b, 0, 1);
            if (verifier_collision( jeu, &tetrimino_a)) {
                deplacer_tetrimino(&tetrimino_a, 0, -1);
                placer_tetrimino(jeu, &tetrimino_a);
                gerer_lignes_completes(jeu);
                jeu->score++;
                copier_tetrimino(&tetrimino_suivant_a, &tetrimino_a);
                init_tetrimino(&tetrimino_suivant_a, rand() % 7, tab_tetri, couleurs);
                if (verifier_collision(jeu, &tetrimino_a)) {
                    perdu = 1;
                    jeu->est_finie = 1;
                }
            }

            if (verifier_collision( jeu, &tetrimino_b)) {
                deplacer_tetrimino(&tetrimino_b, 0, -1);
                placer_tetrimino(jeu, &tetrimino_b);
                gerer_lignes_completes(jeu);
                jeu->score++;
                copier_tetrimino(&tetrimino_suivant_b, &tetrimino_b);
                init_tetrimino(&tetrimino_suivant_b, rand() % 7, tab_tetri, couleurs);
                if (verifier_collision(jeu, &tetrimino_b)) {
                    perdu = 1;
                    jeu->est_finie = 1;
                }
            }

        }

        /* Mettre à jour le timer toutes les secondes */
        if (SDL_GetTicks() - temps_timer >= 1000) {
            temps_timer = SDL_GetTicks();
            mettre_a_jour_temps(&jeu->debut_partie);
        }

        /* Gestion des événements clavier */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        deplacer_tetrimino(&tetrimino_a, -1, 0);
                        if (verifier_collision(jeu, &tetrimino_a)) {
                            deplacer_tetrimino(&tetrimino_a, 1, 0);
                        }
                        break;
                    case SDLK_RIGHT:
                        deplacer_tetrimino(&tetrimino_a, 1, 0);
                        if (verifier_collision(jeu, &tetrimino_a)) {
                            deplacer_tetrimino(&tetrimino_a, -1, 0);
                        }
                        break;
                    case SDLK_DOWN:
                        descente_rapide = 1;
                        break;
                    case SDLK_k:
                        pivoter_tetrimino(&tetrimino_a, -1);
                        if (verifier_collision(jeu, &tetrimino_a)) {
                            pivoter_tetrimino(&tetrimino_a, 1);
                        }
                        break;
                    case SDLK_m:
                        pivoter_tetrimino(&tetrimino_a, 1);
                        if (verifier_collision(jeu, &tetrimino_a)) {
                            pivoter_tetrimino(&tetrimino_a, -1);
                        }
                        break;
                    case SDLK_q:
                        deplacer_tetrimino(&tetrimino_b, -1, 0);
                        if (verifier_collision(jeu, &tetrimino_b)) {
                            deplacer_tetrimino(&tetrimino_b, 1, 0);
                        }
                        break;
                    case SDLK_d:
                        deplacer_tetrimino(&tetrimino_b, 1, 0);
                        if (verifier_collision(jeu, &tetrimino_b)) {
                            deplacer_tetrimino(&tetrimino_b, -1, 0);
                        }
                        break;
                    case SDLK_s:
                        descente_rapide = 1;
                        break;
                    case SDLK_a:
                        pivoter_tetrimino(&tetrimino_b, -1);
                        if (verifier_collision(jeu, &tetrimino_b)) {
                            pivoter_tetrimino(&tetrimino_b, 1);
                        }
                        break;
                    case SDLK_e:
                        pivoter_tetrimino(&tetrimino_b, 1);
                        if (verifier_collision(jeu, &tetrimino_b)) {
                            pivoter_tetrimino(&tetrimino_b, -1);
                        }
                        break;
                    case SDLK_ESCAPE:
                        jeu->en_pause = 1;
                        pause = menu_pause(jeu);
                        if (pause == 0) {
                            jeu->est_finie = 1;
                            return 0;
                        }
                        if (pause == 2) {
                            jeu->est_finie = 1;
                        }
                        break;
                    default:
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
                    /* Arrêter la descente rapide quand les touches de descente sont relâchées */
                    descente_rapide = 0;
                }
            }
        }

        /* Ajout d'un petit délai pour limiter l'usage CPU */
        afficher_jeu_a_deux(jeu, &tetrimino_a, &tetrimino_b, &tetrimino_suivant_a, &tetrimino_suivant_b);
        SDL_Delay(20);
    }

    sauvegarder_score(jeu, "data/scores.txt");
                    
    if(perdu){

        f = fopen("data/scores.txt", "r");
        if (f == NULL) {
            perror("Erreur lors de l'ouverture du fichier");
            return -1;
        }

        fscanf(f, "%d", &record);
        fclose(f);

        sprintf(record_txt, "%d", record);

        afficher_defaite(jeu->score, record);
        attendre_entree();
    }
    /* Affichage de Game Over*/

    
    return 1;
    }
    return 1;
}

#endif /* _JEU_C_ */
