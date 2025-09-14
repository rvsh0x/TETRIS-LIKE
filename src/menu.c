#ifndef _MENU_C_
#define _MENU_C_
#include <SDL2/SDL.h>
#include "affichage.h"
#include "menu.h"
#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>

/* Fonction pour attendre une entrée clavier */
int attendre_entree(void) {
    SDL_Event event;
    
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                /* N'importe quelle touche continue le jeu après la défaite */
                return 1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                /* Clic de souris aussi */
                return 1;
            }
            else if (event.type == SDL_QUIT) {
                return 0;
            }
        }
        SDL_Delay(16); /* Éviter une boucle trop rapide */
    }
    return -1; /* Valeur par défaut si aucune touche correspondante n'est pressée */
}

/* Fonction pour lancer le jeu */
int lancer_jeu(void) {
    int aide = 0;       /* État de l'aide (affichée ou non) */
    int continuer = 1;  /* Variable de contrôle pour la boucle */
    int choix_menu; 
    int mode;
    int x, y;
    int version_aide;
    int chargement;     /* Numéro du slot de sauvegarde */
    Jeu jeu;            /* Déclaration de la variable jeu */
    SDL_Event event;
    int redessiner = 1; /* Flag pour contrôler le redessinage */
    /*affecter_scores(scores);*/
    
    while (continuer) {
        /* Gestion des événements */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                x = event.button.x;
                y = event.button.y;
                if (aide && x >= 20 && x <= 300 && y >= 600 && y <= 670) {
                    version_aide = (version_aide + 1) % 2;
                    redessiner = 1;
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                /* Basculer l'aide avec la touche 'h' */
                if (event.key.keysym.sym == SDLK_h) {
                    aide = (aide + 1) % 2;
                    redessiner = 1;
                }
                /* Quitter avec la touche 'q' */
                else if (event.key.keysym.sym == SDLK_q) {
                    return 0;
                }
                /* Continuer avec la touche Entrée */
                else if (event.key.keysym.sym == SDLK_RETURN) {
                
                choix_menu = lancer_menu();
                if (choix_menu == 2) {

                    mode = menu_mode();
                    if(mode == 1){
                        init_jeu(&jeu); /* Initialiser le jeu */
                        if (jouer(&jeu)){
                            continuer=1;
                        }else{
                            return 0;
                        } 
                    }

                    if(mode == 2){
                        init_jeu(&jeu); /* Initialiser le jeu */
                        if (jouer_a_deux(&jeu)){
                            continuer=1;
                        }else{
                            return 0;
                        } 
                    }


                }

                if (choix_menu == 3){
                    chargement=0;
                    while(chargement==0){
                        if(charger_partie(&jeu)){
                            chargement=1;
                            if (jouer(&jeu)){
                                continuer=1;
                            }else{
                                return 0;
                            }
                        }else{
                            continuer=1;
                        }
                    }
                } 

                if (choix_menu == 4){
                    afficher_records();

                } 

                /* par ex si on veut faire mode deux joueurs */
                /*if (choix_menu == 3) {
                    return jeu_a_deux(); Lancer le mode deux joueurs */
                if (choix_menu == 0) {
                    return 0; /* Retourne 0 pour indiquer que le programme doit se terminer */
                }
                }
            }
            else if (event.type == SDL_QUIT) {
                return 0;
            }
        }
        
        /* Afficher seulement si nécessaire */
        if (redessiner) {
            if (aide) {
                if(version_aide==1){
                    afficher_aide_2();  /* Affiche l'aide si `aide` est activé */
                } else {
                    afficher_aide_1();  /* Affiche l'aide si `aide` est activé */
                }
            } else {
                afficher_accueil();  /* Affiche l'écran d'accueil par défaut */
            }
            redessiner = 0;
        }
        
        SDL_Delay(16); /* Éviter une boucle trop rapide */
    }
    

    
    return 1;  /* Par défaut, continue si aucune condition d'arrêt */
}
/*Fonction pour lancer le menu principal 
int lancer_menu() {
    int aide = 0;            
    int continuer = 1;      
    int x, y; 

    MLV_Keyboard_button touche; 
    MLV_Event type_evenement;

    while (continuer) {
        if (aide) {
            afficher_aide(); 
        } else {
            afficher_menu(); 
        }
        
        type_evenement = MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &x, &y);

        if (type_evenement == MLV_MOUSE_BUTTON) {
            if (x >= 330 && x <= 905 && y >= 275 && y <= 355) {
                return 2;  
            } else if (x >= 330 && x <= 905 && y >= 380 && y <= 460) {
                return 3;  
            } else if (x >= 330 && x <= 905 && y >= 480 && y <= 560) {
                return 4;  
            }
        }
        
        if (type_evenement == MLV_KEY) {
            if (touche == MLV_KEYBOARD_h) {
                aide = (aide + 1) % 2;  
            }
            if (touche == MLV_KEYBOARD_q) {
                return 0;
            }
        }
    }
    
    return 1;  
}
*/

