#ifndef _AFFICHAGE_C
#define _AFFICHAGE_C
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "affichage.h"

#define TAILLE_TETRIMINO 30

/* Variables globales SDL */
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

/* Cache pour les statuts des slots de sauvegarde */
static int slots_status[6] = {-1, -1, -1, -1, -1, -1};
static int cache_slots_valide = 0;

void initialiser_affichage(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur SDL_Init: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Erreur IMG_Init: %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "Erreur TTF_Init: %s\n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                              LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Erreur création fenêtre: %s\n", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Erreur création renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void nettoyer_affichage(void) {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void afficher_image(char *nom_fichier) {
    SDL_Surface* surface;
    SDL_Texture* texture;
    
    surface = IMG_Load(nom_fichier);
    if (!surface) {
        fprintf(stderr, "Erreur chargement image %s: %s\n", nom_fichier, IMG_GetError());
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    if (!texture) {
        fprintf(stderr, "Erreur création texture: %s\n", SDL_GetError());
        return;
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}

void afficher_accueil(void) {
    afficher_image("img/Tetris_Home.png");
}

void afficher_menu(void) {
    afficher_image("img/Tetris_Menu.png");
}

void afficher_aide_1(void) {
    afficher_image("img/Tetris_Help1.png");
}

void afficher_aide_2(void) {
    afficher_image("img/Tetris_Help2.png");
}

void afficher_ecrase(void) {
    afficher_image("img/Tetris_Ecrase.png");
}

void afficher_pause(void) {
    afficher_image("img/Tetris_Pause.png");
}

void afficher_player_mode(void) {
    afficher_image("img/Tetris_player.png");
}

SDL_Color mlv_to_sdl_color(int mlv_color) {
    SDL_Color color = {0, 0, 0, 255};
    
    /* Mapping des couleurs MLV vers SDL */
    switch(mlv_color) {
        case 0xFF0000FF: /* MLV_COLOR_RED */
            color.r = 255; color.g = 0; color.b = 0;
            break;
        case 0x00FF00FF: /* MLV_COLOR_GREEN */
            color.r = 0; color.g = 255; color.b = 0;
            break;
        case 0x0000FFFF: /* MLV_COLOR_BLUE */
            color.r = 0; color.g = 0; color.b = 255;
            break;
        case 0xFFFF00FF: /* MLV_COLOR_YELLOW */
            color.r = 255; color.g = 255; color.b = 0;
            break;
        case 0x00FFFFFF: /* MLV_COLOR_CYAN */
            color.r = 0; color.g = 255; color.b = 255;
            break;
        case 0xFF00FFFF: /* MLV_COLOR_PURPLE */
            color.r = 255; color.g = 0; color.b = 255;
            break;
        case 0xFFA500FF: /* MLV_COLOR_ORANGE */
            color.r = 255; color.g = 165; color.b = 0;
            break;
        case 0x000000FF: /* MLV_COLOR_BLACK */
            color.r = 0; color.g = 0; color.b = 0;
            break;
        case 0xFFFFFFFF: /* MLV_COLOR_WHITE */
            color.r = 255; color.g = 255; color.b = 255;
            break;
        case 0x808080FF: /* MLV_COLOR_GRAY */
            color.r = 128; color.g = 128; color.b = 128;
            break;
        default:
            color.r = 255; color.g = 255; color.b = 255;
            break;
    }
    return color;
}

void dessiner_texte(int x, int y, char *texte, int taille_police, SDL_Color couleur) {
    TTF_Font* font;
    SDL_Surface* surface_texte;
    SDL_Texture* texture_texte;
    SDL_Rect dest_rect;
    
    /* Essayer de charger la police */
    font = TTF_OpenFont("data/avenir-next-heavy.ttf", taille_police);
    if (!font) {
        /* Si la police personnalisée ne fonctionne pas, utiliser une police système */
        font = TTF_OpenFont("/System/Library/Fonts/Arial.ttf", taille_police);
        if (!font) {
            fprintf(stderr, "Erreur: Aucune police disponible: %s\n", TTF_GetError());
            return;
        }
    }

    surface_texte = TTF_RenderText_Solid(font, texte, couleur);
    if (!surface_texte) {
        fprintf(stderr, "Erreur rendu texte '%s': %s\n", texte, TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    texture_texte = SDL_CreateTextureFromSurface(renderer, surface_texte);
    if (!texture_texte) {
        fprintf(stderr, "Erreur création texture texte: %s\n", SDL_GetError());
        SDL_FreeSurface(surface_texte);
        TTF_CloseFont(font);
        return;
    }

    dest_rect.x = x;
    dest_rect.y = y;
    dest_rect.w = surface_texte->w;
    dest_rect.h = surface_texte->h;

    SDL_RenderCopy(renderer, texture_texte, NULL, &dest_rect);

    SDL_DestroyTexture(texture_texte);
    SDL_FreeSurface(surface_texte);
    TTF_CloseFont(font);
}

void afficher_sauvegardes(void) {
    int i;
    SDL_Color couleur_noir = {0, 0, 0, 255};
    SDL_Surface* surface;
    SDL_Texture* texture;
    
    /* Vérifier les statuts seulement si le cache n'est pas valide */
    if (!cache_slots_valide) {
        for(i = 1; i < 6; i++) {
            slots_status[i] = slot_est_vide(i);
        }
        cache_slots_valide = 1;
    }
    
    /* Afficher l'image de fond */
    surface = IMG_Load("img/Tetris_Save.png");
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (texture) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            
            /* Afficher les textes par-dessus */
            for(i = 1; i < 6; i++) {
                if(slots_status[i]) {
                    dessiner_texte(140 + 230*(i-1), 473, "FREE", 26, couleur_noir);
                } else {
                    dessiner_texte(140 + 230*(i-1), 473, "USED", 26, couleur_noir);
                }
            }
            
            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture);
        }
    }
}

void afficher_records(void) {
    int i;
    int scores[10];
    char score_txt[10][12];
    SDL_Color couleur_noir = {0, 0, 0, 255};
    FILE *f;
    SDL_Rect rect;
    int text_x, text_y;
    SDL_Surface* surface;
    SDL_Texture* texture;

    /* Initialiser tous les scores à 0 */
    for (i = 0; i < 10; i++) {
        scores[i] = 0;
    }

    f = fopen("data/scores.txt", "r");
    if (f == NULL) {
        /* Fichier non trouvé, continuer avec des scores à 0 */
    } else {
        for (i = 0; i < 10; i++) {
            if (fscanf(f, "%d", &scores[i]) != 1) {
                break;
            }
        }
        fclose(f);
    }

    /* Afficher l'image de fond */
    surface = IMG_Load("img/Tetris_Record.png");
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (texture) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            
            /* Afficher les scores par-dessus l'image de fond */
            for (i = 0; i < 10; i++) {
                sprintf(score_txt[i], "%d", scores[i]);
                
                /* Dessiner un rectangle blanc comme fond pour les scores */
                rect.x = 550;
                rect.y = 150 + i * 50;
                rect.w = 200;
                rect.h = 50;
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
                
                /* Centrer le texte dans le rectangle */
                text_x = 620; /* Centré dans le rectangle de 200px de large */
                text_y = 160 + i * 50;
                dessiner_texte(text_x, text_y, score_txt[i], 32, couleur_noir);
            }
            
            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture);
        }
    } else {
        fprintf(stderr, "Erreur chargement image records: %s\n", IMG_GetError());
        /* Affichage de secours sans image de fond */
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);
        
        for (i = 0; i < 10; i++) {
            sprintf(score_txt[i], "%d", scores[i]);
            text_x = 620;
            text_y = 160 + i * 50;
            dessiner_texte(text_x, text_y, score_txt[i], 32, couleur_noir);
        }
        
        SDL_RenderPresent(renderer);
    }
    
    /* Attendre une entrée utilisateur pour revenir au menu */
    attendre_entree();
}

