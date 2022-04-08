#pragma once
#include <stdlib.h>
#include "structs.h"

class Entity
{
public:
    vec2 pos, previousPos;
    short modelId;

    explicit Entity(vec2 pos, short modelId)
    {
        this->pos = pos;
        this->previousPos = pos;
        this->modelId = modelId;
    }

    // Entity(vec2 pos, short modelId) // Inutile je crois
    // {
    //     this->pos = pos;
    //     this->modelId = model;
    // }
};

class SpaceEntity : public Entity // Contient les entités qui vont vers le joueur
{
public:
    int id;

    explicit SpaceEntity(vec2 pos, short modelId) : Entity(pos, modelId)
    {
        this->id = rand();
    }
    // SpaceEntity();
    // ~SpaceEntity();
};

class Player : public Entity
{
public:
    int score, hp;
    bool attaque = false;

    Player(vec2 pos, int score, int hp, short modelId) : Entity(pos, modelId)
    {
        this->score = score;
        this->hp = hp;
        this->attaque = attaque;
    }

    void move();
    void toggleAttack();
};

class ObstacleIndestructible : public SpaceEntity
{
public:
    ObstacleIndestructible(vec2 pos, short modelId) : SpaceEntity(pos, modelId)
    {
    }
};

class ObstacleAgressif : public SpaceEntity
{
public:
    bool attaque;

    ObstacleAgressif(vec2 pos, short modelId) : SpaceEntity(pos, modelId)
    {
        this->attaque = false;
    }
};

// class SpaceList // Contient les SpaceEntity actives
// {
// private:
//     int size;
//     void *list;

// public:
//     SpaceList()
//     {
//         this->size = 0;
//     }

//     void addEntity(SpaceEntity entity);

//     void removeEntity(SpaceEntity entity);
// };
