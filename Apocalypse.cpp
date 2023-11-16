#include <iostream>
#include <cmath>
using namespace std;

// Gun class representing a weapon
class Gun {
public:
    int Damage;
    int ammunition;
    int range;

    // Constructor initializes default values
    Gun() : Damage(40), ammunition(12), range(30) {}

    // Reload the gun, replenishing ammunition
    int reload() {
        if (ammunition == 0) {
            ammunition += 12;
            return ammunition;
        } else if (ammunition > 0 && ammunition < 12) {
            ammunition += (12 - ammunition);
        }
        return ammunition;
    }

    // Shoot at a target within range
    bool shoot(int target) {
        if (ammunition == 0) {
            reload();
            return false;
        } else {
            if (target > range) {
                cout << "Target out of range\n";
            } else if (target <= range) {
                ammunition--;
            }
        }
        return true;
    }
};

// Zombie class representing a zombie creature
class Zombie {
public:
    int health;
    int baseDamage;
    int defense;
    int speed;
    int x_coord, y_coord;

    // Constructor initializes zombie's position
    Zombie(int x, int y) : health(50), baseDamage(20), defense(20), speed(10), x_coord(x), y_coord(y) {}

    // Attempt to scratch a human within range
    bool scratch(int humanDefense, int& humanHealth, int humanX, int humanY) {
        if (x_coord == humanX && y_coord == humanY) {
            if (humanDefense >= baseDamage) {
                humanHealth -= 1;
            } else {
                int damage = baseDamage - humanDefense;
                humanHealth -= (damage > 0) ? damage : 0;
            }
            return true;
        } else {
            cout << "Out of range\n";
            return false;
        }
    }
};

// Human class representing a human character
class Human {
public:
    int health;
    int baseDamage;
    int defense;
    int speed;
    Gun pistol;
    int x_coord, y_coord;

    // Constructor initializes human's position
    Human(int x, int y) : health(100), baseDamage(15), defense(10), speed(30), x_coord(x), y_coord(y) {}

    // Get the current health of the human
    int getHealth() {
        return health;
    }

    // Attempt to attack a zombie within range
    bool attack(Zombie& zombie) {
        if (x_coord == zombie.x_coord && y_coord == zombie.y_coord) {
            if (zombie.defense >= baseDamage) {
                zombie.health -= 1;
            } else {
                zombie.health -= baseDamage;
            }
            return true;
        } else {
            cout << "Zombie is out of range\n";
            return false;
        }
    }

    // Use the weapon (pistol) to attack a zombie
    bool useWeapon(Zombie& zombie) {
        float zombieDistance = sqrt((zombie.x_coord - x_coord) * (zombie.x_coord - x_coord) +
                                    (zombie.y_coord - y_coord) * (zombie.y_coord - y_coord));
        if (zombieDistance <= pistol.range) {
            if (pistol.shoot(zombieDistance)) {
                int damage = pistol.Damage - zombie.defense;
                zombie.health -= (damage > 0) ? damage : 0;
                return true;
            }
        } else {
            cout << "Zombie is out of range\n";
        }
        return false;
    }
};

int main() {
    // Create instances of Human and Zombie
    Human devon(7, 6);
    Zombie hungryZombie(20, 20);
    Zombie sleepyZombie(7, 6);

    // Interaction with hungryZombie
    cout << "Devon shot hungry zombie!\n";
    devon.useWeapon(hungryZombie);
    cout << "Hungry zombie has " << hungryZombie.health << " health left" << "\n\n";

    // Interaction with sleepyZombie
    cout << "Devon punched sleepy zombie!\n";
    devon.attack(sleepyZombie);
    cout << "Sleepy zombie has " << sleepyZombie.health << " health left" << "\n\n";

    // Interaction where sleepyZombie scratches Devon
    cout << "Oh no! Sleepy zombie scratched Devon!\n";
    sleepyZombie.scratch(devon.defense, devon.health, devon.x_coord, devon.y_coord);
    cout << "Devon has " << devon.getHealth() << " health left\n\n";

    return 0;
}
