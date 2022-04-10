#include <LiquidCrystal.h>
#include "entity.h"
#include "structs.h"

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

void SpaceList::updateEntities(Player player, unsigned long millis)
{
    for (int i = 0; i < this->size; i++)
    {
        SpaceEntity entity = this->list[i];
        entity.update();
    }
}
