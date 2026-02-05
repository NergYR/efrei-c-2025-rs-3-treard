#include "main.h"
#include "firstLevel.h"
#include "framework.h"
#include "entities.h"
#include "ghosts.h"
#include "game.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction pour obtenir la texture appropriée pour un fantôme
SDL_Texture *getGhostTexture(const MovingEntity *ghost, const Textures *textures)
{
    if (ghost->frightened)
    {
        return textures->textureBLue;
    }
    
    // Déterminer la direction pour choisir la texture
    int dirX = ghost->dir.x;
    int dirY = ghost->dir.y;
    
    if (dirY < 0) // haut
    {
        switch (ghost->name)
        {
            case CLYDE: return textures->textureClydeU;
            case PINKY: return textures->texturePinkyU;
            case INKY: return textures->textureInkyU;
            case BLINKY: return textures->textureBlinkyU;
            default: return textures->textureClydeU;
        }
    }
    else if (dirY > 0) // bas
    {
        switch (ghost->name)
        {
            case CLYDE: return textures->textureClydeD;
            case PINKY: return textures->texturePinkyD;
            case INKY: return textures->textureInkyD;
            case BLINKY: return textures->textureBlinkyD;
            default: return textures->textureClydeD;
        }
    }
    else if (dirX < 0) // gauche
    {
        switch (ghost->name)
        {
            case CLYDE: return textures->textureClydeL;
            case PINKY: return textures->texturePinkyL;
            case INKY: return textures->textureInkyL;
            case BLINKY: return textures->textureBlinkyL;
            default: return textures->textureClydeL;
        }
    }
    else // droite ou immobile
    {
        switch (ghost->name)
        {
            case CLYDE: return textures->textureClyde;
            case PINKY: return textures->texturePinky;
            case INKY: return textures->textureInky;
            case BLINKY: return textures->textureBlinky;
            default: return textures->textureClyde;
        }
    }
}


