#pragma once

#include "entities.h"

// Constantes pour le comportement des fantômes
#define INKY_RANDOMNESS 3
#define BLINKY_RANDOMNESS 5

// Obtenir les directions potentielles pour un fantôme (sans faire demi-tour)
Coord *getPotentialDirection(const char **level, const MovingEntity *ghost, int *nbDir);

// Déplacement spécifique de chaque fantôme
void clydeMove(const char **level, MovingEntity *ghost, const MovingEntity *pacman, int *nbDir, Coord *potentialDirs);
void pinkyMove(const char **level, MovingEntity *ghost, const MovingEntity *pacman, int *nbDir, Coord *potentialDirs);
void inkyMove(const char **level, MovingEntity *ghost, const MovingEntity *pacman, int *nbDir, Coord *potentialDirs);
void blinkyMove(const char **level, MovingEntity *ghost, const MovingEntity *pacman, int *nbDir, Coord *potentialDirs);

// Déplacement général d'un fantôme
void ghostMove(const char **level, MovingEntity *ghost, const MovingEntity *pacman);

// Vérifier s'il y a une ligne de vue directe entre deux entités
int hasLineOfSight(const char **level, const MovingEntity *entity1, const MovingEntity *entity2);

// Trouver la prochaine intersection que rencontrera Pacman
Coord getPacmanNextIntersec(const char **level, MovingEntity pacman, int depth);
