#ifndef TERRORIST_H
#define TERRORIST_H

#include "Player.h"

namespace CounterStrike {
    class Terrorist : public Player {
    private:
        bool hasBomb;
        bool plantedBomb;

    public:
    
        Terrorist();
        Terrorist(const std::string& name, CounterStrike::PlayerType type, int money);
        Terrorist(const Terrorist& other);

        void setHasBomb(bool value);
        bool getHasBomb() const;
        void setPlantedBomb(bool value);
        bool getPlantedBomb() const;

        void createTerrorist(const std::string& name, PlayerType type, int money);
        void readTerroristInfo() const;
        void updateTerroristInfo(const std::string& name, PlayerType type, int money);
        void deleteTerrorist();

        void printPlayerInfo() const override;
    };
}

#endif 