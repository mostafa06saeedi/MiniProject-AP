#include "GameMap.h"
#include <iostream>
#include <vector>

using namespace std;

namespace CounterStrike {

GameMap::GameMap() : mapName("Unknown"), mapDesigner("Unknown"), mapStatus(MapStatus::DAY) {}

GameMap::GameMap(const std::string& mapName, const std::string& mapDesigner, MapStatus mapStatus)
: mapName(mapName), mapDesigner(mapDesigner), mapStatus(mapStatus) {}

GameMap::GameMap(const GameMap& other)
: mapName(other.mapName), mapDesigner(other.mapDesigner), mapStatus(other.mapStatus) {}

void GameMap::createMap(const std::string& mapName, const std::string& mapDesigner, MapStatus mapStatus) {
    this->mapName = mapName;
    this->mapDesigner = mapDesigner;
    this->mapStatus = mapStatus;
}

void GameMap::readMap() const {
    cout << "Map Name: " << mapName << "\n";
    cout << "Map Designer: " << mapDesigner << "\n";
    cout << "Map Status: " << (mapStatus == MapStatus::DAY ? "Day" : "Night") << "\n";
}

void GameMap::updateMap(const std::string& mapName, const std::string& mapDesigner, MapStatus mapStatus) {
    this->mapName = mapName;
    this->mapDesigner = mapDesigner;
    this->mapStatus = mapStatus;
}

void GameMap::deleteMap() {
    mapName.clear();
    mapDesigner.clear();
    mapStatus = MapStatus::DAY;
}

    std::string GameMap::getMapName() const { return mapName; }
    std::string GameMap::getMapDesigner() const { return mapDesigner; }
    MapStatus GameMap::getMapStatus() const { return mapStatus; }

    bool GameMap::operator==(const GameMap& other) const {
        return mapName == other.mapName && mapDesigner == other.mapDesigner && mapStatus == other.mapStatus;
    }

    bool GameMap::operator!=(const GameMap& other) const {
        return !(*this == other);
    }

    std::vector<GameMap> GameMap::createDefaultMaps() {
        std::vector<GameMap> maps;
        maps.emplace_back("Alghadir", "Roham", MapStatus::NIGHT);
        maps.emplace_back("Daneshkadeh", "Mostafa", MapStatus::DAY);
        maps.emplace_back("Aviny", "Fazel", MapStatus::DAY);
        maps.emplace_back("Kharazmi", "Sina", MapStatus::NIGHT);
        maps.emplace_back("Aborihan", "Iman", MapStatus::DAY);

        return maps;
    }

} 