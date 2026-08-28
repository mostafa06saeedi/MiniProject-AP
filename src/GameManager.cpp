#include"GameManager.h"
#include<iostream>
#include<algorithm>
#include<stdexcept>

using namespace std;
namespace CounterStrike{

    GameManager* GameManager::instance = nullptr;
    std::mutex GameManager::mtx;

    GameManager:: GameManager() : mapName("Unknown"), gameResult("Ongoing") {}
    GameManager::GameManager(const GameManager& other)
:    terroristTeam(other.terroristTeam),
    ctTeam(other.ctTeam),
    mapName(other.mapName),
    gameResult(other.gameResult),
    gameMap(other.gameMap){}

    GameManager::GameManager(const std::string& mapName, const std::string& gameResult, const GameMap& gameMap) :
        mapName(mapName),
        gameResult(gameResult),
        gameMap(gameMap) {}

        GameManager::~GameManager() {}


        GameManager* GameManager::getInstance() {
            lock_guard<mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new GameManager();
            }
            return instance;
        }

        void GameManager::deleteInstance() {
            lock_guard<mutex>lock(mtx);
            if(instance != nullptr){
                delete instance;
                instance = nullptr;
            }
        }

        void GameManager::create(const std::string& mapName, const std::string& gameResult, const GameMap& gameMap) {
            if (mapName.empty() || gameResult.empty()) {
                throw std::invalid_argument("Map name and game result cannot be empty.");
            }
            this->mapName = mapName;
            this->gameResult = gameResult;
            this->gameMap = gameMap;
            terroristTeam.clear();
            ctTeam.clear();
        }
        void GameManager::read() const{
            printGameInfo();
        }
        void GameManager::update(const std::string& mapName, const std::string& gameResult, const GameMap& gameMap){
            this-> mapName = mapName;
            this-> gameResult = gameResult;
            this-> gameMap = gameMap;
        }
        void GameManager::remove() {
            terroristTeam.clear();
        ctTeam.clear();
        mapName = "Unknown";
        gameResult = "Ongoing";
        gameMap = GameMap(); 
        }




        void GameManager::addPlayerToTerroristTeam(std::shared_ptr<Player>player){
            terroristTeam.push_back(player);

        }
        void GameManager::addPlayerToCTTeam(std::shared_ptr<Player>player){
            ctTeam.push_back(player);
        }
        void GameManager::removePlayerFromTerroristTeam(std::shared_ptr<Player>player){
            auto it = find(terroristTeam.begin() , terroristTeam.end(), player);
            if(it != terroristTeam.end()){
                terroristTeam.erase(it);
            }else {
                throw runtime_error("Player not found in Terrorist team.");
            }
        }
        void GameManager::removePlayerFromCTTeam(std::shared_ptr<Player>player){
            auto it = find(ctTeam.begin(),ctTeam.end(), player);
            if(it != ctTeam.end()){
                ctTeam.erase(it);
            }else {
                throw runtime_error("Player not found in CT team.");
            }
        }


        void GameManager::setGameResult(const std::string& result){
            gameResult = result;
        }
        void GameManager::setMap(const GameMap& map){
            gameMap = map;
        }
        

        std::vector<std::shared_ptr<Player>>& GameManager::getTerroristTeam() {
            return terroristTeam;
        }

        std::vector<std::shared_ptr<Player>>& GameManager::getCTTeam() {
            return ctTeam;
        }
        string GameManager::getMapName() const{
            return mapName;
        }
        string GameManager::getGameResult() const{
            return gameResult;
        }
        GameMap GameManager::getGameMap() const{
            return gameMap;
        }


        void GameManager::printGameInfo() const {
            cout << "Game Info:\n";
            cout << "Map Name: " << mapName << "\n";
            cout << "Game Result: " << gameResult << "\n";
            cout << "Terrorist Team Players (" << terroristTeam.size() << "):\n";
            for (const auto& player : terroristTeam) {
                cout << "- " << player->getName() << "\n";
            }
            cout << "CT Team Players (" << ctTeam.size() << "):\n";
            for (const auto& player : ctTeam) {
                cout << "- " << player->getName() << "\n";
            }
        }


        GameManager& GameManager::operator=(const GameManager& other){
            if (this != &other)
            {
                terroristTeam = other.terroristTeam;
                ctTeam= other.ctTeam;
                mapName = other.mapName;
                gameResult = other.gameResult;
                gameMap = other.gameMap;
            }
            return *this;
        }
        bool GameManager::operator==(const GameManager& other) const{
            return mapName == other.mapName &&
            gameResult == other.gameResult &&
            gameMap == other.gameMap;
        }
        bool GameManager::operator!=(const GameManager& other) const{
            return !(*this == other);
        }

}