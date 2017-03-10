//
//  MonsterManager.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/6/17.
//
//

#ifndef MonsterManager_h
#define MonsterManager_h

#include "Monster.h"
#include "GameScene.h"

class MonsterManager
{
    
public:
    
    static MonsterManager* getInstance();
    
    void initOptions();
    
    void reset();
    
    ~MonsterManager() {};
    
    void spawnSnake();
    
    void update(float dt);
    
    std::vector<cocos2d::Sprite*> getSprites();
    
    bool handleTouch(cocos2d::Point touchLocation);
    
    cocos2d::Size getMonsterSize();
    
    void speedUpMonsters();
    
private:
    MonsterManager() {};
    
    std::vector<Monster*> monsters;
    
    static MonsterManager* mmInstance;
    
    //Current time until next monster respawn
    float respawnTime;
    
    //Current rate until next monster respawn
    float respawnRate;
    
    //Initial monter respawn time
    const float initRespwanRate = 5.0f;
    
    //Current time until next respawn rate decrease
    float respawnDecreaseTime;
    
    //Rate of decreasing monster spawning pace
    const float respawnDecreaseRate = 10.0f;
};

#endif /* MonsterManager_h */
