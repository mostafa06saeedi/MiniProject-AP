#include "Terrorist.h"
#include <iostream>

namespace CounterStrike {
using namespace std;
    Terrorist::Terrorist() : Player(), hasBomb(false), plantedBomb(false) {}

    Terrorist::Terrorist(const std::string& name, CounterStrike::PlayerType type, int money)
        : Player(name, type, money), hasBomb(false), plantedBomb(false) {}

    Terrorist::Terrorist(const Terrorist& other)
        : Player(other), hasBomb(other.hasBomb), plantedBomb(other.plantedBomb) {}

    void Terrorist::setHasBomb(bool value) { hasBomb = value; }
    bool Terrorist::getHasBomb() const { return hasBomb; }

    void Terrorist::setPlantedBomb(bool value) { plantedBomb = value; }
    bool Terrorist::getPlantedBomb() const { return plantedBomb; }

    void Terrorist::createTerrorist(const std::string& name, PlayerType type, int money) {
        createPlayer(name, type, money);
        hasBomb = false;
        plantedBomb = false;
    }

    void Terrorist::readTerroristInfo() const {
        printPlayerInfo();
    }

    void Terrorist::updateTerroristInfo(const std::string& name, PlayerType type, int money) {
        updatePlayerInfo(name, type, money);
    }

    void Terrorist::deleteTerrorist() {
        deletePlayer();
        hasBomb = false;
        plantedBomb = false;
    }

    void Terrorist::printPlayerInfo() const {
        cout << "[Terrorist Team]\n";
        Player::printPlayerInfo();
             cout << "Has Bomb: " << (hasBomb ? "Yes" : "No") << "\n"
                  << "Planted Bomb: " << (plantedBomb ? "Yes" : "No") << "\n";
    }
}