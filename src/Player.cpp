#include "Player.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace CounterStrike {
using namespace std;
    
    std::string Player::generateUniqueId() {
        static int counter = 0;
        return "PLAYER_" + std::to_string(++counter);
    }

    Player::Player()
        : id(generateUniqueId()), name("Unknown"), type(PlayerType::AI), money(0),
          health(MAX_HEALTH), armor(0), status(PlayerStatus::ALIVE) {}

    Player::Player(const Player& other)
        : id(generateUniqueId()), name(other.name), type(other.type), money(other.money),
          health(other.health), armor(other.armor), status(other.status), weaponList(other.weaponList) {}

    Player::Player(std::string _name, PlayerType _type, int _money)
        : id(generateUniqueId()), name(_name), type(_type), money(_money),
          health(MAX_HEALTH), armor(0), status(PlayerStatus::ALIVE) {}

    std::string Player::getId() const { return id; }
    std::string Player::getName() const { return name; }
    PlayerType Player::getType() const { return type; }
    int Player::getMoney() const { return money; }
    int Player::getHealth() const { return health; }
    int Player::getArmor() const { return armor; }
    PlayerStatus Player::getStatus() const { return status; }

    const std::vector<Weapon>& Player::getWeapons() const {
        return weaponList;
    }

    void Player::setName(const std::string& _name) { name = _name; }
    void Player::setType(PlayerType _type) { type = _type; }
    void Player::setMoney(int _money) {
        if (_money < 0)
            throw std::invalid_argument("Money cannot be negative");
        money = _money;
    }

    void Player::setHealth(int _health) {
        if (_health < 0 || _health > 100) {
            throw std::invalid_argument("Health must be between 0 and 100");
        }
        health = _health;
    }

    void Player::setArmor(int _armor) {
        if (_armor < 0 || _armor > 100)
            throw std::invalid_argument("Armor must be between 0 and 100");
        armor = _armor;
    }

    void Player::addWeapon(const Weapon& weapon) {
        weaponList.push_back(weapon);
    }

    void Player::removeWeaponById(int weaponId) {
        weaponList.erase(std::remove_if(weaponList.begin(), weaponList.end(),
                                        [weaponId](const Weapon& weapon) { return weapon.getId() == weaponId; }),
                         weaponList.end());
    }

    void Player::printWeaponList() const {
        for (const auto& weapon : weaponList) {
            std::cout << weapon << std::endl;
        }
    }

    int Player::calculateCombatPower() const {
        int power = health + armor + money;
        for (const auto& weapon : weaponList) {
            power += weapon.getAmmo() * weapon.getDamage();
        }
        return power;
    }

    void Player::createPlayer(std::string _name, PlayerType _type, int _money) {
        name = _name;
        type = _type;
        money = _money;
    }

    void Player::readPlayerInfo() const {
        printPlayerInfo();
    }

    void Player::updatePlayerInfo(const std::string& _name, PlayerType _type, int _money) {
        name = _name;
        type = _type;
        money = _money;
    }

    void Player::deletePlayer() {
        name = "Deleted";
        health = 0;
        armor = 0;
        status = PlayerStatus::DEAD;
        weaponList.clear();
    }

    bool Player::operator==(const Player& other) const {
        return id == other.id;
    }

    bool Player::operator!=(const Player& other) const {
        return !(*this == other);
    }

    Player& Player::operator=(const Player& other) {
        if (this != &other) {
            name = other.name;
            type = other.type;
            money = other.money;
            health = other.health;
            armor = other.armor;
            status = other.status;
            weaponList = other.weaponList;
        }
        return *this;
    }

    void Player::printPlayerInfo() const {
             cout << "Player Info:\n"
                  << "ID: " << id << "\n"
                  << "Name: " << name << "\n"
                  << "Health: " << health << "\n"
                  << "Armor: " << armor << "\n"
                  << "Status: " << (status == PlayerStatus::ALIVE ? "Alive" : "Dead") << "\n"
                  << "Type: " << (type == PlayerType::HUMAN ? "Human" : "AI") << "\n"
                  << "Money: " << money << "\n"
                  << "Weapons: " << weaponList.size() << " weapons\n";
        printWeaponList();
    }

}
