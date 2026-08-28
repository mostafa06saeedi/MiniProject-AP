#include "Weapon.h"
using namespace std;
namespace CounterStrike {

int Weapon::weaponCount = 0;

Weapon::Weapon() : id(0), ammo(0), price(0), damage(0), type(WeaponType::AK47) {
    weaponCount++;
}

Weapon::Weapon(int id, int ammo, int price, int damage, WeaponType type) {
    if (ammo < 0) {
        throw std::invalid_argument("Ammo cannot be negative");
    }
    if (price < 0) {
        throw std::invalid_argument("Price cannot be negative");
    }
    if (damage < 0) {
        throw std::invalid_argument("Damage cannot be negative");
    }

    this->id = id;
    this->ammo = ammo;
    this->price = price;
    this->damage = damage;
    this->type = type;

    weaponCount++;
}

Weapon::Weapon(const Weapon& other)
    : id(other.id), ammo(other.ammo), price(other.price), damage(other.damage), type(other.type) {
    weaponCount++;
}

Weapon::~Weapon() {
    weaponCount--;
}

int Weapon::getId() const {
    return id;
}

int Weapon::getAmmo() const {
    return ammo;
}

void Weapon::setAmmo(int ammo) {
    if (ammo < 0) {
        throw std::invalid_argument("Ammo cannot be negative");
    }
    this->ammo = ammo;
}

int Weapon::getPrice() const {
    return price;
}

void Weapon::setPrice(int price) {
    if (price < 0) {
        throw std::invalid_argument("Price cannot be negative");
    }
    this->price = price;
}

int Weapon::getDamage() const {
    return damage;
}

void Weapon::setDamage(int damage) {
    if (damage < 0) {
        throw std::invalid_argument("Damage cannot be negative");
    }
    this->damage = damage;
}

WeaponType Weapon::getType() const {
    return type;
}

std::string Weapon::getWeaponName(WeaponType type) {
    switch (type) {
        case WeaponType::AK47: return "AK47";
        case WeaponType::M4A1: return "M4A1";
        case WeaponType::AWP: return "AWP";
        case WeaponType::DEAGLE: return "DEAGLE";
        case WeaponType::UMP45: return "UMP45";
        default: return "Unknown";
    }
}

int Weapon::getWeaponCount() {
    return weaponCount;
}

Weapon Weapon::createWeapon(int id, int ammo, int price, int damage, WeaponType type) {
    return Weapon(id, ammo, price, damage, type);
}

void Weapon::updateWeapon(int ammo, int price) {
    setAmmo(ammo);
    setPrice(price);
}

Weapon& Weapon::operator=(const Weapon& other) {
    if (this != &other) {
        id = other.id;
        ammo = other.ammo;
        price = other.price;
        damage = other.damage;
        type = other.type;
    }
    return *this;
}

bool Weapon::operator==(const Weapon& other) const {
    return id == other.id && ammo == other.ammo && price == other.price &&
           damage == other.damage && type == other.type;
}

bool Weapon::operator!=(const Weapon& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
    os << "Weapon(ID: " << weapon.id
       << ", Ammo: " << weapon.ammo
       << ", Price: " << weapon.price
       << ", Damage: " << weapon.damage
       << ", Type: " << Weapon::getWeaponName(weapon.type) << ")";
    return os;
}
}