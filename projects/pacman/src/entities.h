#pragma once

// Structure pour les coordonnées
typedef struct Coord Coord;
struct Coord
{
    int x;
    int y;
};

// Enum pour différencier les entités
typedef enum EntityName EntityName;
enum EntityName
{
    PACMAN,
    BLINKY,
    CLYDE,
    INKY,
    PINKY
};

// Structure pour une entité mobile (Pacman ou fantôme)
typedef struct MovingEntity MovingEntity;
struct MovingEntity
{
    Coord pos;          // Position actuelle
    Coord dir;          // Direction actuelle
    Coord originalPos;  // Position de départ
    EntityName name;    // Nom de l'entité
    int frightened;     // 1 si le fantôme est bleu (effrayé)
    float angle;        // Angle pour l'affichage
};

// Initialisation d'une entité mobile
void initEntity(MovingEntity *entity, int x, int y, EntityName name);
