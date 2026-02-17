#include <iostream>
#include <vector>
#include <string>

//////////////////////////////////////////////////////////////
// Element

enum ElementType {
    ELEMENT_FIRE,
    ELEMENT_WATER,
    ELEMENT_ICE,
    ELEMENT_LIGHTNING,
    ELEMENT_WIND,
    ELEMENT_EARTH
};

//////////////////////////////////////////////////////////////
// Monster Base

class Enemy {
public:
    float hp;
    bool alive;
    ElementType element;

    Enemy(float hpValue, ElementType e) {
        hp = hpValue;
        alive = true;
        element = e;
    }

    std::string getElementName() {
        switch (element) {
        case ELEMENT_FIRE: return "Fire";
        case ELEMENT_WATER: return "Water";
        case ELEMENT_ICE: return "Ice";
        case ELEMENT_LIGHTNING: return "Lightning";
        case ELEMENT_WIND: return "Wind";
        case ELEMENT_EARTH: return "Earth";
        }
        return "";
    }

    void takeDamage(float dmg) {
        hp -= dmg;
        std::cout << "HP left: " << hp << "\n";
        if (hp <= 0) {
            alive = false;
            std::cout << "Monster Dead\n";
        }
    }
};

//////////////////////////////////////////////////////////////
// Damage Multiplier System

float getDamageMultiplier(ElementType tower,
                          ElementType monster) {

    // 🔥 Fire Monster
    if (monster == ELEMENT_FIRE &&
        tower == ELEMENT_WATER)
        return 1.5f;

    // 💧 Water Monster
    if (monster == ELEMENT_WATER &&
        tower == ELEMENT_LIGHTNING)
        return 1.5f;

    // ❄ Ice Monster
    if (monster == ELEMENT_ICE &&
        tower == ELEMENT_FIRE)
        return 1.5f;

    // ⚡ Lightning Monster
    if (monster == ELEMENT_LIGHTNING &&
        tower == ELEMENT_EARTH)
        return 1.5f;

    // 🌪 Wind Monster
    if (monster == ELEMENT_WIND &&
        tower == ELEMENT_FIRE)
        return 1.5f;

    // 🌍 Earth Monster
    if (monster == ELEMENT_EARTH &&
        tower == ELEMENT_WIND)
        return 1.5f;

    return 1.0f;
}

//////////////////////////////////////////////////////////////
// CC Strength System

float getCCMultiplier(ElementType tower,
                      ElementType monster) {

    // Fire Monster โดน Ice CC แรง
    if (monster == ELEMENT_FIRE &&
        tower == ELEMENT_ICE)
        return 1.5f;

    // Water Monster โดน Wind CC แรง
    if (monster == ELEMENT_WATER &&
        tower == ELEMENT_WIND)
        return 1.5f;

    // Ice Monster โดน Lightning CC แรง
    if (monster == ELEMENT_ICE &&
        tower == ELEMENT_LIGHTNING)
        return 1.5f;

    // Lightning Monster โดน Ice CC แรง
    if (monster == ELEMENT_LIGHTNING &&
        tower == ELEMENT_ICE)
        return 1.5f;

    // Wind Monster โดน Water CC แรง
    if (monster == ELEMENT_WIND &&
        tower == ELEMENT_WATER)
        return 1.5f;

    // Earth Monster โดน Fire CC แรง
    if (monster == ELEMENT_EARTH &&
        tower == ELEMENT_FIRE)
        return 1.5f;

    return 1.0f;
}

//////////////////////////////////////////////////////////////
// Example Attack

void towerAttack(Enemy* monster,
                 ElementType towerElement,
                 float baseDamage) {

    float dmgMultiplier =
        getDamageMultiplier(towerElement,
                            monster->element);

    float ccMultiplier =
        getCCMultiplier(towerElement,
                        monster->element);

    float finalDamage = baseDamage * dmgMultiplier;

    std::cout << "Tower Element: " << towerElement
              << " -> Monster: "
              << monster->getElementName() << "\n";

    std::cout << "Damage Multiplier: x"
              << dmgMultiplier << "\n";

    std::cout << "CC Multiplier: x"
              << ccMultiplier << "\n";

    monster->takeDamage(finalDamage);
}

//////////////////////////////////////////////////////////////
// Create 6 Monsters

int main() {

    std::vector<Enemy*> monsters;

    monsters.push_back(new Enemy(200, ELEMENT_FIRE));
    monsters.push_back(new Enemy(200, ELEMENT_WATER));
    monsters.push_back(new Enemy(200, ELEMENT_ICE));
    monsters.push_back(new Enemy(200, ELEMENT_LIGHTNING));
    monsters.push_back(new Enemy(200, ELEMENT_WIND));
    monsters.push_back(new Enemy(200, ELEMENT_EARTH));

    // ตัวอย่างยิงด้วยป้อมน้ำ
    towerAttack(monsters[0], ELEMENT_WATER, 50);

    return 0;
}