void afficher_defaite(int score, int record) {
    char record_txt[50];
    char score_txt[50];
    SDL_Color couleur_noir = {0, 0, 0, 255};
    SDL_Surface* surface;
    SDL_Texture* texture;

    sprintf(score_txt, "%d", score);
    sprintf(record_txt, "%d", record);
    
    /* Afficher l'image de fond de défaite */
    surface = IMG_Load("img/Tetris_Lose.png");
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (texture) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_DestroyTexture(texture);
        }
    }

    /* Afficher le score et le record */
    dessiner_texte(610, 300, score_txt, 34, couleur_noir);
    dessiner_texte(580, 420, record_txt, 34, couleur_noir);

    SDL_RenderPresent(renderer);
}

void afficher_grille(void) {
    int i, j;
    int x, y;
    SDL_Rect rect;
    
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); /* Couleur grise */
    
    /* Dessin des cellules de la grille */
    for (i = 0; i < NB_LIGNES; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            x = DECALAGE_GRILLE_X + j * TAILLE_CELLULE;
            y = DECALAGE_GRILLE_Y + i * TAILLE_CELLULE;

            rect.x = x;
            rect.y = y;
            rect.w = TAILLE_CELLULE;
            rect.h = TAILLE_CELLULE;
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void afficher_jeu(Jeu *jeu, Tetrimino *tetrimino, Tetrimino *tetrimino_suivant) {
    int i, j;
    char texte_score[50];
    char texte_timer[50];
    char record_txt[50];
    int x, y;
    int record;
    SDL_Color couleur_noir = {0, 0, 0, 255};
    FILE *f;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;

    f = fopen("data/scores.txt", "r");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    fscanf(f, "%d", &record);
    fclose(f);

    sprintf(texte_score, "%d", jeu->score);
    sprintf(record_txt, "%d", record);
    sprintf(texte_timer, "%02d:%02d", jeu->debut_partie.minutes, jeu->debut_partie.secondes);

    /* Afficher l'image de fond */
    surface = IMG_Load("img/Tetris_Game.png");
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (texture) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_DestroyTexture(texture);
        }
    }

    /* Afficher les textes */
    dessiner_texte(945, 190, texte_score, 26, couleur_noir);
    dessiner_texte(925, 160, texte_timer, 26, couleur_noir);
    dessiner_texte(1000, 222, record_txt, 26, couleur_noir);

    /* Afficher les blocs placés */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (i = 0; i < NB_LIGNES; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            if (jeu->grille[i][j] != 0) {
                rect.x = DECALAGE_GRILLE_X + j * TAILLE_CELLULE;
                rect.y = DECALAGE_GRILLE_Y + i * TAILLE_CELLULE;
                rect.w = TAILLE_CELLULE;
                rect.h = TAILLE_CELLULE;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    /* Afficher le tétrimino actuel */
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); /* Rouge */
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            if (tetrimino->forme[i][j] != 0) {
                x = DECALAGE_GRILLE_X + (tetrimino->x + j) * TAILLE_CELLULE;
                y = DECALAGE_GRILLE_Y + (tetrimino->y + i) * TAILLE_CELLULE;
                rect.x = x; rect.y = y; rect.w = TAILLE_CELLULE; rect.h = TAILLE_CELLULE;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    /* Afficher le tétrimino suivant */
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            if (tetrimino_suivant->forme[i][j] != 0) {
                x = 50 + (tetrimino_suivant->x + j) * TAILLE_CELLULE;
                y = 200 + (tetrimino_suivant->y + i) * TAILLE_CELLULE;
                rect.x = x; rect.y = y; rect.w = TAILLE_CELLULE; rect.h = TAILLE_CELLULE;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    afficher_grille();
    SDL_RenderPresent(renderer);
}

void afficher_jeu_a_deux(Jeu *jeu, Tetrimino *tetrimino_a, Tetrimino *tetrimino_b, Tetrimino *tetrimino_suivant_a, Tetrimino *tetrimino_suivant_b) {
    int i, j;
    char texte_score[50];
    char texte_timer[50];
    char record_txt[50];
    int x, y;
    int record;
    SDL_Color couleur_noir = {0, 0, 0, 255};
    FILE *f;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;

    f = fopen("data/scores.txt", "r");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    fscanf(f, "%d", &record);
    fclose(f);

    sprintf(texte_score, "%d", jeu->score);
    sprintf(record_txt, "%d", record);
    sprintf(texte_timer, "%02d:%02d", jeu->debut_partie.minutes, jeu->debut_partie.secondes);

    /* Afficher l'image de fond */
    surface = IMG_Load("img/Tetris_Game.png");
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (texture) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_DestroyTexture(texture);
        }
    }

    /* Afficher les textes */
    dessiner_texte(945, 190, texte_score, 26, couleur_noir);
    dessiner_texte(925, 160, texte_timer, 26, couleur_noir);
    dessiner_texte(1000, 222, record_txt, 26, couleur_noir);

    /* Afficher les blocs placés */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (i = 0; i < NB_LIGNES; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            if (jeu->grille[i][j] != 0) {
                rect.x = DECALAGE_GRILLE_X + j * TAILLE_CELLULE;
                rect.y = DECALAGE_GRILLE_Y + i * TAILLE_CELLULE;
                rect.w = TAILLE_CELLULE;
                rect.h = TAILLE_CELLULE;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    /* Afficher le tétrimino A (bleu) */
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            if (tetrimino_a->forme[i][j] != 0) {
                x = DECALAGE_GRILLE_X + (tetrimino_a->x + j) * TAILLE_CELLULE;
                y = DECALAGE_GRILLE_Y + (tetrimino_a->y + i) * TAILLE_CELLULE;
                rect.x = x; rect.y = y; rect.w = TAILLE_CELLULE; rect.h = TAILLE_CELLULE;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    /* Afficher le tétrimino B (rouge) */
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            if (tetrimino_b->forme[i][j] != 0) {
                x = DECALAGE_GRILLE_X + (tetrimino_b->x + j) * TAILLE_CELLULE;
                y = DECALAGE_GRILLE_Y + (tetrimino_b->y + i) * TAILLE_CELLULE;
                rect.x = x; rect.y = y; rect.w = TAILLE_CELLULE; rect.h = TAILLE_CELLULE;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    /* Afficher les tétriminos suivants */
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); /* Bleu pour A */
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            if (tetrimino_suivant_a->forme[i][j] != 0) {
                x = 30 + (tetrimino_suivant_a->x + j) * TAILLE_CELLULE;
                y = 200 + (tetrimino_suivant_a->y + i) * TAILLE_CELLULE;
                rect.x = x; rect.y = y; rect.w = TAILLE_CELLULE; rect.h = TAILLE_CELLULE;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); /* Rouge pour B */
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            if (tetrimino_suivant_b->forme[i][j] != 0) {
                x = 30 + (tetrimino_suivant_b->x + j) * TAILLE_CELLULE;
                y = 320 + (tetrimino_suivant_b->y + i) * TAILLE_CELLULE;
                rect.x = x; rect.y = y; rect.w = TAILLE_CELLULE; rect.h = TAILLE_CELLULE;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    afficher_grille();
    SDL_RenderPresent(renderer);
}

void invalider_cache_slots(void) {
    cache_slots_valide = 0;
}

void superposer_image(char *nom_fichier) {
    afficher_image(nom_fichier);
}

#endif /* _AFFICHAGE_C */
