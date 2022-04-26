#pragma once

#define KILL_PTS 10
#define HIT_DMG 1

enum GameState
{
    ACCUEIL,
    PLAY,
    DEAD
};

enum EntityType
{
    OBSTACLE_TYPE,
    ENNEMI_TYPE,
    POINT_TYPE,
    MISSILE_TYPE,
    EXPLOSION_TYPE
};

enum ModelId
{
    PLAYER_MODEL,
    OBSTACLE_MODEL,
    ENEMY_MODEL,
    POINT_MODEL,
    HEART_FULL_MODEL,
    HEART_EMPTY_MODEL,
    EXPLOSION_MODEL,
    MISSILE_MODEL
};
