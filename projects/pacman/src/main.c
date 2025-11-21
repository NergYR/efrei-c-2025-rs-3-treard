#include "main.h"
#include "firstLevel.h"
#include "framework.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>


int gameLoop(void)
{
    RendererParameters params;
    Textures textures;

    // Initialisation du framework
    initWindowed(&params, &textures);

    // Charger le premier niveau
    char **level = loadFirstLevel();

    // Trouver la position initiale de Pacman (caractère 'O' dans le niveau)
    int pacmanX = WIDTH / 2;
    int pacmanY = HEIGHT / 2;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (level[i][j] == 'O')
            {
                pacmanX = j;
                pacmanY = i;
                level[i][j] = '.'; // Remplacer par un point
            }
        }
    }
    
    float pacmanAngle = 0.0f;

    // Boucle de jeu
    int running = 1;
    while (running)
    {
        // Écouter les entrées clavier
        int input = getInput();
        
        // Si l'utilisateur appuie sur Échap ou ferme la fenêtre, on quitte
        if (input == SDLK_ESCAPE || input == SDL_EVENT_QUIT)
        {
            running = 0;
        }
        
        // Calculer la nouvelle position en fonction de l'entrée
        int newX = pacmanX;
        int newY = pacmanY;
        
        if (input == SDLK_UP || input == SDLK_W)
        {
            newY--;
            pacmanAngle = 90.0f; // Nord (haut)
        }
        else if (input == SDLK_DOWN || input == SDLK_S)
        {
            newY++;
            pacmanAngle = 270.0f; // Sud (bas)
        }
        else if (input == SDLK_LEFT || input == SDLK_A)
        {
            newX--;
            pacmanAngle = 0.0f; // Ouest (gauche)
        }
        else if (input == SDLK_RIGHT || input == SDLK_D)
        {
            newX++;
            pacmanAngle = 180.0f; // Est (droite)
        }
        
        // Vérifier les collisions avec les murs et les bordures
        if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT)
        {
            // Si la case n'est pas un mur ('H'), on peut se déplacer
            if (level[newY][newX] != 'H')
            {
                pacmanX = newX;
                pacmanY = newY;
            }
        }
        
        // Afficher le niveau
        drawLevel(level, &params, &textures);
        
        // Afficher Pacman
        drawSpriteOnGrid(textures.texturePacman, pacmanX, pacmanY, pacmanAngle, &params);
        
        // Mettre à jour l'affichage (gestion du framerate + présentation)
        update(&params);
    }

    // Libérer la mémoire du niveau
    for (int i = 0; i < HEIGHT; i++)
    {
        free(level[i]);
    }
    free(level);

    return 0;
}

#ifndef PACMAN_TESTS
int main(void)
{
    gameLoop();
    return 0;
}
#endif
