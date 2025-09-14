#ifndef _SAUVEGARDE_C_
#define _SAUVEGARDE_C_
#include "sauvegarde.h"
#include <stdio.h>

/* VERSION DE SAUVEGARDE NON BINAIRE

void sauvegarder_partie(Jeu *jeu) {
    FILE *fichier;
    char chemin[50];
    int i, j;

    int slot = menu_sauvegarde();

     Construire le chemin du fichier de sauvegarde 
    sprintf(chemin, "data/slot_%d.txt", slot);
    
    fichier = fopen(chemin, "w");
    if (fichier == NULL) {
        printf("Erreur dans l'ouverture du fichier\n");
        return; 
    }
    for (i = 0; i < NB_LIGNES; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            fprintf(fichier, "%d ", jeu->grille[i][j]);
        }
        fprintf(fichier, "\n");
    }
    fprintf(fichier, "%d\n", jeu->score);
    fprintf(fichier, "%d\n", jeu->est_finie);
    fprintf(fichier, "%d\n", jeu->en_pause);
    fprintf(fichier, "%02d:%02d\n", jeu->debut_partie.minutes, jeu->debut_partie.secondes);

    fprintf(fichier, "\n");
    fclose(fichier);
}

* Fonction pour charger une partie 
int charger_partie(Jeu *jeu) {
    FILE *fichier;
    char chemin[50];
    int i, j;

    int slot = menu_sauvegarde();

    if(!slot_est_vide(slot)){
    Construire le chemin du fichier de sauvegarde 
    sprintf(chemin, "data/slot_%d.txt", slot);
    printf("Chemin du fichier: %s\n", chemin); 

    fichier = fopen(chemin, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de chargement\n");
        return; 
    }
    for (i = 0; i < NB_LIGNES; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            fscanf(fichier, "%d", &jeu->grille[i][j]);
        }
    }
    fscanf(fichier, "%d", &jeu->score);
    fscanf(fichier, "%d", &jeu->est_finie);
    fscanf(fichier, "%d", &jeu->en_pause);
    fscanf(fichier, "%02d:%02d", &jeu->debut_partie.minutes, &jeu->debut_partie.secondes);
    
    fclose(fichier);
    return 1;
    } 

    return 0;
}
*/

void sauvegarder_partie(Jeu *jeu) {
    FILE *fichier;
    char chemin[50];
    int i, j;

    int slot = menu_sauvegarde();


    sprintf(chemin, "data/slot_%d.bin", slot);
    
    fichier = fopen(chemin, "wb");
    if (fichier == NULL) {
        printf("Erreur dans l'ouverture du fichier\n");
        return; 
    }

    for (i = 0; i < NB_LIGNES; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            fwrite(&jeu->grille[i][j], sizeof(int), 1, fichier);
        }
    }
    fwrite(&jeu->score, sizeof(int), 1, fichier);
    fwrite(&jeu->est_finie, sizeof(int), 1, fichier);
    fwrite(&jeu->en_pause, sizeof(int), 1, fichier);
    fwrite(&jeu->debut_partie.minutes, sizeof(int), 1, fichier);
    fwrite(&jeu->debut_partie.secondes, sizeof(int), 1, fichier);

    fclose(fichier);
    
    /* Invalider le cache des slots après sauvegarde */
    invalider_cache_slots();
}

int charger_partie(Jeu *jeu) {
    FILE *fichier;
    char chemin[50];
    int i, j;

    int slot = menu_chargement();

    /* Si l'utilisateur a annulé la sélection */
    if (slot == 0) {
        return 0;
    }

    if(!slot_est_vide(slot)){
        sprintf(chemin, "data/slot_%d.bin", slot);
       
        fichier = fopen(chemin, "rb");
        if (fichier == NULL) {
            printf("Erreur lors de l'ouverture du fichier de chargement\n");
            return 0; 
        }

        /* Charger les données du jeu */
        for (i = 0; i < NB_LIGNES; i++) {
            for (j = 0; j < NB_COLONNES; j++) {
                if (fread(&jeu->grille[i][j], sizeof(int), 1, fichier) != 1) {
                    printf("Erreur de lecture du fichier\n");
                    fclose(fichier);
                    return 0;
                }
            }
        }
        
        if (fread(&jeu->score, sizeof(int), 1, fichier) != 1 ||
            fread(&jeu->est_finie, sizeof(int), 1, fichier) != 1 ||
            fread(&jeu->en_pause, sizeof(int), 1, fichier) != 1 ||
            fread(&jeu->debut_partie.minutes, sizeof(int), 1, fichier) != 1 ||
            fread(&jeu->debut_partie.secondes, sizeof(int), 1, fichier) != 1) {
            printf("Erreur de lecture du fichier\n");
            fclose(fichier);
            return 0;
        }

        fclose(fichier);
        
        /* S'assurer que le jeu chargé est dans un état jouable */
        jeu->est_finie = 0;  /* Le jeu reprend, donc pas fini */
        jeu->en_pause = 0;   /* Le jeu reprend, donc pas en pause */
        
        return 1;
    } else {
        printf("Le slot sélectionné est vide\n");
        return 0;
    }

    return 0;
}


