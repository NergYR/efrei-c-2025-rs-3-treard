#include "game.h"
#include "framework.h"

// Manger une Pacgum si présente
void eat(char **level, int x, int y)
{
    if (level[y][x] == '.' || level[y][x] == 'G')
    {
        level[y][x] = ' ';
    }
}

// Vérifier la victoire (plus de Pacgums)
int win(const char **level)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (level[i][j] == '.' || level[i][j] == 'G')
            {
                return 0; // Encore des Pacgums
            }
        }
    }
    return 1; // Victoire!
}

// Vérifier collision entre deux entités
int checkCollision(const MovingEntity *entity1, const MovingEntity *entity2)
{
    return (entity1->pos.x == entity2->pos.x && entity1->pos.y == entity2->pos.y);
}

// Vérifier collision avec croisement (deux entités qui échangent leur position)
int checkCrossCollision(const MovingEntity *entity1, const MovingEntity *entity2, 
                        const MovingEntity *prevEntity1, const MovingEntity *prevEntity2)
{
    // Collision normale
    if (checkCollision(entity1, entity2))
        return 1;
    
    // Collision par croisement (inversion de position)
    if (entity1->pos.x == prevEntity2->pos.x && entity1->pos.y == prevEntity2->pos.y &&
        entity2->pos.x == prevEntity1->pos.x && entity2->pos.y == prevEntity1->pos.y)
    {
        return 1;
    }
    
    return 0;
}

// Réinitialiser un fantôme à sa position de départ
void resetGhostToStart(MovingEntity *ghost)
{
    ghost->pos.x = ghost->originalPos.x;
    ghost->pos.y = ghost->originalPos.y;
    ghost->dir.x = 0;
    ghost->dir.y = 0;
    ghost->frightened = 0;
}

// Rendre tous les fantômes effrayés
void frightenAllGhosts(MovingEntity *ghosts, int ghostCount)
{
    for (int i = 0; i < ghostCount; i++)
    {
        ghosts[i].frightened = 1;
    }
}

// Faire faire demi-tour à tous les fantômes
void turnAllGhostsAround(MovingEntity *ghosts, int ghostCount)
{
    for (int i = 0; i < ghostCount; i++)
    {
        ghosts[i].dir.x = -ghosts[i].dir.x;
        ghosts[i].dir.y = -ghosts[i].dir.y;
    }
}
