#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
namespace CounterStrike {

    enum class MapStatus {
        DAY,
        NIGHT
    };

    class GameMap {
    private:
        std::string mapName;
        std::string mapDesigner;
        MapStatus mapStatus;

    public:
        GameMap();
        GameMap(const std::string& mapName, const std::string& mapDesigner, MapStatus mapStatus);
        GameMap(const GameMap& other);

        ~GameMap() = default;

        void createMap(const std::string& mapName, const std::string& mapDesigner, MapStatus mapStatus);
        void readMap() const;
        void updateMap(const std::string& mapName, const std::string& mapDesigner, MapStatus mapStatus);
        void deleteMap();
        
        std::string getMapName() const;
        std::string getMapDesigner() const;
        MapStatus getMapStatus() const;
        
        bool operator==(const GameMap& other) const;
        bool operator!=(const GameMap& other) const;
        
        static std::vector<GameMap> createDefaultMaps();
    };

}

#endif