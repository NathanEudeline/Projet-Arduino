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

unsigned long lastShot = 0;
unsigned long lastSpawnTime = 0;
double difficulty = 1;
unsigned long brouillard = 0;

void setup()
{
    // Arduino declaration //
    lcd.begin(16, 2);
    Serial.begin(9600);

    // Création des textures //
    lcd.createChar(PLAYER_MODEL, vaisseau2);
    lcd.createChar(OBSTACLE_MODEL, obstacle);
    lcd.createChar(ENEMY_MODEL, ennemirepos);
    lcd.createChar(POINT_MODEL, humain);
    lcd.createChar(HEART_FULL_MODEL, viepleine);
    lcd.createChar(HEART_EMPTY_MODEL, vievide);
    lcd.createChar(EXPLOSION_MODEL, explo1);
    lcd.createChar(MISSILE_MODEL, tirEn1);

    attachInterrupt(digitalPinToInterrupt(2), playerShoot, FALLING);
    // attachInterrupt(digitalPinToInterrupt(8), playerShoot, FALLING);

    pinMode(9, INPUT);
    pinMode(8, INPUT);
    pinMode(LED_BLEUE, OUTPUT);
}

void loop()
{
    // unsigned long voltage = analogRead(3);

    brouillard = analogRead(3) / 113;
    // // 113;
    // lcd.setCursor(1, 0);
    // lcd.print(voltage);

    if (gameState == ACCUEIL)
    {
        ecranD();
    }

    if (gameState == PLAY)
    {
        // lcd.setCursor(1, 0);
        // lcd.print(list.list[0]->id);
        // lcd.setCursor(1, 1);
        // lcd.print(list.size);
        if (difficulty == 1)
            lcd.clear();
        difficulty += 0.0001;
        // lcd.setCursor(1, 0);
        // lcd.print(difficulty);

        if (digitalRead(8) == LOW)
        {
            player.move(0);
        }
        else if (digitalRead(9) == LOW)
        {
            player.move(1);
        }

        if (player.attaque)
        {
            player.attaque = false;
            lcd.createChar(PLAYER_MODEL, vaisseau1);
            SpaceEntity *missile;
            missile = new SpaceEntity({player.pos.x + 1, player.pos.y}, MISSILE_MODEL, MISSILE_TYPE, false, millis());
            list.addEntity(missile);
        }
        list.updateEntities(&player, millis(), difficulty, lcd);

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

        restart();
        ecranF(player.score);
        player.hp = 3;
        player.score = 0;
        list.size = 0;
        gameState = ACCUEIL;
    }
}

void playerShoot()
{
    if (gameState == ACCUEIL)
    {
        gameState = PLAY;
        srand(millis());
    }
    else if (gameState == PLAY)
    {
        if (lastShot + 4000 < millis())
        {
            lastShot = millis();
            player.shoot();
        }
    }
}

void ecranD()
{
    delay(2000);
    lcd.clear();
    for (byte i = 5; i < 11; i++)
    {
        lcd.setCursor(i - 5, 0);
        lcd.print(" SPACE");
        delay(100);
    }
    for (byte i = 0; i < 11; i++)
    {
        lcd.setCursor(15 - i, 1);
        lcd.print("INVADER ");
        delay(100);
    }
    // lcd.clear();
}

void ecranF(int score)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SCORE :");
    lcd.print(score);
    delay(5000);
}

void restart()
{
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print(" ");
    delay(200);
    lcd.setCursor(3, 0);
    lcd.print("G");
    delay(200);
    lcd.setCursor(4, 1);
    lcd.print("A");
    delay(200);
    lcd.setCursor(5, 0);
    lcd.print("M");
    delay(200);
    lcd.setCursor(6, 1);
    lcd.print("E");
    delay(200);
    lcd.setCursor(7, 0);
    lcd.print(" ");
    lcd.setCursor(8, 0);
    lcd.print("O");
    delay(200);
    lcd.setCursor(9, 1);
    lcd.print("V");
    delay(200);
    lcd.setCursor(10, 0);
    lcd.print("E");
    delay(200);
    lcd.setCursor(11, 1);
    lcd.print("R");
    delay(200);
    lcd.setCursor(12, 0);
    lcd.print("!");
    delay(5000);
    lcd.clear();
}

void renderHUD(Player player)
{

    int nbEmpty = 3 - player.hp;
    for (int i = 0; i < 3; i++)
    {
        lcd.setCursor(13 + i, 0);
        lcd.write((i >= nbEmpty) ? HEART_FULL_MODEL : HEART_EMPTY_MODEL);
    }
    lcd.setCursor(13, 1);
    lcd.print(player.score);
}

void entitySpawner(SpaceList *list) //
{
    if (list->size > 9)
    {
        return;
    }

    Serial.print(list->size);
    Serial.print(" : ");
    for (int i = 0; i < list->size; i++)
    {
        Serial.println(list->list[i]->id);
    }
    Serial.print("\n");

    int rando = rand() % 3;
    SpaceEntity *tmp;
    switch (rando)
    {
    case 0:
        tmp = new SpaceEntity({12, rand() % 2}, OBSTACLE_MODEL, OBSTACLE_TYPE, true, millis());
        break;
    case 1:
        tmp = new SpaceEntity({12, rand() % 2}, ENEMY_MODEL, ENNEMI_TYPE, true, millis());
        break;
    case 2:
        tmp = new SpaceEntity({12, rand() % 2}, POINT_MODEL, POINT_TYPE, true, millis());
        break;
    default:
        break;
    }
    list->addEntity(tmp);
}

void renderFog(int fog)
{
    for (int i = 12; i > 12 - fog; i--)
    {
        lcd.setCursor(i, 0);
        lcd.write(177);
        lcd.setCursor(i, 1);
        lcd.write(177);
    }
}
