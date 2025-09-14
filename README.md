# Tetris SDL2

Réimplémentation du classique Tetris en C avec des fonctionnalités modernes. Inclut des modes de jeu personnalisés, un système de score avancé, système de sauvegarde, et effets visuels innovants.

## Fonctionnalités

- **Jeu classique Tetris** 
- **Mode solo et mode à deux joueurs**
- **Système de sauvegarde** avec 5 slots
- **Tableau des meilleurs scores**
- **Interface graphique** 
- **Contrôles clavier** intuitifs

## Prérequis

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

### Linux (Fedora)
```bash
sudo dnf install SDL2-devel SDL2_image-devel SDL2_ttf-devel
```

### Linux (Arch)
```bash
sudo pacman -S sdl2 sdl2_image sdl2_ttf
```

### macOS
```bash
brew install sdl2 sdl2_image sdl2_ttf
```

### Windows (MinGW)
Installer SDL2, SDL2_image et SDL2_ttf via MSYS2 ou vcpkg.

## Compilation

### Compilation automatique
```bash
make
```

### Test de détection des bibliothèques
```bash
make test-compile
```

### Compilation manuelle
```bash
gcc -W -Wall -pedantic -std=c89 -I/usr/include/SDL2 *.c -o tetris -lSDL2 -lSDL2_image -lSDL2_ttf
```

## Utilisation

### Lancer le jeu
```bash
./tetris
```

### Commandes disponibles
- **Flèches** : Déplacer les pièces
- **Q - D** : Rotation
- **Échap** : Pause/Quitter
- **H** : Aide
- **Q** : Quitter

### Nettoyage
```bash
make clean
```

### Réinitialiser les sauvegardes
```bash
make reset_game
```

## Structure du projet

```
tetris/
├── src/                # Code source
│   ├── main.c          # Point d'entrée
│   ├── jeu.c/h         # Logique du jeu
│   ├── affichage.c/h   # Rendu graphique SDL2
│   ├── menu.c/h        # Menus et navigation
│   ├── sauvegarde.c/h  # Système de sauvegarde
│   └── types.h         # Définitions des structures
├── Makefile            # Configuration de compilation
├── README.md           # Documentation
├── img/                # Images du jeu
│   ├── Tetris_Home.png
│   ├── Tetris_Menu.png
│   ├── Tetris_Game.png
│   └── ...
└── data/               # Données du jeu
    ├── *.ttf           # Polices
    ├── scores.txt      # Meilleurs scores
    └── slot_*.bin      # Sauvegardes
```

## Création d'un package de distribution

```bash
make dist
```

Cela crée un fichier `tetris-sdl2.tar.gz` contenant tout le projet.

## Dépannage

### Erreur "SDL2/SDL.h not found"
Vérifiez que les bibliothèques SDL2 sont installées et que les chemins d'inclusion sont corrects.

### Erreur de police
Le jeu utilise `data/avenir-next-heavy.ttf`. Si elle n'est pas trouvée, il utilisera Arial comme police de secours.

### Problèmes de compilation
Utilisez `make test-compile` pour diagnostiquer les problèmes de détection des bibliothèques.

## Auteur

- LAICHE Khayr Eddine
- GHODBANE Rachid

## Licence

Ce projet est sous licence MIT.