/* Fonction pour trier les scores */
void trier_scores(char *fichier) {
    FILE *f;
    int scores[100];  /* Supposons qu'il y ait au maximum 100 scores dans le fichier */
    int count = 0;
    int i, j, temp, unique_count;

    f = fopen(fichier, "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    /* Lecture des scores dans le tableau */
    while (fscanf(f, "%d", &scores[count]) == 1) {
        count++;
    }
    fclose(f);

    /* Tri des scores en ordre décroissant avec un tri à bulles */
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {
                temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }

    /* Suppression des doublons */
    unique_count = 0;
    for (i = 0; i < count; i++) {
        if (i == 0 || scores[i] != scores[i - 1]) {
            scores[unique_count++] = scores[i];
        }
    }

    /* Réouverture du fichier en mode écriture pour remplacer le contenu */
    f = fopen(fichier, "w");
    if (f == NULL) {
        printf("Erreur lors de la réouverture du fichier\n");
        return;
    }

    /* Écriture des scores triés et sans doublons dans le fichier */
    for (i = 0; i < unique_count; i++) {
        fprintf(f, "%d\n", scores[i]);
    }

    fclose(f);
}


/* Fonction pour sauvegarder un score */
void sauvegarder_score(Jeu *jeu, char *chemin) {
    FILE *fichier;
    
    fichier = fopen(chemin, "a");
    if (fichier == NULL) {
        printf("Erreur dans l'ouverture du fichier\n");
        return; 
    }
    fprintf(fichier, "%d\n", jeu->score);
    fclose(fichier);
    trier_scores(chemin);
}

/* version non binaire
int slot_est_vide(int slot) {
    

    char chemin[50];

    sprintf(chemin, "data/slot_%d.txt", slot);

    FILE *fichier = fopen(chemin, "r");
    if (fichier == NULL) {
        return -1;
    }

    fseek(fichier, 0, SEEK_END);
    long taille = ftell(fichier);
    fclose(fichier);

    if (taille == 0) {
        return 1;
    } else {
        return 0;
    }
}
*/

void initialiser_slots_sauvegarde(void) {
    int i;
    char chemin[50];
    FILE *fichier;
    
    /* Créer les fichiers de slot vides s'ils n'existent pas */
    for (i = 1; i <= 5; i++) {
        sprintf(chemin, "data/slot_%d.bin", i);
        fichier = fopen(chemin, "r");
        if (fichier == NULL) {
            /* Le fichier n'existe pas, le créer vide */
            fichier = fopen(chemin, "w");
            if (fichier != NULL) {
                fclose(fichier);
            }
        } else {
            fclose(fichier);
        }
    }
}

int slot_est_vide(int slot) {
    char chemin[50];
    FILE *fichier;
    long taille;

    /* Construire le chemin du fichier de sauvegarde */
    sprintf(chemin, "data/slot_%d.bin", slot);

    /* Ouvrir le fichier en mode binaire */
    fichier = fopen(chemin, "rb");
    if (fichier == NULL) {
        return 1; /* Si le fichier n'existe pas, considérer le slot comme vide */
    }

    /* Se déplacer à la fin du fichier pour obtenir sa taille */
    fseek(fichier, 0, SEEK_END);
    taille = ftell(fichier);
    fclose(fichier);

    /* Vérifier si le fichier est vide */
    if (taille == 0) {
        return 1;
    } else {
        return 0;
    }
}


/* Fonction pour charger une partie depuis un slot */
int charger_jeu(void) {
    Jeu jeu;
    int slot;

    /* Demander à l'utilisateur de choisir un slot de sauvegarde */
    printf("Entrez le numéro du slot de sauvegarde (1-5) : ");
    if(scanf("%d", &slot) != 1 || slot < 1 || slot > 5) {
        printf("Erreur: Entrez un numéro de slot valide (1-5)\n");
        return 1;
    }

    /* Charger la partie depuis le fichier de sauvegarde */
    charger_partie(&jeu);

    /* Lancer le jeu avec la partie chargée */
    return jouer(&jeu);
}



#endif /* _SAUVEGARDE_C */
