#include <LiquidCrystal.h>
#include "entity.h"
#include "game.h"
#include "structs.h"
#include "texture.h"

GameState gameState = PLAY;

LiquidCrystal lcd(15, 14, 4, 5, 6, 7);

Player player = Player({0, 0}, 0, 100);
SpaceEntity obin = SpaceEntity({8, 0}, OBSTACLE_MODEL, OBSTACLE_TYPE, true);
SpaceEntity obag = SpaceEntity({10, 1}, ENNEMI_MODEL, ENNEMI_TYPE, true);
SpaceList list = SpaceList();

void setup()
{
    // Arduino declaration //
    lcd.begin(16, 2);
    lcd.createChar(PLAYER_MODEL, vaisseau0);
    lcd.createChar(OBSTACLE_MODEL, obstacle);
    lcd.createChar(ENNEMI_MODEL, ennemirepos);
    attachInterrupt(digitalPinToInterrupt(2), movePlayer, FALLING);
    attachInterrupt(digitalPinToInterrupt(1), playerShoot, FALLING);

    // Game declaration //
    list.addEntity(obag);
    list.addEntity(obin);
}

void loop()
{
    if (gameState == PLAY)
    {
        if (player.attaque)
        {
            list.addEntity(SpaceEntity({player.pos.x + 1, player.pos.y}, MISSILE_MODEL, MISSILE_TYPE, false));
        }
        list.updateEntities(player, millis());
    }
}

void movePlayer()
{
    player.move();
}

void playerShoot()
{
    player.shoot();
}