/* Fonction pour lancer le menu principal */
int lancer_menu(void) {
    int aide = 0;            
    int continuer = 1;     
    int version_aide = 0; 
    int x, y;
    SDL_Event event;
    int redessiner = 1; /* Flag pour contrôler le redessinage */

    while (continuer) {
        /* Gestion des événements */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                x = event.button.x;
                y = event.button.y;
                
                if (aide && x >= 20 && x <= 300 && y >= 600 && y <= 670) {
                    version_aide = (version_aide + 1) % 2; 
                    redessiner = 1;
                }
                else if (!aide) {
                    if (x >= 330 && x <= 905 && y >= 275 && y <= 355) {
                        return 2;  /* Lancer une nouvelle partie */
                    } else if (x >= 330 && x <= 905 && y >= 380 && y <= 460) {
                        /*Option "Charger une partie"*/
                        return 3;
                    } else if (x >= 330 && x <= 905 && y >= 480 && y <= 560) {
                        return 4;  /* Afficher les meilleurs scores */
                    }
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_h) {
                    aide = (aide + 1) % 2;  
                    redessiner = 1;
                }
                else if (event.key.keysym.sym == SDLK_q) {
                    return 0;  /* Quitter */
                }
            }
            else if (event.type == SDL_QUIT) {
                return 0;
            }
        }
        
        /* Afficher seulement si nécessaire */
        if (redessiner) {
            if (aide) {
                if(version_aide==1){
                    afficher_aide_2();  /* Affiche l'aide si `aide` est activé */
                } else {
                    afficher_aide_1();  /* Affiche l'aide si `aide` est activé */
                }
            } else {
                afficher_menu(); 
            }
            redessiner = 0;
        }
        
        SDL_Delay(16); /* Éviter une boucle trop rapide */
    }
    
    return 1;  
}


/* Fonction pour afficher le menu de pause */
int menu_pause(Jeu *jeu){
    int aide = 0;   
    int version_aide = 0;               
    int x, y;
    SDL_Event event;
    int redessiner = 1; /* Flag pour contrôler le redessinage */

    while (jeu->en_pause) {
        /* Gestion des événements */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                x = event.button.x;
                y = event.button.y;
                
                if (aide && x >= 20 && x <= 300 && y >= 600 && y <= 670) {
                    version_aide = (version_aide + 1) % 2;
                    redessiner = 1;
                }
                else if (!aide) {
                    if (x >= 330 && x <= 905 && y >= 230 && y <= 320) {
                        jeu->en_pause = (jeu->en_pause + 1) % 2;  /* Continuer le jeu */
                    } else if (x >= 330 && x <= 905 && y >= 330 && y <= 410) {
                        sauvegarder_partie(jeu); 
                        redessiner = 1; /* Redessiner après sauvegarde */
                    } else if (x >= 330 && x <= 905 && y >= 420 && y <= 500) {
                        return 2;
                    }
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_h) {
                    aide = (aide + 1) % 2;  
                    redessiner = 1;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    jeu->en_pause = (jeu->en_pause + 1) % 2;  /* Continuer le jeu */
                }
                else if (event.key.keysym.sym == SDLK_q) {
                    return 0;
                }
            }
            else if (event.type == SDL_QUIT) {
                return 0;
            }
        }
        
        /* Afficher seulement si nécessaire */
        if (redessiner) {
            if (aide) {
                if(version_aide==1){
                    afficher_aide_2();  /* Affiche l'aide si `aide` est activé */
                } else {
                    afficher_aide_1();  /* Affiche l'aide si `aide` est activé */
                }
            } else {
                afficher_pause();
            }
            redessiner = 0;
        }
        
        SDL_Delay(16); /* Éviter une boucle trop rapide */
    }
    
    return 1;  
}


