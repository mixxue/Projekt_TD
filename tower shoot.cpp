#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

//////////////////////////////////////////////////////////////
// Utility

struct Vector2 {
    float x, y;
};

float distance(Vector2 a, Vector2 b) {
    return std::sqrt(
        (a.x - b.x)*(a.x - b.x) +
        (a.y - b.y)*(a.y - b.y)
    );
}

//////////////////////////////////////////////////////////////
// Element & Status

enum StatusType {
    BURN,
    SLOW,
    STUN
};

enum ElementType {
    ELEMENT_NONE,
    ELEMENT_FIRE,
    ELEMENT_ICE,
    ELEMENT_LIGHTNING,
    ELEMENT_WIND
};

struct StatusEffect {
    StatusType type;
    ElementType element;
    float duration;
    float value;
};

//////////////////////////////////////////////////////////////
// Enemy

class Enemy {
public:
    Vector2 position;
    float hp;
    float baseSpeed;
    float currentSpeed;
    bool alive;

    std::vector<StatusEffect> effects;

    Enemy(float x, float y) {
        position = {x, y};
        hp = 200;
        baseSpeed = 40;
        currentSpeed = baseSpeed;
        alive = true;
    }

    void takeDamage(float dmg) {
        hp -= dmg;
        std::cout << "Enemy HP: " << hp << "\n";
        if (hp <= 0) {
            alive = false;
            std::cout << "Enemy Dead\n";
        }
    }

    bool hasElement(ElementType e) {
        for (auto& ef : effects)
            if (ef.element == e)
                return true;
        return false;
    }

    void checkElementCombo(StatusEffect newEffect,
                           std::vector<Enemy*>& enemies) {

        // 🔥 + ❄ = Explosion
        if (newEffect.element == ELEMENT_FIRE &&
            hasElement(ELEMENT_ICE)) {

            std::cout << "🔥❄ COMBO: Explosion!\n";

            for (auto enemy : enemies) {
                if (distance(position, enemy->position) < 100) {
                    enemy->takeDamage(40);
                }
            }
        }

        // ⚡ + ❄ = Super Stun
        if (newEffect.element == ELEMENT_LIGHTNING &&
            hasElement(ELEMENT_ICE)) {

            std::cout << "⚡❄ COMBO: Super Stun!\n";

            StatusEffect stun;
            stun.type = STUN;
            stun.element = ELEMENT_NONE;
            stun.duration = 3.0f;
            stun.value = 0;

            effects.push_back(stun);
        }

        // 🔥 + 🌪 = Fire Spread
        if (newEffect.element == ELEMENT_FIRE &&
            hasElement(ELEMENT_WIND)) {

            std::cout << "🔥🌪 COMBO: Fire Spread!\n";

            for (auto enemy : enemies) {
                if (distance(position, enemy->position) < 120) {

                    StatusEffect burn;
                    burn.type = BURN;
                    burn.element = ELEMENT_FIRE;
                    burn.duration = 2.0f;
                    burn.value = 15;

                    enemy->effects.push_back(burn);
                }
            }
        }
    }

    void applyEffect(StatusEffect effect,
                     std::vector<Enemy*>& enemies) {

        checkElementCombo(effect, enemies);
        effects.push_back(effect);
    }

    void update(float dt) {

        currentSpeed = baseSpeed;

        for (auto& ef : effects) {

            ef.duration -= dt;

            switch (ef.type) {
            case BURN:
                takeDamage(ef.value * dt);
                break;

            case SLOW:
                currentSpeed = baseSpeed * (1.0f - ef.value);
                break;

            case STUN:
                currentSpeed = 0;
                break;
            }
        }

        effects.erase(
            std::remove_if(effects.begin(), effects.end(),
                [](StatusEffect& e){ return e.duration <= 0; }),
            effects.end()
        );

        position.x += currentSpeed * dt;
    }
};

//////////////////////////////////////////////////////////////
// Tower Base

