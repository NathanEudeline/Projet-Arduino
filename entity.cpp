#include "entity.h"
#include "structs.h"

void Player::move()
{
    this->previousPos = this->pos; // on stocke la pos précédente avant de bouger
    this->pos.y = (this->pos.y == 1) ? 0 : 1;
}

void Player::toggleAttack()
{
    this->attaque = !this->attaque;
}

// void SpaceList::addEntity(SpaceEntity entity)
// {
//     this->list[this->size] = realloc(this->list, sizeof(this->list) + sizeof(entity));
//     this->list[this->size] = entity;

//     this->size++;
// }

// void SpaceList::removeEntity(SpaceEntity entity)
// {
//     for (int i = 0; i < this->size; i++)
//     {
//         if (this->list[i].id == entity.id)
//         {
//             if (i == this->size - 1) // Derniere pos
//             {
//                 this->size--;
//             }
//             else
//             {
//                 for (int j = i; j < this->size; j++)
//                 {
//                     this->list[j] = this->list[j + 1];
//                 }

//                 this->size--;
//             }
//             return;
//         }
//     }
// }