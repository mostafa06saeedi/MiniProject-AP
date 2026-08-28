#ifndef CT_H
#define CT_H

#include "Player.h"
#include <string>

namespace CounterStrike {
    class CT : public Player {
    private:
        bool hasDefuseKit;
        bool defusedBomb;

    public:
        
        CT(const std::string& name, CounterStrike::PlayerType type, int money);
        CT(const CT& other);

        void setHasDefuseKit(bool value);
        bool getHasDefuseKit() const;
        void setDefusedBomb(bool value);
        bool getDefusedBomb() const;

        void createCT(std::string _name, PlayerType _type, int _money);
        void readCTInfo() const;
        void updateCTInfo(const std::string& _name, PlayerType _type, int _money);
        void deleteCT();
        void printPlayerInfo() const override;
    };
}

#endif 