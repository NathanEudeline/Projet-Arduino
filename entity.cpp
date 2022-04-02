#include "entity.h"
#include "structs.h"

void Player::move()
{
    this->previousPos = this->pos; // on stocke la pos précédente avant de bouger

    if (this->pos.y == 1)
    {
        this->pos.y = 0;
    }
    else
    {
        this->pos.y = 1;
    }
}

void Player::toggleAttack()
{
    this->attaque = !this->attaque;
}

void SpaceList::addEntity(SpaceEntity entity)
{
    this->list[this->size] = entity;
}

void SpaceList::removeEntity(SpaceEntity entity)
{
    for (int i = 0; i < 5; i++)
    {
        if (this->list[i] == entity)
        {
            if (i == 4) // Derniere pos
            {
                this->size--;
            }
            else
            {
                for (int j = i; j < 4; j++)
                {
                    this->list[j] = this->list[j + 1]
                }

                this->size--;
            }
            return;
        }
    }
}