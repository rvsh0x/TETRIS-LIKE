
#include <time.h>
#include "affichage.h"
#include "menu.h"
#include "jeu.h"
#include "sauvegarde.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    srand(time(NULL));
    
    initialiser_affichage();
    initialiser_slots_sauvegarde(); /* Créer les fichiers de sauvegarde s'ils n'existent pas */
    invalider_cache_slots(); /* Initialiser le cache des slots */
    lancer_jeu();

    nettoyer_affichage(); 
    exit(EXIT_SUCCESS);
}
