#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>
#include <stdexcept>
#include "WeaponType.h"

namespace CounterStrike {

class Weapon {
private:
    int id;
    int ammo;
    int price;
    int damage;
    static int weaponCount;
    WeaponType type;

public:
    Weapon();
    Weapon(int id, int ammo, int price, int damage, WeaponType type);
    Weapon(const Weapon& other);
    ~Weapon();

    int getId() const;
    int getAmmo() const;
    void setAmmo(int ammo);       
    int getPrice() const;
    void setPrice(int price);     
    int getDamage() const;
    void setDamage(int damage);    
    WeaponType getType() const;

    static std::string getWeaponName(WeaponType type);
    static int getWeaponCount();
    static Weapon createWeapon(int id, int ammo, int price, int damage, WeaponType type);

    void updateWeapon(int ammo, int price);
    Weapon& operator=(const Weapon& other);

    bool operator==(const Weapon& other) const;
    bool operator!=(const Weapon& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon);
};

}

#endif
