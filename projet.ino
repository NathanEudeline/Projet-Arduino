#include <LiquidCrystal.h>
#include "entity.h"
#include "game.h"
#include "structs.h"
#include "texture.h"

GameState gameState = PLAY;

LiquidCrystal lcd(15, 14, 4, 5, 6, 7);

void show(Entity entity);
void update();

void setup()
{
    lcd.begin(16, 2);
    lcd.createChar(0, vaisseau);
    lcd.createChar(1, obstacle);
    attachInterrupt(digitalPinToInterrupt(2), movePlayer, FALLING);
}

Player player = Player({0, 0}, 0, 100, 0);
ObstacleIndestructible obin = ObstacleIndestructible({8, 0}, 1);
ObstacleAgressif obag = ObstacleAgressif({10, 1}, 1);
// SpaceList spaceList = SpaceList();
// spaceList.addEntity(aa);

void loop()
{
    if (gameState == PLAY)
    {
        show(player);
        show(obin);
        show(obag);
    }
}

void movePlayer()
{
    player.move();
}

void show(Entity entity)
{
    if (entity.previousPos.x != entity.pos.x || entity.previousPos.y != entity.pos.y) // Si on a bougé depuis le dernier tick
    {
        // On clear l'ancienne pos
        lcd.setCursor(entity.previousPos.x, entity.previousPos.y);
        lcd.print(' ');
    }

    // On affiche la nouvelle
    lcd.setCursor(entity.pos.x, entity.pos.y);
    lcd.write(entity.modelId);
}

void update()
{
}