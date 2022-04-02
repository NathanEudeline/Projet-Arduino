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
    lcd.createChar(1, vaisseau);
    attachInterrupt(digitalPinToInterrupt(2), movePlayer, FALLING);
}

Player player = Player({0, 0}, 0, 100, 1);
ObstacleIndestructible aa = ObstacleIndestructible({8, 0});
SpaceList spaceList = SpaceList();
spaceList.addEntity(aa);

void loop()
{
    if (gameState == PLAY)
    {
        show(player);
    }
}

void movePlayer()
{
    player.move();
}

void show(Entity entity)
{
    // On clear l'ancienne pos
    lcd.setCursor(entity.previousPos.x, entity.previousPos.y);
    lcd.print(' ');

    // On affiche la nouvelle
    lcd.setCursor(entity.pos.x, entity.pos.y);
    lcd.write(entity.modelId);
}

void update()
{
}