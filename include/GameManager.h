#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include<vector>
#include<memory>
#include<string>
#include"Player.h"
#include"GameMap.h"
#include<mutex>

namespace CounterStrike
{
  class GameManager{
    private:
    static GameManager* instance;
    static std::mutex mtx;


    std::vector<std::shared_ptr<Player>> terroristTeam;
    std::vector<std::shared_ptr<Player>> ctTeam;
    std::string mapName;
    std::string gameResult;
    GameMap gameMap;

    GameManager();
    GameManager(const GameManager& other);
    GameManager(const std::string& mapName,const std::string& gameResult, const GameMap& gameMap);

    public:
    ~GameManager();
    

    static GameManager* getInstance();
    static void deleteInstance();

    void create(const std::string& mapName,const std::string& gameResult, const GameMap& gameMap);
    void read() const;
    void update(const std::string& mapName,const std::string& gameResult, const GameMap& gameMap);
    void remove();

    void addPlayerToTerroristTeam(std::shared_ptr<Player>player);
    void addPlayerToCTTeam(std::shared_ptr<Player>player);
    void removePlayerFromTerroristTeam(std::shared_ptr<Player>player);
    void removePlayerFromCTTeam(std::shared_ptr<Player>player);

    void setGameResult(const std::string& result);
    void setMap(const GameMap& map);
    std::vector<std::shared_ptr<Player>>& getTerroristTeam();
    std::vector<std::shared_ptr<Player>>& getCTTeam();
    std::string getMapName() const;
    std::string getGameResult() const;
    GameMap getGameMap() const;


    void printGameInfo() const;


    GameManager& operator=(const GameManager& other);
    bool operator==(const GameManager& other) const;
    bool operator!=(const GameManager& other) const;
  };

} 

#endif