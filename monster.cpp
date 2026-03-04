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
// Monster Class

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

        if (!alive) {
            std::cout << "Monster already dead\n";
            return;
        }

        hp -= dmg;

        if (hp <= 0) {
            hp = 0;
            alive = false;

            std::cout << "HP left: " << hp << "\n";
            std::cout << "Monster Dead\n";
        }
        else {
            std::cout << "HP left: " << hp << "\n";
        }
    }
};

//////////////////////////////////////////////////////////////
// Damage Multiplier

float getDamageMultiplier(ElementType tower,
                          ElementType monster) {

    if (monster == ELEMENT_FIRE && tower == ELEMENT_WATER)
        return 1.5f;

    if (monster == ELEMENT_WATER && tower == ELEMENT_LIGHTNING)
        return 1.5f;

    if (monster == ELEMENT_ICE && tower == ELEMENT_FIRE)
        return 1.5f;

    if (monster == ELEMENT_LIGHTNING && tower == ELEMENT_EARTH)
        return 1.5f;

    if (monster == ELEMENT_WIND && tower == ELEMENT_FIRE)
        return 1.5f;

    if (monster == ELEMENT_EARTH && tower == ELEMENT_WIND)
        return 1.5f;

    return 1.0f;
}

//////////////////////////////////////////////////////////////
// CC Multiplier

float getCCMultiplier(ElementType tower,
                      ElementType monster) {

    if (monster == ELEMENT_FIRE && tower == ELEMENT_ICE)
        return 1.5f;

    if (monster == ELEMENT_WATER && tower == ELEMENT_WIND)
        return 1.5f;

    if (monster == ELEMENT_ICE && tower == ELEMENT_LIGHTNING)
        return 1.5f;

    if (monster == ELEMENT_LIGHTNING && tower == ELEMENT_ICE)
        return 1.5f;

    if (monster == ELEMENT_WIND && tower == ELEMENT_WATER)
        return 1.5f;

    if (monster == ELEMENT_EARTH && tower == ELEMENT_FIRE)
        return 1.5f;

    return 1.0f;
}

//////////////////////////////////////////////////////////////
// Tower Attack

void towerAttack(Enemy* monster,
                 ElementType towerElement,
                 float baseDamage) {

    if (!monster->alive)
        return;

    float dmgMultiplier =
        getDamageMultiplier(towerElement,
                            monster->element);

    float ccMultiplier =
        getCCMultiplier(towerElement,
                        monster->element);

    float finalDamage = baseDamage * dmgMultiplier;

    std::cout << "\nTower Attack -> "
              << monster->getElementName()
              << " Monster\n";

    std::cout << "Damage Multiplier: x"
              << dmgMultiplier << "\n";

    std::cout << "CC Multiplier: x"
              << ccMultiplier << "\n";

    monster->takeDamage(finalDamage);
}

//////////////////////////////////////////////////////////////
// Main Simulation

int main() {

    std::vector<Enemy*> monsters;

    monsters.push_back(new Enemy(200, ELEMENT_FIRE));
    monsters.push_back(new Enemy(200, ELEMENT_WATER));
    monsters.push_back(new Enemy(200, ELEMENT_ICE));
    monsters.push_back(new Enemy(200, ELEMENT_LIGHTNING));
    monsters.push_back(new Enemy(200, ELEMENT_WIND));
    monsters.push_back(new Enemy(200, ELEMENT_EARTH));

    ElementType towerElement = ELEMENT_WATER;
    float towerDamage = 50;

    while (!monsters.empty()) {

        Enemy* target = monsters.front(); // ยิงตัวหน้าสุด

        towerAttack(target,
                    towerElement,
                    towerDamage);

        if (!target->alive) {

            delete target;

            monsters.erase(monsters.begin());

            std::cout << "Monster removed from lane\n";
        }
    }

    std::cout << "\nAll monsters defeated!\n";

    return 0;
}
