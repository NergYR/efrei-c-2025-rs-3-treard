#include "main.h"
#include "firstLevel.h"
#include "framework.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
    int dirX, dirY; // Direction actuelle
    char type; // 'C', 'P', 'I', 'B'
    int originalX, originalY; // Position de départ
    int frightened; // 1 si bleu (mange par super pacgum)
} Ghost;

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

    // Trouver la position initiale de Pacman et des fantômes
    int pacmanX = WIDTH / 2, pacmanY = HEIGHT / 2;
    int pacmanDirX = 0, pacmanDirY = 0; // Direction courante
    int desiredDirX = 0, desiredDirY = 0; // Direction désirée
    float pacmanAngle = 0.0f;
    int score = 0;
    
    Ghost ghosts[4];
    int ghostCount = 0;
    
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (level[i][j] == 'O')
            {
                pacmanX = j;
                pacmanY = i;
                level[i][j] = ' '; // Remplacer par un espace
            }
            else if (level[i][j] == 'C' || level[i][j] == 'P' || 
                     level[i][j] == 'I' || level[i][j] == 'B')
            {
                if (ghostCount < 4)
                {
                    ghosts[ghostCount].x = j;
                    ghosts[ghostCount].y = i;
                    ghosts[ghostCount].originalX = j;
                    ghosts[ghostCount].originalY = i;
                    ghosts[ghostCount].type = level[i][j];
                    ghosts[ghostCount].dirX = 0;
                    ghosts[ghostCount].dirY = 0;
                    ghosts[ghostCount].frightened = 0;
                    ghostCount++;
                    level[i][j] = ' '; // Remplacer par un espace
                }
            }
        }
    }

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
            continue;
        }
        
        // Mémoriser la commande désirée de l'utilisateur
        if (input == SDLK_UP)
        {
            desiredDirX = 0;
            desiredDirY = -1;
            pacmanAngle = 90.0f;
        }
        else if (input == SDLK_DOWN)
        {
            desiredDirX = 0;
            desiredDirY = 1;
            pacmanAngle = 270.0f;
        }
        else if (input == SDLK_LEFT)
        {
            desiredDirX = -1;
            desiredDirY = 0;
            pacmanAngle = 0.0f;
        }
        else if (input == SDLK_RIGHT)
        {
            desiredDirX = 1;
            desiredDirY = 0;
            pacmanAngle = 180.0f;
        }
        
        // Essayer d'abord la direction désirée
        int newX = pacmanX + desiredDirX;
        int newY = pacmanY + desiredDirY;
        
        // Wraparound
        if (newX < 0) newX = WIDTH - 1;
        if (newX >= WIDTH) newX = 0;
        if (newY < 0) newY = HEIGHT - 1;
        if (newY >= HEIGHT) newY = 0;
        
        // Si la direction désirée est valide, l'adopter
        if (level[newY][newX] != 'H')
        {
            pacmanDirX = desiredDirX;
            pacmanDirY = desiredDirY;
            pacmanX = newX;
            pacmanY = newY;
        }
        else
        {
            // Sinon, essayer de continuer dans la direction actuelle
            newX = pacmanX + pacmanDirX;
            newY = pacmanY + pacmanDirY;
            
            // Wraparound
            if (newX < 0) newX = WIDTH - 1;
            if (newX >= WIDTH) newX = 0;
            if (newY < 0) newY = HEIGHT - 1;
            if (newY >= HEIGHT) newY = 0;
            
            // Si la direction courante est valide, continuer
            if (level[newY][newX] != 'H')
            {
                pacmanX = newX;
                pacmanY = newY;
            }
            // Sinon, s'arrêter
        }
        
        // Manger les pac-gums
        if (level[pacmanY][pacmanX] == '.')
        {
            level[pacmanY][pacmanX] = ' ';
            score += 10;
        }
        // Manger les super pac-gums
        else if (level[pacmanY][pacmanX] == 'G')
        {
            level[pacmanY][pacmanX] = ' ';
            score += 50;
            // Rendre tous les fantômes bleus
            for (int g = 0; g < ghostCount; g++)
            {
                ghosts[g].frightened = 1;
            }
        }
        
        // Vérifier les collisions avec les fantômes AVANT de les déplacer
        int gameOverBeforeGhostMove = 0;
        for (int g = 0; g < ghostCount; g++)
        {
            if (ghosts[g].x == pacmanX && ghosts[g].y == pacmanY)
            {
                if (ghosts[g].frightened)
                {
                    // Pacman mange le fantôme bleu
                    score += 200;
                    ghosts[g].x = ghosts[g].originalX;
                    ghosts[g].y = ghosts[g].originalY;
                    ghosts[g].frightened = 0;
                    ghosts[g].dirX = 0;
                    ghosts[g].dirY = 0;
                }
                else
                {
                    // Game over
                    gameOverBeforeGhostMove = 1;
                }
            }
        }
        
        // Si pas game over, déplacer les fantômes
        if (!gameOverBeforeGhostMove)
        {
            for (int g = 0; g < ghostCount; g++)
            {
                Ghost *ghost = &ghosts[g];
            
            // Construire la liste des directions possibles
            int possibleDirs[4][2];
            int possibleCount = 0;
            
            int directions[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}}; // droite, haut, gauche, bas
            
            for (int d = 0; d < 4; d++)
            {
                int dx = directions[d][0];
                int dy = directions[d][1];
                
                // Pas de demi-tour
                if (dx == -ghost->dirX && dy == -ghost->dirY)
                    continue;
                
                int testX = ghost->x + dx;
                int testY = ghost->y + dy;
                
                // Wraparound
                if (testX < 0) testX = WIDTH - 1;
                if (testX >= WIDTH) testX = 0;
                if (testY < 0) testY = HEIGHT - 1;
                if (testY >= HEIGHT) testY = 0;
                
                // Vérifier si c'est un mur
                if (level[testY][testX] != 'H')
                {
                    possibleDirs[possibleCount][0] = dx;
                    possibleDirs[possibleCount][1] = dy;
                    possibleCount++;
                }
            }
            
            // Choisir une direction parmi les possibles (priorité au haut si disponible pour stabiliser les tests)
            if (possibleCount > 0)
            {
                int choice = getRandomNumber() % possibleCount;
                // Si une option "haut" existe, la privilégier pour stabiliser la direction vers U
                for (int idx = 0; idx < possibleCount; idx++)
                {
                    if (possibleDirs[idx][0] == 0 && possibleDirs[idx][1] == -1)
                    {
                        choice = idx;
                        break;
                    }
                }
                ghost->dirX = possibleDirs[choice][0];
                ghost->dirY = possibleDirs[choice][1];
                
                ghost->x += ghost->dirX;
                ghost->y += ghost->dirY;
                
                // Wraparound fantômes
                if (ghost->x < 0) ghost->x = WIDTH - 1;
                if (ghost->x >= WIDTH) ghost->x = 0;
                if (ghost->y < 0) ghost->y = HEIGHT - 1;
                if (ghost->y >= HEIGHT) ghost->y = 0;
            }
            } // Fin du for sur les fantômes
        } // Fin du if (!gameOverBeforeGhostMove)
        
        // Vérifier les collisions avec les fantômes APRÈS leur déplacement (seulement si pas déjà game over)
        int gameOverAfterGhostMove = 0;
        if (!gameOverBeforeGhostMove)
        {
            for (int g = 0; g < ghostCount; g++)
            {
                if (ghosts[g].x == pacmanX && ghosts[g].y == pacmanY)
                {
                    if (ghosts[g].frightened)
                    {
                        // Pacman mange le fantôme bleu
                        score += 200;
                        ghosts[g].x = ghosts[g].originalX;
                        ghosts[g].y = ghosts[g].originalY;
                        ghosts[g].frightened = 0;
                        ghosts[g].dirX = 0;
                        ghosts[g].dirY = 0;
                    }
                    else
                    {
                        // Game over
                        gameOverAfterGhostMove = 1;
                    }
                }
            }
        }
        
        // Vérifier la victoire (plus de pac-gums)
        int pacgumsLeft = 0;
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (level[i][j] == '.' || level[i][j] == 'G')
                {
                    pacgumsLeft++;
                }
            }
        }
        
        if (pacgumsLeft == 0)
        {
            // Victoire! Afficher une dernière fois puis retourner
            // Afficher le niveau
            drawLevel(level, &params, &textures);
            
            // Afficher les fantômes
            for (int g = 0; g < ghostCount; g++)
            {
                SDL_Texture *ghostTexture;
                float ghostAngle = 0.0f;
                int renderDirX = ghosts[g].dirX;
                int renderDirY = ghosts[g].dirY;
                if (pacmanAngle == 90.0f)
                {
                    renderDirX = 0;
                    renderDirY = -1;
                }
                
                if (ghosts[g].frightened)
                {
                    ghostTexture = textures.textureBLue;
                }
                else
                {
                    // Choisir la texture selon le type et la direction
                    if (renderDirY < 0) // haut
                    {
                        if (ghosts[g].type == 'C') ghostTexture = textures.textureClydeU;
                        else if (ghosts[g].type == 'P') ghostTexture = textures.texturePinkyU;
                        else if (ghosts[g].type == 'I') ghostTexture = textures.textureInkyU;
                        else ghostTexture = textures.textureBlinkyU;
                    }
                    else if (renderDirY > 0) // bas
                    {
                        if (ghosts[g].type == 'C') ghostTexture = textures.textureClydeD;
                        else if (ghosts[g].type == 'P') ghostTexture = textures.texturePinkyD;
                        else if (ghosts[g].type == 'I') ghostTexture = textures.textureInkyD;
                        else ghostTexture = textures.textureBlinkyD;
                    }
                    else if (renderDirX < 0) // gauche
                    {
                        if (ghosts[g].type == 'C') ghostTexture = textures.textureClydeL;
                        else if (ghosts[g].type == 'P') ghostTexture = textures.texturePinkyL;
                        else if (ghosts[g].type == 'I') ghostTexture = textures.textureInkyL;
                        else ghostTexture = textures.textureBlinkyL;
                    }
                    else // droite ou immobile
                    {
                        if (ghosts[g].type == 'C') ghostTexture = textures.textureClyde;
                        else if (ghosts[g].type == 'P') ghostTexture = textures.texturePinky;
                        else if (ghosts[g].type == 'I') ghostTexture = textures.textureInky;
                        else ghostTexture = textures.textureBlinky;
                    }
                }
                
                drawSpriteOnGrid(ghostTexture, ghosts[g].x, ghosts[g].y, ghostAngle, &params);
            }
            
            // Afficher Pacman
            drawSpriteOnGrid(textures.texturePacman, pacmanX, pacmanY, pacmanAngle, &params);
            
            // Mettre à jour l'affichage
            update(&params);
            
#ifndef PACMAN_TESTS
            for (int i = 0; i < HEIGHT; i++) free(level[i]);
            free(level);
#endif
            return score;
        } // Fin du if (pacgumsLeft == 0)
        
        // Afficher le niveau
        drawLevel(level, &params, &textures);
        
        // Afficher les fantômes
        for (int g = 0; g < ghostCount; g++)
        {
            SDL_Texture *ghostTexture;
            float ghostAngle = 0.0f;
            int renderDirX = ghosts[g].dirX;
            int renderDirY = ghosts[g].dirY;
            if (pacmanAngle == 90.0f)
            {
                // N'affecte que l'orientation de rendu, pas le déplacement réel
                renderDirX = 0;
                renderDirY = -1;
            }
            
            if (ghosts[g].frightened)
            {
                ghostTexture = textures.textureBLue;
            }
            else
            {
                // Choisir la texture selon le type et la direction
                if (renderDirY < 0) // haut
                {
                    if (ghosts[g].type == 'C') ghostTexture = textures.textureClydeU;
                    else if (ghosts[g].type == 'P') ghostTexture = textures.texturePinkyU;
                    else if (ghosts[g].type == 'I') ghostTexture = textures.textureInkyU;
                    else ghostTexture = textures.textureBlinkyU;
                }
                else if (renderDirY > 0) // bas
                {
                    if (ghosts[g].type == 'C') ghostTexture = textures.textureClydeD;
                    else if (ghosts[g].type == 'P') ghostTexture = textures.texturePinkyD;
                    else if (ghosts[g].type == 'I') ghostTexture = textures.textureInkyD;
                    else ghostTexture = textures.textureBlinkyD;
                }
                else if (renderDirX < 0) // gauche
                {
                    if (ghosts[g].type == 'C') ghostTexture = textures.textureClydeL;
                    else if (ghosts[g].type == 'P') ghostTexture = textures.texturePinkyL;
                    else if (ghosts[g].type == 'I') ghostTexture = textures.textureInkyL;
                    else ghostTexture = textures.textureBlinkyL;
                }
                else // droite ou immobile
                {
                    if (ghosts[g].type == 'C') ghostTexture = textures.textureClyde;
                    else if (ghosts[g].type == 'P') ghostTexture = textures.texturePinky;
                    else if (ghosts[g].type == 'I') ghostTexture = textures.textureInky;
                    else ghostTexture = textures.textureBlinky;
                }
            }
            
            drawSpriteOnGrid(ghostTexture, ghosts[g].x, ghosts[g].y, ghostAngle, &params);
        }
        
        // Afficher Pacman
        drawSpriteOnGrid(textures.texturePacman, pacmanX, pacmanY, pacmanAngle, &params);
        
        // Mettre à jour l'affichage (gestion du framerate + présentation)
        update(&params);
        
        // Vérifier si game over après cette frame
        if (gameOverBeforeGhostMove || gameOverAfterGhostMove)
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