class Tower {
protected:
    Vector2 position;
    float damage;
    float range;
    float attackSpeed;
    float cooldown;

public:
    Tower(Vector2 pos) {
        position = pos;
        cooldown = 0;
    }

    virtual void update(float dt,
                        std::vector<Enemy*>& enemies) = 0;

    Enemy* findTarget(std::vector<Enemy*>& enemies) {
        for (auto e : enemies) {
            if (e->alive &&
                distance(position, e->position) <= range)
                return e;
        }
        return nullptr;
    }
};

//////////////////////////////////////////////////////////////
// Fire Tower

class FireTower : public Tower {
public:
    FireTower(Vector2 pos) : Tower(pos) {
        damage = 20;
        range = 150;
        attackSpeed = 1.0f;
    }

    void attack(Enemy* target,
                std::vector<Enemy*>& enemies) {

        target->takeDamage(damage);

        StatusEffect burn;
        burn.type = BURN;
        burn.element = ELEMENT_FIRE;
        burn.duration = 3.0f;
        burn.value = 10;

        target->applyEffect(burn, enemies);
    }

    void update(float dt,
                std::vector<Enemy*>& enemies) override {

        cooldown -= dt;
        Enemy* target = findTarget(enemies);

        if (target && cooldown <= 0) {
            attack(target, enemies);
            cooldown = attackSpeed;
        }
    }
};

//////////////////////////////////////////////////////////////
// Ice Tower

class IceTower : public Tower {
public:
    IceTower(Vector2 pos) : Tower(pos) {
        damage = 10;
        range = 150;
        attackSpeed = 1.5f;
    }

    void attack(Enemy* target,
                std::vector<Enemy*>& enemies) {

        target->takeDamage(damage);

        StatusEffect stun;
        stun.type = STUN;
        stun.element = ELEMENT_ICE;
        stun.duration = 1.5f;
        stun.value = 0;

        target->applyEffect(stun, enemies);
    }

    void update(float dt,
                std::vector<Enemy*>& enemies) override {

        cooldown -= dt;
        Enemy* target = findTarget(enemies);

        if (target && cooldown <= 0) {
            attack(target, enemies);
            cooldown = attackSpeed;
        }
    }
};

//////////////////////////////////////////////////////////////
// Lightning Tower

class LightningTower : public Tower {
public:
    LightningTower(Vector2 pos) : Tower(pos) {
        damage = 15;
        range = 150;
        attackSpeed = 1.2f;
    }

    void attack(Enemy* target,
                std::vector<Enemy*>& enemies) {

        target->takeDamage(damage);

        StatusEffect shock;
        shock.type = STUN;
        shock.element = ELEMENT_LIGHTNING;
        shock.duration = 1.0f;
        shock.value = 0;

        target->applyEffect(shock, enemies);
    }

    void update(float dt,
                std::vector<Enemy*>& enemies) override {

        cooldown -= dt;
        Enemy* target = findTarget(enemies);

        if (target && cooldown <= 0) {
            attack(target, enemies);
            cooldown = attackSpeed;
        }
    }
};

//////////////////////////////////////////////////////////////
// Wind Tower

class WindTower : public Tower {
public:
    WindTower(Vector2 pos) : Tower(pos) {
        damage = 5;
        range = 150;
        attackSpeed = 1.3f;
    }

    void attack(Enemy* target,
                std::vector<Enemy*>& enemies) {

        target->takeDamage(damage);

        StatusEffect slow;
        slow.type = SLOW;
        slow.element = ELEMENT_WIND;
        slow.duration = 2.0f;
        slow.value = 0.3f;

        target->applyEffect(slow, enemies);
    }

    void update(float dt,
                std::vector<Enemy*>& enemies) override {

        cooldown -= dt;
        Enemy* target = findTarget(enemies);

        if (target && cooldown <= 0) {
            attack(target, enemies);
            cooldown = attackSpeed;
        }
    }
};
