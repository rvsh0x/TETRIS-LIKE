# Makefile pour Tetris SDL2 - Version portable
CC=gcc
CFLAGS=-W -Wall -pedantic -std=c89
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf

# Détection automatique des chemins SDL2
# Linux (Ubuntu/Debian)
ifeq ($(shell uname),Linux)
    CFLAGS += $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf 2>/dev/null)
    LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf 2>/dev/null)
endif

# macOS (Homebrew)
ifeq ($(shell uname),Darwin)
    # Essayer pkg-config d'abord (Homebrew)
    ifneq ($(shell pkg-config --cflags sdl2 2>/dev/null),)
        CFLAGS += $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
        LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf)
    else
        # Fallback pour installations manuelles
        CFLAGS += -I/usr/local/include/SDL2 -I/usr/include/SDL2
        LDFLAGS += -L/usr/local/lib -L/usr/lib
    endif
endif

# Windows (MinGW)
ifeq ($(OS),Windows_NT)
    CFLAGS += -I/usr/include/SDL2
    LDFLAGS += -L/usr/lib
endif

# Règle par défaut
all: tetris

# Règle pour compiler l'exécutable
tetris: src/main.o src/affichage.o src/menu.o src/jeu.o src/sauvegarde.o
	$(CC) -o tetris src/main.o src/affichage.o src/menu.o src/jeu.o src/sauvegarde.o $(LDFLAGS)

# Règles pour compiler les fichiers objets
src/main.o: src/main.c src/affichage.h src/menu.h src/jeu.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/affichage.o: src/affichage.c src/affichage.h
	$(CC) $(CFLAGS) -c src/affichage.c -o src/affichage.o

src/menu.o: src/menu.c src/menu.h src/jeu.h
	$(CC) $(CFLAGS) -c src/menu.c -o src/menu.o

src/jeu.o: src/jeu.c src/jeu.h src/affichage.h src/sauvegarde.h src/menu.h
	$(CC) $(CFLAGS) -c src/jeu.c -o src/jeu.o

src/sauvegarde.o: src/sauvegarde.c src/sauvegarde.h
	$(CC) $(CFLAGS) -c src/sauvegarde.c -o src/sauvegarde.o

# Règle pour nettoyer les fichiers objets et binaires
clean:
	rm -f src/*.o tetris

# Règle pour réinitialiser le jeu
reset_game:
	rm -f data/slot_1.bin data/slot_2.bin data/slot_3.bin data/slot_4.bin data/slot_5.bin
	touch data/slot_1.bin data/slot_2.bin data/slot_3.bin data/slot_4.bin data/slot_5.bin

# Règles pour installer les dépendances SDL2
install-deps-ubuntu:
	sudo apt-get update
	sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev

install-deps-fedora:
	sudo dnf install SDL2-devel SDL2_image-devel SDL2_ttf-devel

install-deps-arch:
	sudo pacman -S sdl2 sdl2_image sdl2_ttf

install-deps-macos:
	brew install sdl2 sdl2_image sdl2_ttf

# Règle pour tester la compilation
test-compile:
	@echo "Test de détection des bibliothèques SDL2..."
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@$(CC) $(CFLAGS) -c src/main.c -o test_main.o
	@rm -f test_main.o
	@echo "✅ Compilation de test réussie"

# Règle pour créer un package de distribution
dist: clean
	mkdir -p tetris-dist
	cp -r src/ tetris-dist/
	cp Makefile README.md tetris-dist/
	cp -r img/ tetris-dist/
	cp -r data/ tetris-dist/
	tar -czf tetris-sdl2.tar.gz tetris-dist/
	rm -rf tetris-dist/
	@echo "Package créé: tetris-sdl2.tar.gz"

.PHONY: all clean reset_game install-deps-ubuntu install-deps-fedora install-deps-arch install-deps-macos test-compile dist