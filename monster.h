#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

struct Vector2 {
    float x, y;
};

float distance(Vector2 a, Vector2 b);

enum StatusType {
    BURN,
    SLOW,
    STUN
};

enum ElementType {
    ELEMENT_FIRE,
    ELEMENT_WATER,
    ELEMENT_LIGHTNING,
    ELEMENT_WIND,
    ELEMENT_EARTH,
    ELEMENT_LIGHT
};

struct StatusEffect {
    StatusType type;
    ElementType element;
    float duration;
    float value;
};

class Enemy {
public:
    Vector2 position;
    float hp;
    float baseSpeed;
    float currentSpeed;
    bool alive;

    std::vector<StatusEffect> effects;

    Enemy(float x, float y);

    void takeDamage(float dmg);
    void update(float dt);
};

#endif