int menu_sauvegarde(void) {
    int aide = 0;  
    int version_aide = 0;                
    int x, y;
    SDL_Event event;
    int slot = 0;
    int continuer = 1;
    int redessiner = 1; /* Flag pour contrôler le redessinage */

    while (continuer) {
        /* Gestion des événements */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                x = event.button.x;
                y = event.button.y;
                
                if (aide && x >= 20 && x <= 300 && y >= 600 && y <= 670) {
                    version_aide = (version_aide + 1) % 2;
                }
                else if (!aide) {
               


                if (x > 100 && x < 280 &&
                    y > 320 && y < 520) {
                    slot = 1; 
                    
                   
                }

                if (x > 325 && x < 485 &&
                    y > 320 && y < 520) {
                    slot = 2;   
                   
                    
                }

                if (x > 550 && x < 710 &&
                    y > 320 && y < 520) {
                    slot = 3;  
                   
                    
                }

                if (x > 775 && x < 935 &&
                    y > 320 && y < 520) {
                    slot = 4;  
                    
                    
                }

                if (x > 1000 && x < 1160 &&
                        y > 320 && y < 520) {
                    slot = 5;    
                }
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q) {
                    return 0;
                }
                else if (event.key.keysym.sym == SDLK_h) {
                    aide = (aide + 1) % 2;
                    redessiner = 1;
                }
            }
            else if (event.type == SDL_QUIT) {
                return 0;
            }
        }
        
        /* Afficher seulement si nécessaire */
        if (redessiner) {
            if (aide) {
                if(version_aide==1){
                    afficher_aide_2();  /* Affiche l'aide si `aide` est activé */
                } else {
                    afficher_aide_1();  /* Affiche l'aide si `aide` est activé */
                }
            } else {
                afficher_sauvegardes();
            }
            redessiner = 0;
        }
        
        if( slot != 0 && slot_est_vide(slot)==1){
            continuer=0;
        }
        
        SDL_Delay(16); /* Éviter une boucle trop rapide */

        while( slot != 0 && slot_est_vide(slot)==0){
            int redessiner_ecrase = 1;
            
            while (slot != 0 && slot_est_vide(slot)==0) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        x = event.button.x;
                        y = event.button.y;
                        
                        if (x > 370 && x < 580 && y > 380 && y < 470) {
                            return slot;
                        }
                        else if (x > 650 && x < 850 && y > 380 && y < 470) {
                            slot = 0;
                        }
                    }
                    else if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q) {
                            return 0;
                        }
                        else if (event.key.keysym.sym == SDLK_RETURN) {
                            return slot; /* Confirmer l'écrasement */
                        }
                    }
                    else if (event.type == SDL_QUIT) {
                        return 0;
                    }
                }
                
                /* Afficher seulement si nécessaire */
                if (redessiner_ecrase) {
                    afficher_ecrase();
                    redessiner_ecrase = 0;
                }
                
                SDL_Delay(16); /* Éviter une boucle trop rapide */
            }
        }   
            
    }

    
    return slot;  
}


int menu_chargement(void) {
    int aide = 0;   
    int version_aide = 0;               
    int x, y;
    SDL_Event event;
    int slot = 0;
    int continuer = 1;
    int redessiner = 1; /* Flag pour contrôler le redessinage */

    while (continuer) {
        /* Gestion des événements */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                x = event.button.x;
                y = event.button.y;
                
                if (aide && x >= 20 && x <= 300 && y >= 600 && y <= 670) {
                    version_aide = (version_aide + 1) % 2;
                    redessiner = 1;
                }
                else if (!aide) {
                    if (x > 100 && x < 280 && y > 320 && y < 520) {
                        if (!slot_est_vide(1)) {
                            slot = 1; 
                            continuer = 0;
                        }
                    }
                    else if (x > 325 && x < 485 && y > 320 && y < 520) {
                        if (!slot_est_vide(2)) {
                            slot = 2; 
                            continuer = 0;
                        }
                    }
                    else if (x > 550 && x < 710 && y > 320 && y < 520) {
                        if (!slot_est_vide(3)) {
                            slot = 3;  
                            continuer = 0;
                        }
                    }
                    else if (x > 775 && x < 935 && y > 320 && y < 520) {
                        if (!slot_est_vide(4)) {
                            slot = 4;  
                            continuer = 0;
                        }
                    }
                    else if (x > 1000 && x < 1160 && y > 320 && y < 520) {
                        if (!slot_est_vide(5)) {
                            slot = 5;    
                            continuer = 0;
                        }
                    }
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q) {
                    return 0; /* Annuler - retourner 0 */
                }
                else if (event.key.keysym.sym == SDLK_h) {
                    aide = (aide + 1) % 2;
                    redessiner = 1;
                }
            }
            else if (event.type == SDL_QUIT) {
                return 0;
            }
        }
        
        /* Afficher seulement si nécessaire */
        if (redessiner) {
            if (aide) {
                if(version_aide==1){
                    afficher_aide_2();  /* Affiche l'aide si `aide` est activé */
                } else {
                    afficher_aide_1();  /* Affiche l'aide si `aide` est activé */
                }
            } else {
                afficher_sauvegardes();
            }
            redessiner = 0;
        }
        
        SDL_Delay(16); /* Éviter une boucle trop rapide */
    }
    
    return slot;  
}


int menu_mode(void) {
    int x, y, choix = 0;
    SDL_Event event;
    int redessiner = 1; /* Flag pour contrôler le redessinage */
    
    while(choix == 0) {
        /* Gestion des événements */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                x = event.button.x;
                y = event.button.y;
                
                if (x >= 330 && x <= 905 && y >= 320 && y <= 400) {
                    choix = 1;
                }
                else if (x >= 330 && x <= 905 && y >= 420 && y <= 500) {
                    choix = 2;
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q) {
                    return 0;
                }
                else if (event.key.keysym.sym == SDLK_1) {
                    choix = 1;
                }
                else if (event.key.keysym.sym == SDLK_2) {
                    choix = 2;
                }
            }
            else if (event.type == SDL_QUIT) {
                return 0;
            }
        }
        
        /* Afficher seulement si nécessaire */
        if (redessiner) {
            afficher_player_mode();
            redessiner = 0;
        }
        
        SDL_Delay(16); /* Éviter une boucle trop rapide */
    }

    return choix;
}


#endif /* _MENU_C */
