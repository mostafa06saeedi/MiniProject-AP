#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include <random>
#include <sstream>
#include "Weapon.h"
#include "WeaponType.h"
#include <stdexcept>

namespace CounterStrike {

    enum class PlayerStatus { ALIVE, DEAD };
    enum class PlayerType { HUMAN, AI };

    constexpr int MAX_HEALTH = 100;
    constexpr int MAX_ARMOR = 100;

    class Player {
    private:
        std::string id;               
        std::string name;               
        PlayerType type;                 
        int money;                      
        int health;                 
        int armor;                    
        PlayerStatus status;          
        std::vector<Weapon> weaponList;  

        static std::string generateUniqueId(); 

    public:
        
        Player();
        Player(const Player& other);
        Player(std::string _name, PlayerType _type, int _money);
        virtual ~Player() = default;

        std::string getId() const;
        std::string getName() const;
        PlayerType getType() const;
        int getMoney() const;
        int getHealth() const;
        int getArmor() const;
        PlayerStatus getStatus() const;
        const std::vector<Weapon>& getWeapons() const;

        void setName(const std::string& _name);
        void setType(PlayerType _type);
        void setMoney(int _money);
        void setHealth(int _health);
        void setArmor(int _armor);

        void addWeapon(const Weapon& weapon);          
        void removeWeaponById(int weaponId);     
        void printWeaponList() const;                

        int calculateCombatPower() const;      

        void createPlayer(std::string _name, PlayerType _type, int _money);
        void readPlayerInfo() const;
        void updatePlayerInfo(const std::string& _name, PlayerType _type, int _money);
        void deletePlayer();

        bool operator==(const Player& other) const;
        bool operator!=(const Player& other) const;
        Player& operator=(const Player& other);

        virtual void printPlayerInfo() const;
    };

}

#endif
