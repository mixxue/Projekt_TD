#include "Enemy.h"
#include <iostream>
#include <cmath>
#include <algorithm>

float distance(Vector2 a, Vector2 b) {
    return std::sqrt(
        (a.x - b.x)*(a.x - b.x) +
        (a.y - b.y)*(a.y - b.y)
    );
}

Enemy::Enemy(float x, float y) {
    position = {x,y};
    hp = 200;
    baseSpeed = 40;
    currentSpeed = baseSpeed;
    alive = true;
}

void Enemy::takeDamage(float dmg) {

    if (!alive) return;

    hp -= dmg;

    std::cout << "HP: " << hp << "\n";

    if (hp <= 0) {
        alive = false;
        hp = 0;
        std::cout << "Enemy Dead\n";
    }
}

void Enemy::update(float dt) {

    if (!alive) return;

    currentSpeed = baseSpeed;

    for (auto& ef : effects) {

        ef.duration -= dt;

        if (ef.type == BURN)
            takeDamage(ef.value * dt);

        if (ef.type == SLOW)
            currentSpeed = baseSpeed * (1 - ef.value);

        if (ef.type == STUN)
            currentSpeed = 0;
    }

    effects.erase(
        std::remove_if(
            effects.begin(),
            effects.end(),
            [](StatusEffect& e){
                return e.duration <= 0;
            }),
        effects.end()
    );

    position.x += currentSpeed * dt;
}
