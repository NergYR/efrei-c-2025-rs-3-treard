#pragma once

#include "entities.h"

// Fonctions utilitaires pour le jeu

// Manger une Pacgum si présente
void eat(char **level, int x, int y);

// Vérifier la victoire (plus de Pacgums)
int win(const char **level);

// Vérifier collision entre deux entités
int checkCollision(const MovingEntity *entity1, const MovingEntity *entity2);

// Vérifier collision avec croisement (deux entités qui échangent leur position)
int checkCrossCollision(const MovingEntity *entity1, const MovingEntity *entity2, 
                        const MovingEntity *prevEntity1, const MovingEntity *prevEntity2);

// Réinitialiser un fantôme à sa position de départ
void resetGhostToStart(MovingEntity *ghost);

// Rendre tous les fantômes effrayés
void frightenAllGhosts(MovingEntity *ghosts, int ghostCount);

// Faire faire demi-tour à tous les fantômes
void turnAllGhostsAround(MovingEntity *ghosts, int ghostCount);
