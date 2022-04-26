#include <LiquidCrystal.h>
#include <stdlib.h>
#include "entity.h"

void Entity::render(LiquidCrystal lcd)
{
    if (this->previousPos.x != this->pos.x || this->previousPos.y != this->pos.y) // Si on a bougé depuis le dernier tick
    {
        // On clear l'ancienne pos
        lcd.setCursor(this->previousPos.x, this->previousPos.y);
        lcd.print(' ');
    }

    // On affiche la nouvelle
    lcd.setCursor(this->pos.x, this->pos.y);
    lcd.write(this->modelId);
}

void Player::move()
{
    this->previousPos = this->pos; // on stocke la pos précédente avant de bouger
    this->pos.y = (this->pos.y == 1) ? 0 : 1;
}

void Player::shoot()
{
    this->attaque = true;
}

void SpaceEntity::move()
{
    this->previousPos = this->pos; // on stocke la pos précédente avant de bouger
    this->pos.x += this->direction ? -1 : 1;
}

void SpaceEntity::update(unsigned long millis, double diff)
{
    if (this->type != MISSILE_TYPE && this->lastMove + (rand() % 1000) + 5000 * diff > millis)
    {
        this->move();
        if (this->type == ENNEMI_TYPE && millis % 2 == 0)
        {
            this->attaque = true;
        }
    }
    if (this->type == MISSILE_TYPE && this->lastMove + (rand() % 500) + 3000 > millis)
    {
        this->move();
    }
    this->lastMove = millis;
}

bool SpaceEntity::testCol(Entity entity)
{
    return (this->pos.x == entity.pos.x && this->pos.y == entity.pos.y);
}

void SpaceList::updateEntities(Player *player, unsigned long millis, double diff)
{
    for (int i = 0; i < this->size; i++) // On boucle sur tt les entité du tableau
    {
        SpaceEntity *entity = this->list[i];
        entity->update(millis, diff); // on update l'entité
        if (entity->pos.x < 0)        // On la vire si elle sort du jeu en on continue pas la logique
        {
            this->removeEntity(entity);
            continue;
        }

        if (entity->attaque) // si l'entité a son attaque en true on spawn un missile
        {
            entity->attaque = false;
            this->addEntity(&SpaceEntity({entity->pos.x - 1, entity->pos.y}, MISSILE_MODEL, MISSILE_TYPE, true));
        }
        if (entity->testCol(*player))
        {
            if (entity->type == POINT_TYPE)
            {
                player->score += KILL_PTS;
            }
            else
            {
                player->hp--;
            }
        }

        if (entity->type == MISSILE_TYPE)
        {
            for (int j = 0; j < this->size; j++)
            {
                if (i != j)
                    continue;

                SpaceEntity *entityBis = this->list[j];

                if (entity->testCol(*entityBis))
                {
                    if (entityBis->type != OBSTACLE_TYPE)
                    {
                        this->removeEntity(entity);
                    }
                    else
                    {
                        this->removeEntity(entityBis);
                        this->removeEntity(entity);
                    }
                    break;
                }
            }
        }
    }
}

void SpaceList::renderEntities(LiquidCrystal lcd)
{
    for (int i = 0; i < this->size; i++)
    {
        SpaceEntity *entity = this->list[i];
        entity->render(lcd);
    }
}

void SpaceList::addEntity(SpaceEntity *entity)
{
    this->list[this->size] = entity;
}

void SpaceList::removeEntity(SpaceEntity *entity)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->list[i] == entity)
        {
            if (i == this->size - 1) // Derniere pos
            {
                this->size--;
            }
            else
            {
                for (int j = i; j < this->size; j++)
                {
                    this->list[j] = this->list[j + 1];
                }
                this->size--;
            }
            return;
        }
    }
}