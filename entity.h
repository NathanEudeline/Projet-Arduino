#pragma once
#include <stdlib.h>
#include "structs.h"
#include "game.h"

#define MAX_ENTITY 10

class Entity
{
public:
    vec2 pos, previousPos;
    ModelId modelId;

    explicit Entity(vec2 pos, ModelId modelId)
    {
        this->pos = pos;
        this->previousPos = pos;
        this->modelId = modelId;
    }

    void render(LiquidCrystal lcd);
};

class SpaceEntity : public Entity // Contient les entités qui vont vers le joueur
{
public:
    int id;
    bool direction;
    EntityType type;

    SpaceEntity(vec2 pos, ModelId modelId, EntityType type, bool direction) : Entity(pos, modelId)
    {
        this->id = rand();
        this->direction = direction;
        this->type = type;
    }
    SpaceEntity();

    bool update();
};

class Player : public Entity
{
public:
    int score, hp;
    bool attaque;

    Player(vec2 pos, int score, int hp) : Entity(pos, PLAYER_MODEL)
    {
        this->score = score;
        this->hp = hp;
        this->attaque = false;
    }

    void move();
    void shoot();
};

class SpaceList // Contient les SpaceEntity actives
{
private:
    int size;
    SpaceEntity list[MAX_ENTITY];

public:
    SpaceList()
    {
        this->size = 0;
    }

    void addEntity(SpaceEntity entity);

    void removeEntity(SpaceEntity entity);

    void updateEntities(Player player, unsigned long millis);
};
