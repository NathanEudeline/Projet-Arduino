#include <LiquidCrystal.h>
#include <stdlib.h>
#include "game.h"
#include "entity.h"
#include "structs.h"
#include "texture.h"

#define LED_BLEUE 3

void renderMenu();
void renderOver();
void renderHUD(Player player);
void entitySpawner(SpaceList *list);

GameState gameState = ACCUEIL;

LiquidCrystal lcd(15, 14, 4, 5, 6, 7);

Player player = Player({0, 0}, 0, 3);
SpaceList list = SpaceList();

unsigned long lastSpawnTime = 0;
double difficulty = 1;
int brouillard = 0;

void setup()
{
    // Arduino declaration //
    lcd.begin(16, 2);

    // Création des textures //
    lcd.createChar(PLAYER_MODEL, vaisseau0);
    lcd.createChar(OBSTACLE_MODEL, obstacle);
    lcd.createChar(ENEMY_MODEL, ennemirepos);
    lcd.createChar(POINT_MODEL, humain);
    lcd.createChar(HEART_FULL_MODEL, viepleine);
    lcd.createChar(HEART_EMPTY_MODEL, vievide);
    lcd.createChar(EXPLOSION_MODEL, explo1);
    lcd.createChar(MISSILE_MODEL, tirEn1);

    attachInterrupt(digitalPinToInterrupt(2), movePlayer, FALLING);
    attachInterrupt(digitalPinToInterrupt(1), playerShoot, FALLING);

    pinMode(LED_BLEUE, OUTPUT);
}

void loop()
{
    brouillard = analogRead(3) / 113;
    if (gameState == ACCUEIL)
    {
        renderMenu();
    }

    if (gameState == PLAY)
    {
        difficulty += 0.01;
        if (player.attaque)
        {
            player.attaque = false;
            list.addEntity(&SpaceEntity({player.pos.x + 1, player.pos.y}, MISSILE_MODEL, MISSILE_TYPE, false));
        }
        list.updateEntities(&player, millis(), difficulty);

        if (player.hp <= 1)
        {
            digitalWrite(LED_BLEUE, HIGH);
            if (player.hp <= 0)
                gameState = DEAD;
        }
        else
        {
            digitalWrite(LED_BLEUE, LOW);
        }

        player.render(lcd);
        list.renderEntities(lcd);
        renderFog(brouillard);
        renderHUD(player);

        if (lastSpawnTime + 4000 < millis())
        {
            lastSpawnTime = millis();
            entitySpawner(&list);
        }
    }

    if (gameState == DEAD)
    {
        renderOver();
    }
}

void movePlayer()
{
    if (gameState == ACCUEIL)
    {
        gameState = PLAY;
        srand(millis());
    }
    else if (gameState == PLAY)
    {
        player.move();
    }
    else if (gameState == DEAD)
    {
        gameState = ACCUEIL;
    }
}

void playerShoot()
{
    player.shoot();
}

void renderMenu()
{
    lcd.clear();
    char text[4] = {'P', 'L', 'A', 'Y'};

    for (int i = 0; i < 4; i++)
    {
        lcd.setCursor(i, 0);
        lcd.print(text[i]);
        delay(200);
    }

    lcd.setCursor(5, 1);
    lcd.write(PLAYER_MODEL);
}

void renderOver()
{
    lcd.clear();
    lcd.print("Miskin");
}

void renderHUD(Player player)
{
    int lastHp = 0, lastScore = 0;
    if (player.hp != lastHp)
    {
        int nbEmpty = 3 - player.hp;
        for (int i = 0; i < 3; i++)
        {
            lcd.setCursor(13 + i, 0);
            lcd.print((i <= nbEmpty) ? HEART_FULL_MODEL : HEART_EMPTY_MODEL);
        }

        lastHp = player.hp;
    }
    if (player.score != lastScore)
    {
        lcd.setCursor(13, 1);
        lcd.print(player.score);

        lastScore = player.score;
    }
}

void entitySpawner(SpaceList *list)
{
    int rando = rand() % 3;
    SpaceEntity newEntity = SpaceEntity({12, rand() % 2}, OBSTACLE_MODEL, OBSTACLE_TYPE, true);
    switch (rando)
    {
    case 0:
        newEntity = SpaceEntity({12, rand() % 2}, OBSTACLE_MODEL, OBSTACLE_TYPE, true);
        break;
    case 1:
        newEntity = SpaceEntity({12, rand() % 2}, ENEMY_MODEL, ENNEMI_TYPE, true);
        break;
    case 2:
        newEntity = SpaceEntity({12, rand() % 2}, POINT_MODEL, POINT_TYPE, true);
        break;
    default:
        break;
    }
    list->addEntity(&newEntity);
}

void renderFog(int fog)
{
    for (int i = 12; i > 12 - fog; i--)
    {
        lcd.setCursor(i, 0);
        lcd.print(177);
        lcd.setCursor(i, 1);
        lcd.print(177);
    }
}