int gameLoop(void)
{
    RendererParameters params;
    Textures textures;

    // Initialisation du framework
    initWindowed(&params, &textures);

    // Charger le premier niveau
#ifdef PACMAN_TESTS
    char **level = fw_test_get_level();
#else
    char **level = loadFirstLevel();
#endif

    // Initialiser Pacman
    MovingEntity pacman;
    MovingEntity ghosts[4];
    int ghostCount = 0;
    int score = 0;
    
    // Parcourir le niveau pour trouver Pacman et les fantômes
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (level[i][j] == 'O')
            {
                initEntity(&pacman, j, i, PACMAN);
                level[i][j] = ' ';
            }
            else if (level[i][j] == 'C' && ghostCount < 4)
            {
                initEntity(&ghosts[ghostCount], j, i, CLYDE);
                ghostCount++;
                level[i][j] = ' ';
            }
            else if (level[i][j] == 'P' && ghostCount < 4)
            {
                initEntity(&ghosts[ghostCount], j, i, PINKY);
                ghostCount++;
                level[i][j] = ' ';
            }
            else if (level[i][j] == 'I' && ghostCount < 4)
            {
                initEntity(&ghosts[ghostCount], j, i, INKY);
                ghostCount++;
                level[i][j] = ' ';
            }
            else if (level[i][j] == 'B' && ghostCount < 4)
            {
                initEntity(&ghosts[ghostCount], j, i, BLINKY);
                ghostCount++;
                level[i][j] = ' ';
            }
        }
    }
    
    // Direction désirée par le joueur
    Coord desiredDir = {0, 0};

    // Boucle de jeu
    int running = 1;
    while (running)
    {
        // Sauvegarder les positions précédentes pour détecter les croisements
        MovingEntity prevPacman = pacman;
        MovingEntity prevGhosts[4];
        for (int g = 0; g < ghostCount; g++)
        {
            prevGhosts[g] = ghosts[g];
        }
        
        // Écouter les entrées clavier
        int input = getInput();
        
        // Si l'utilisateur appuie sur Échap ou ferme la fenêtre, on quitte
        if (input == SDLK_ESCAPE || input == SDL_EVENT_QUIT)
        {
            running = 0;
            continue;
        }
        
        // Mémoriser la commande désirée de l'utilisateur
        if (input == SDLK_UP)
        {
            desiredDir.x = 0;
            desiredDir.y = -1;
            pacman.angle = 90.0f;
        }
        else if (input == SDLK_DOWN)
        {
            desiredDir.x = 0;
            desiredDir.y = 1;
            pacman.angle = 270.0f;
        }
        else if (input == SDLK_LEFT)
        {
            desiredDir.x = -1;
            desiredDir.y = 0;
            pacman.angle = 0.0f;
        }
        else if (input == SDLK_RIGHT)
        {
            desiredDir.x = 1;
            desiredDir.y = 0;
            pacman.angle = 180.0f;
        }
        
        // Essayer d'abord la direction désirée
        int newX = pacman.pos.x + desiredDir.x;
        int newY = pacman.pos.y + desiredDir.y;
        
        // Wraparound
        if (newX < 0) newX = WIDTH - 1;
        if (newX >= WIDTH) newX = 0;
        if (newY < 0) newY = HEIGHT - 1;
        if (newY >= HEIGHT) newY = 0;
        
        // Si la direction désirée est valide, l'adopter
        if (level[newY][newX] != 'H')
        {
            pacman.dir.x = desiredDir.x;
            pacman.dir.y = desiredDir.y;
            pacman.pos.x = newX;
            pacman.pos.y = newY;
        }
        else
        {
            // Sinon, essayer de continuer dans la direction actuelle
            newX = pacman.pos.x + pacman.dir.x;
            newY = pacman.pos.y + pacman.dir.y;
            
            // Wraparound
            if (newX < 0) newX = WIDTH - 1;
            if (newX >= WIDTH) newX = 0;
            if (newY < 0) newY = HEIGHT - 1;
            if (newY >= HEIGHT) newY = 0;
            
            // Si la direction courante est valide, continuer
            if (level[newY][newX] != 'H')
            {
                pacman.pos.x = newX;
                pacman.pos.y = newY;
            }
            // Sinon, Pacman s'arrête
        }
        
        // Manger les pac-gums
        if (level[pacman.pos.y][pacman.pos.x] == '.')
        {
            level[pacman.pos.y][pacman.pos.x] = ' ';
            score += 10;
        }
        // Manger les super pac-gums
        else if (level[pacman.pos.y][pacman.pos.x] == 'G')
        {
            level[pacman.pos.y][pacman.pos.x] = ' ';
            score += 50;
            
            // Faire demi-tour et effrayer tous les fantômes
            turnAllGhostsAround(ghosts, ghostCount);
            frightenAllGhosts(ghosts, ghostCount);
        }
        
        // Vérifier les collisions avec les fantômes AVANT de les déplacer
        int gameOver = 0;
        for (int g = 0; g < ghostCount; g++)
        {
            if (checkCollision(&pacman, &ghosts[g]))
            {
                if (ghosts[g].frightened)
                {
                    // Pacman mange le fantôme bleu
                    score += 200;
                    resetGhostToStart(&ghosts[g]);
                }
                else
                {
                    // Game over
                    gameOver = 1;
                }
            }
        }
        
        // Si pas game over, déplacer les fantômes
        if (!gameOver)
        {
            for (int g = 0; g < ghostCount; g++)
            {
                ghostMove((const char **)level, &ghosts[g], &pacman);
            }
            
            // Vérifier les collisions APRÈS le déplacement des fantômes
            for (int g = 0; g < ghostCount; g++)
            {
                // Vérifier collision normale et croisement
                if (checkCrossCollision(&pacman, &ghosts[g], &prevPacman, &prevGhosts[g]))
                {
                    if (ghosts[g].frightened)
                    {
                        // Pacman mange le fantôme bleu
                        score += 200;
                        resetGhostToStart(&ghosts[g]);
                    }
                    else
                    {
                        // Game over
                        gameOver = 1;
                    }
                }
            }
        }
        
        // Vérifier la victoire (plus de pac-gums)
        if (win((const char **)level))
        {
            // Affichage final
            drawLevel(level, &params, &textures);
            
            for (int g = 0; g < ghostCount; g++)
            {
                SDL_Texture *ghostTexture = getGhostTexture(&ghosts[g], &textures);
                drawSpriteOnGrid(ghostTexture, ghosts[g].pos.x, ghosts[g].pos.y, 0.0f, &params);
            }
            
            drawSpriteOnGrid(textures.texturePacman, pacman.pos.x, pacman.pos.y, pacman.angle, &params);
            update(&params);
            
#ifndef PACMAN_TESTS
            for (int i = 0; i < HEIGHT; i++) free(level[i]);
            free(level);
#endif
            return score;
        }
        
        // Afficher le niveau
        drawLevel(level, &params, &textures);
        
        // Afficher les fantômes
        for (int g = 0; g < ghostCount; g++)
        {
            SDL_Texture *ghostTexture = getGhostTexture(&ghosts[g], &textures);
            drawSpriteOnGrid(ghostTexture, ghosts[g].pos.x, ghosts[g].pos.y, 0.0f, &params);
        }
        
        // Afficher Pacman
        drawSpriteOnGrid(textures.texturePacman, pacman.pos.x, pacman.pos.y, pacman.angle, &params);
        
        // Mettre à jour l'affichage
        update(&params);
        
        // Vérifier si game over
        if (gameOver)
        {
#ifndef PACMAN_TESTS
            for (int i = 0; i < HEIGHT; i++) free(level[i]);
            free(level);
#endif
            return -score - 1;
        }
    }

    // Libérer la mémoire du niveau
#ifndef PACMAN_TESTS
    for (int i = 0; i < HEIGHT; i++)
    {
        free(level[i]);
    }
    free(level);
#endif

    return score;
}

#ifndef PACMAN_TESTS
int main(void)
{
    gameLoop();
    return 0;
}
#endif
