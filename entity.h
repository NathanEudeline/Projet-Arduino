#pragma once
#include "structs.h"

class Entity
{
public:
    vec2 pos, previousPos;
    short modelId;

    // Entity(vec2 pos, short modelId) // Inutile je crois
    // {
    //     this->pos = pos;
    //     this->modelId = model;
    // }
};

class SpaceEntity : public Entity // Contient les entités qui vont vers le joueur
{
public:
    SpaceEntity();
    ~SpaceEntity();
};

class Player : public Entity
{
public:
    int score, hp;
    bool attaque = false;

    Player(vec2 pos, int score, int hp, short modelId)
    {
        this->pos = pos;
        this->score = score;
        this->hp = hp;
        this->attaque = attaque;
        this->modelId = modelId;
    }

    void move();
    void toggleAttack();
};

class ObstacleIndestructible : public SpaceEntity
{
public:
    ObstacleIndestructible(vec2 pos)
    {
        this->pos = pos;
    }
};

class ObstacleAgressif : public SpaceEntity
{
public:
    bool attaque = false;
    ObstacleAgressif(vec2 pos, bool attaque)
    {
        this->pos = pos;
        this->attaque = attaque;
    }
};

class SpaceList // Contient les SpaceEntity actives
{
private:
    int size;
    SpaceEntity list[5];

public:
    SpaceList();

    void addEntity(SpaceEntity entity);

    void removeEntity(SpaceEntity entity);
};

SpaceList::SpaceList()
{
    this->size = 0;
}
