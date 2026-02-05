#include "ghosts.h"
#include "framework.h"
#include <stdlib.h>
#include <math.h>

// Obtenir les directions potentielles pour un fantôme (sans faire demi-tour)
Coord *getPotentialDirection(const char **level, const MovingEntity *ghost, int *nbDir)
{
    *nbDir = 0;
    
    // Tableau des 4 directions possibles : droite, haut, gauche, bas
    int directions[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    
    // Compter les directions valides
    for (int d = 0; d < 4; d++)
    {
        int dx = directions[d][0];
        int dy = directions[d][1];
        
        // Pas de demi-tour (sauf si on est immobile)
        if (ghost->dir.x != 0 || ghost->dir.y != 0)
        {
            if (dx == -ghost->dir.x && dy == -ghost->dir.y)
                continue;
        }
        
        int testX = ghost->pos.x + dx;
        int testY = ghost->pos.y + dy;
        
        // Wraparound
        if (testX < 0) testX = WIDTH - 1;
        if (testX >= WIDTH) testX = 0;
        if (testY < 0) testY = HEIGHT - 1;
        if (testY >= HEIGHT) testY = 0;
        
        // Vérifier si ce n'est pas un mur
        if (level[testY][testX] != 'H')
        {
            (*nbDir)++;
        }
    }
    
    // Allouer le tableau
    Coord *potentialDirs = (Coord *)malloc(sizeof(Coord) * (*nbDir));
    int idx = 0;
    
    // Remplir le tableau
    for (int d = 0; d < 4; d++)
    {
        int dx = directions[d][0];
        int dy = directions[d][1];
        
        // Pas de demi-tour (sauf si on est immobile)
        if (ghost->dir.x != 0 || ghost->dir.y != 0)
        {
            if (dx == -ghost->dir.x && dy == -ghost->dir.y)
                continue;
        }
        
        int testX = ghost->pos.x + dx;
        int testY = ghost->pos.y + dy;
        
        // Wraparound
        if (testX < 0) testX = WIDTH - 1;
        if (testX >= WIDTH) testX = 0;
        if (testY < 0) testY = HEIGHT - 1;
        if (testY >= HEIGHT) testY = 0;
        
        // Vérifier si ce n'est pas un mur
        if (level[testY][testX] != 'H')
        {
            potentialDirs[idx].x = dx;
            potentialDirs[idx].y = dy;
            idx++;
        }
    }
    
    return potentialDirs;
}

// Déplacement aléatoire de Clyde
void clydeMove(const char **level, MovingEntity *ghost, const MovingEntity *pacman, int *nbDir, Coord *potentialDirs)
{
    (void)level;    // Paramètre non utilisé
    (void)pacman;   // Paramètre non utilisé
    
    if (*nbDir == 0)
    {
        // Cul-de-sac : demi-tour
        ghost->dir.x = -ghost->dir.x;
        ghost->dir.y = -ghost->dir.y;
    }
    else if (*nbDir == 1)
    {
        // Une seule direction : avancer
        ghost->dir.x = potentialDirs[0].x;
        ghost->dir.y = potentialDirs[0].y;
    }
    else
    {
        // Plusieurs directions : choisir aléatoirement
        int choice = getRandomNumber() % (*nbDir);
        ghost->dir.x = potentialDirs[choice].x;
        ghost->dir.y = potentialDirs[choice].y;
    }
}

// Vérifier s'il y a une ligne de vue directe entre deux entités
int hasLineOfSight(const char **level, const MovingEntity *entity1, const MovingEntity *entity2)
{
    // Vérifier si sur la même ligne
    if (entity1->pos.y == entity2->pos.y)
    {
        int minX = entity1->pos.x < entity2->pos.x ? entity1->pos.x : entity2->pos.x;
        int maxX = entity1->pos.x > entity2->pos.x ? entity1->pos.x : entity2->pos.x;
        
        for (int x = minX + 1; x < maxX; x++)
        {
            if (level[entity1->pos.y][x] == 'H')
                return 0;
        }
        return 1;
    }
    
    // Vérifier si sur la même colonne
    if (entity1->pos.x == entity2->pos.x)
    {
        int minY = entity1->pos.y < entity2->pos.y ? entity1->pos.y : entity2->pos.y;
        int maxY = entity1->pos.y > entity2->pos.y ? entity1->pos.y : entity2->pos.y;
        
        for (int y = minY + 1; y < maxY; y++)
        {
            if (level[y][entity1->pos.x] == 'H')
                return 0;
        }
        return 1;
    }
    
    return 0;
}

// Déplacement de Pinky : suit Pacman s'il le voit
void pinkyMove(const char **level, MovingEntity *ghost, const MovingEntity *pacman, int *nbDir, Coord *potentialDirs)
{
    // Vérifier s'il y a une ligne de vue
    if (hasLineOfSight(level, ghost, pacman))
    {
        // Suivre Pacman
        if (*nbDir == 0)
        {
            // Cul-de-sac : demi-tour
            ghost->dir.x = -ghost->dir.x;
            ghost->dir.y = -ghost->dir.y;
        }
        else if (*nbDir == 1)
        {
            // Une seule direction : avancer
            ghost->dir.x = potentialDirs[0].x;
            ghost->dir.y = potentialDirs[0].y;
        }
        else
        {
            // Choisir la direction vers Pacman
            int bestIdx = 0;
            
            // Priorité : direction vers Pacman
            if (pacman->pos.y < ghost->pos.y)
            {
                // Pacman est en haut
                for (int i = 0; i < *nbDir; i++)
                {
                    if (potentialDirs[i].x == 0 && potentialDirs[i].y == -1)
                    {
                        bestIdx = i;
                        break;
                    }
                }
            }
            else if (pacman->pos.y > ghost->pos.y)
            {
                // Pacman est en bas
                for (int i = 0; i < *nbDir; i++)
                {
                    if (potentialDirs[i].x == 0 && potentialDirs[i].y == 1)
                    {
                        bestIdx = i;
                        break;
                    }
                }
            }
            else if (pacman->pos.x < ghost->pos.x)
            {
                // Pacman est à gauche
                for (int i = 0; i < *nbDir; i++)
                {
                    if (potentialDirs[i].x == -1 && potentialDirs[i].y == 0)
                    {
                        bestIdx = i;
                        break;
                    }
                }
            }
            else if (pacman->pos.x > ghost->pos.x)
            {
                // Pacman est à droite
                for (int i = 0; i < *nbDir; i++)
                {
                    if (potentialDirs[i].x == 1 && potentialDirs[i].y == 0)
                    {
                        bestIdx = i;
                        break;
                    }
                }
            }
            
            ghost->dir.x = potentialDirs[bestIdx].x;
            ghost->dir.y = potentialDirs[bestIdx].y;
        }
    }
    else
    {
        // Pas de ligne de vue : se comporter comme Clyde
        clydeMove(level, ghost, pacman, nbDir, potentialDirs);
    }
}

// Déplacement d'Inky : suit Pacman intelligemment
void inkyMove(const char **level, MovingEntity *ghost, const MovingEntity *pacman, int *nbDir, Coord *potentialDirs)
{
    // Hasard pour rendre Inky moins parfait
    if (getRandomNumber() % INKY_RANDOMNESS == 0)
    {
        clydeMove(level, ghost, pacman, nbDir, potentialDirs);
        return;
    }
    
    if (*nbDir == 0)
    {
        // Cul-de-sac : demi-tour
        ghost->dir.x = -ghost->dir.x;
        ghost->dir.y = -ghost->dir.y;
    }
    else if (*nbDir == 1)
    {
        // Une seule direction : avancer
        ghost->dir.x = potentialDirs[0].x;
        ghost->dir.y = potentialDirs[0].y;
    }
    else
    {
        // Calculer les distances
        int diffX = abs(pacman->pos.x - ghost->pos.x);
        int diffY = abs(pacman->pos.y - ghost->pos.y);
        
        // Déterminer la direction à privilégier
        int targetDirX = 0, targetDirY = 0;
        
        if (diffX > diffY)
        {
            // Réduire la distance horizontale
            targetDirX = (pacman->pos.x > ghost->pos.x) ? 1 : -1;
        }
        else if (diffY > diffX)
        {
            // Réduire la distance verticale
            targetDirY = (pacman->pos.y > ghost->pos.y) ? 1 : -1;
        }
        
        // Chercher la direction cible dans les directions possibles
        int bestIdx = 0;
        int found = 0;
        
        for (int i = 0; i < *nbDir; i++)
        {
            if (potentialDirs[i].x == targetDirX && potentialDirs[i].y == targetDirY)
            {
                bestIdx = i;
                found = 1;
                break;
            }
        }
        
        // Si pas trouvé, essayer l'autre direction
        if (!found)
        {
            if (targetDirX != 0)
            {
                targetDirY = (pacman->pos.y > ghost->pos.y) ? 1 : -1;
                targetDirX = 0;
            }
            else if (targetDirY != 0)
            {
                targetDirX = (pacman->pos.x > ghost->pos.x) ? 1 : -1;
                targetDirY = 0;
            }
            
            for (int i = 0; i < *nbDir; i++)
            {
                if (potentialDirs[i].x == targetDirX && potentialDirs[i].y == targetDirY)
                {
                    bestIdx = i;
                    found = 1;
                    break;
                }
            }
        }
        
        // Si toujours pas trouvé, prendre n'importe quelle direction
        if (!found)
        {
            bestIdx = getRandomNumber() % (*nbDir);
        }
        
        ghost->dir.x = potentialDirs[bestIdx].x;
        ghost->dir.y = potentialDirs[bestIdx].y;
    }
}

// Trouver la prochaine intersection que rencontrera Pacman (récursif)
Coord getPacmanNextIntersec(const char **level, MovingEntity pacman, int depth)
{
    // Cas d'arrêt : Pacman ne bouge pas ou profondeur max atteinte
    if (pacman.dir.x == 0 && pacman.dir.y == 0)
    {
        return pacman.pos;
    }
    
    // Limite de profondeur pour éviter le stack overflow
    if (depth > 100)
    {
        return pacman.pos;
    }
    
    // Obtenir les directions possibles pour Pacman
    int nbDir;
    Coord *potentialDirs = getPotentialDirection(level, &pacman, &nbDir);
    
    // Cas d'arrêt : c'est une intersection (plus d'une direction possible, sans compter le retour)
    if (nbDir >= 2)
    {
        free(potentialDirs);
        return pacman.pos;
    }
    
    // Avancer Pacman
    pacman.pos.x += pacman.dir.x;
    pacman.pos.y += pacman.dir.y;
    
    // Wraparound
    if (pacman.pos.x < 0) pacman.pos.x = WIDTH - 1;
    if (pacman.pos.x >= WIDTH) pacman.pos.x = 0;
    if (pacman.pos.y < 0) pacman.pos.y = HEIGHT - 1;
    if (pacman.pos.y >= HEIGHT) pacman.pos.y = 0;
    
    free(potentialDirs);
    
    // Appel récursif
    return getPacmanNextIntersec(level, pacman, depth + 1);
}

// Déplacement de Blinky : anticipe la prochaine intersection de Pacman
void blinkyMove(const char **level, MovingEntity *ghost, const MovingEntity *pacman, int *nbDir, Coord *potentialDirs)
{
    // Hasard pour rendre Blinky moins parfait
    if (getRandomNumber() % BLINKY_RANDOMNESS == 0)
    {
        clydeMove(level, ghost, pacman, nbDir, potentialDirs);
        return;
    }
    
    // Trouver la prochaine intersection de Pacman
    MovingEntity pacmanCopy = *pacman;
    Coord targetIntersec = getPacmanNextIntersec(level, pacmanCopy, 0);
    
    // Créer une entité temporaire avec la position cible
    MovingEntity target = *pacman;
    target.pos = targetIntersec;
    
    // Utiliser la logique d'Inky pour se diriger vers cette intersection
    // (sans le hasard)
    if (*nbDir == 0)
    {
        // Cul-de-sac : demi-tour
        ghost->dir.x = -ghost->dir.x;
        ghost->dir.y = -ghost->dir.y;
    }
    else if (*nbDir == 1)
    {
        // Une seule direction : avancer
        ghost->dir.x = potentialDirs[0].x;
        ghost->dir.y = potentialDirs[0].y;
    }
    else
    {
        // Calculer les distances vers l'intersection cible
        int diffX = abs(targetIntersec.x - ghost->pos.x);
        int diffY = abs(targetIntersec.y - ghost->pos.y);
        
        // Déterminer la direction à privilégier
        int targetDirX = 0, targetDirY = 0;
        
        if (diffX > diffY)
        {
            // Réduire la distance horizontale
            targetDirX = (targetIntersec.x > ghost->pos.x) ? 1 : -1;
        }
        else if (diffY > diffX)
        {
            // Réduire la distance verticale
            targetDirY = (targetIntersec.y > ghost->pos.y) ? 1 : -1;
        }
        
        // Chercher la direction cible dans les directions possibles
        int bestIdx = 0;
        int found = 0;
        
        for (int i = 0; i < *nbDir; i++)
        {
            if (potentialDirs[i].x == targetDirX && potentialDirs[i].y == targetDirY)
            {
                bestIdx = i;
                found = 1;
                break;
            }
        }
        
        // Si pas trouvé, essayer l'autre direction
        if (!found)
        {
            if (targetDirX != 0)
            {
                targetDirY = (targetIntersec.y > ghost->pos.y) ? 1 : -1;
                targetDirX = 0;
            }
            else if (targetDirY != 0)
            {
                targetDirX = (targetIntersec.x > ghost->pos.x) ? 1 : -1;
                targetDirY = 0;
            }
            
            for (int i = 0; i < *nbDir; i++)
            {
                if (potentialDirs[i].x == targetDirX && potentialDirs[i].y == targetDirY)
                {
                    bestIdx = i;
                    found = 1;
                    break;
                }
            }
        }
        
        // Si toujours pas trouvé, prendre n'importe quelle direction
        if (!found)
        {
            bestIdx = getRandomNumber() % (*nbDir);
        }
        
        ghost->dir.x = potentialDirs[bestIdx].x;
        ghost->dir.y = potentialDirs[bestIdx].y;
    }
}

// Déplacement général d'un fantôme
void ghostMove(const char **level, MovingEntity *ghost, const MovingEntity *pacman)
{
    // Obtenir les directions potentielles
    int nbDir;
    Coord *potentialDirs = getPotentialDirection(level, ghost, &nbDir);
    
    // Si le fantôme est effrayé, il se comporte comme Clyde (aléatoire)
    if (ghost->frightened)
    {
        clydeMove(level, ghost, pacman, &nbDir, potentialDirs);
    }
    else
    {
        // Appeler la fonction spécifique selon le type de fantôme
        switch (ghost->name)
        {
            case CLYDE:
                clydeMove(level, ghost, pacman, &nbDir, potentialDirs);
                break;
            case PINKY:
                pinkyMove(level, ghost, pacman, &nbDir, potentialDirs);
                break;
            case INKY:
                inkyMove(level, ghost, pacman, &nbDir, potentialDirs);
                break;
            case BLINKY:
                blinkyMove(level, ghost, pacman, &nbDir, potentialDirs);
                break;
            default:
                clydeMove(level, ghost, pacman, &nbDir, potentialDirs);
                break;
        }
    }
    
    // Appliquer le déplacement
    ghost->pos.x += ghost->dir.x;
    ghost->pos.y += ghost->dir.y;
    
    // Wraparound
    if (ghost->pos.x < 0) ghost->pos.x = WIDTH - 1;
    if (ghost->pos.x >= WIDTH) ghost->pos.x = 0;
    if (ghost->pos.y < 0) ghost->pos.y = HEIGHT - 1;
    if (ghost->pos.y >= HEIGHT) ghost->pos.y = 0;
    
    free(potentialDirs);
}
