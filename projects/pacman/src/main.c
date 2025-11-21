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

    // Position initiale de Pacman au centre de l'écran
    int pacmanX = WIDTH / 2;
    int pacmanY = HEIGHT / 2;
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
        
        // Gérer les déplacements avec les touches directionnelles
        if (input == SDLK_UP || input == SDLK_W)
        {
            pacmanY--;
            pacmanAngle = 90.0f; // Nord (haut)
        }
        else if (input == SDLK_DOWN || input == SDLK_S)
        {
            pacmanY++;
            pacmanAngle = 270.0f; // Sud (bas)
        }
        else if (input == SDLK_LEFT || input == SDLK_A)
        {
            pacmanX--;
            pacmanAngle = 0.0f; // Ouest (gauche)
        }
        else if (input == SDLK_RIGHT || input == SDLK_D)
        {
            pacmanX++;
            pacmanAngle = 180.0f; // Est (droite)
        }
        
        // Limiter Pacman aux bordures de l'écran
        if (pacmanX < 0) pacmanX = 0;
        if (pacmanX >= WIDTH) pacmanX = WIDTH - 1;
        if (pacmanY < 0) pacmanY = 0;
        if (pacmanY >= HEIGHT) pacmanY = HEIGHT - 1;
        
        // Effacer l'écran
        SDL_SetRenderDrawColor(params.renderer, 0, 0, 0, 255);
        SDL_RenderClear(params.renderer);
        
        // Afficher Pacman
        drawSpriteOnGrid(textures.texturePacman, pacmanX, pacmanY, pacmanAngle, &params);
        
        // Présenter le rendu
        SDL_RenderPresent(params.renderer);
        
        // Mettre à jour l'affichage (gestion du framerate)
        update(&params);
    }

    return 0;
}

#ifndef PACMAN_TESTS
int main(void)
{
    gameLoop();
    return 0;
}
#endif
