#include "entities.h"
#include "framework.h"

// Initialisation d'une entité mobile
void initEntity(MovingEntity *entity, int x, int y, EntityName name)
{
    entity->pos.x = x;
    entity->pos.y = y;
    entity->dir.x = 0;
    entity->dir.y = 0;
    entity->originalPos.x = x;
    entity->originalPos.y = y;
    entity->name = name;
    entity->frightened = 0;
    entity->angle = 0.0f;
}
