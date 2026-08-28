#include "CT.h"
#include <iostream>
using namespace std;
namespace CounterStrike {

    CT::CT(const std::string& name, CounterStrike::PlayerType type, int money)
        : Player(name, type, money), hasDefuseKit(false), defusedBomb(false) {}

    CT::CT(const CT& other)
        : Player(other), hasDefuseKit(other.hasDefuseKit), defusedBomb(other.defusedBomb) {}

    void CT::setHasDefuseKit(bool value) { hasDefuseKit = value; }
    bool CT::getHasDefuseKit() const { return hasDefuseKit; }
    void CT::setDefusedBomb(bool value) { defusedBomb = value; }
    bool CT::getDefusedBomb() const { return defusedBomb; }

    void CT::createCT(std::string _name, PlayerType _type, int _money) {
        createPlayer(_name, _type, _money);
        hasDefuseKit = false;
        defusedBomb = false;
    }

    void CT::readCTInfo() const {
        printPlayerInfo();
    }

    void CT::updateCTInfo(const std::string& _name, PlayerType _type, int _money) {
        updatePlayerInfo(_name, _type, _money);
    }

    void CT::deleteCT() {
        deletePlayer();
        hasDefuseKit = false;
        defusedBomb = false;
    }

    void CT::printPlayerInfo() const {
        cout << "[Counter-Terrorist Team]\n";
        Player::printPlayerInfo();
        cout << "Has Defuse Kit: " << (hasDefuseKit ? "Yes" : "No") << "\n"
                  << "Defused Bomb: " << (defusedBomb ? "Yes" : "No") << "\n";
    }
}