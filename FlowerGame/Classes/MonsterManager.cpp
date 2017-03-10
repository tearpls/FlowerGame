//
//  MonsterManager.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/6/17.
//
//

#include "MonsterManager.h"
#include "Snake.h"
#include "GameField.h"

USING_NS_CC;

MonsterManager* MonsterManager::mmInstance;

MonsterManager* MonsterManager::getInstance()
{
    if (!mmInstance) {
        
        mmInstance = new MonsterManager();
  
    }
    return mmInstance;
}



void MonsterManager::reset()
{
    
    //Init respawn rate with initial value
    respawnRate = initRespwanRate;
    
    //Init respawn time with 0, so monster would be spawned right after 1st touch
    respawnTime = 0;
    
    respawnDecreaseTime = respawnDecreaseRate;

    monsters.clear();
}

void MonsterManager::spawnSnake()
{
    

  
    Vec2 spawnPoint = GameField::getInstance()->getFreePointForSpawning();
    

    
    
    if (spawnPoint != Vec2::ZERO ) {
        monsters.emplace_back(new Snake(spawnPoint));
    }else {
        log("No free space to spawn new Snake!");
    }
    
    
}

void MonsterManager::update(float dt)
{

    respawnDecreaseTime -= dt;
    
    if (respawnDecreaseTime <= 0) {
        respawnRate += respawnRate*0.05f;
        respawnDecreaseTime = respawnDecreaseRate;
    }
    
    respawnTime -= dt;
    if (respawnTime <= 0) {
        
        //Spawn monster
        this->spawnSnake();
        
        //reset respawn time
        respawnTime = respawnRate;
        
    }

    
    
    for (auto& monster: monsters) {
        monster->update(dt);
    }

}

bool MonsterManager::handleTouch(Point touchLocation)
{
    bool isMonsterTouched = false;
    
    for (auto& monster: monsters) {
        
        isMonsterTouched = monster->handleTouch(touchLocation);
    }
    
    //Check if there any "dead" monsters
    auto monsterItr = std::find_if(monsters.begin(), monsters.end(), [](Monster* monster) {return monster->isDead(); });
 
    if (monsterItr != monsters.end()) {
        
        (*monsterItr)->deleteMe();
        monsters.erase(monsterItr);
    }
    
    return isMonsterTouched;
}


std::vector<cocos2d::Sprite*> MonsterManager::getSprites()
{
    std::vector<Sprite*> monstersSprites;
    for (auto& monster: monsters) {
        std::vector<Sprite*> sprites = monster->getSprites();
        monstersSprites.insert(monstersSprites.end(), sprites.begin(), sprites.end());
    }
    
    return std::move(monstersSprites);
    
}


Size MonsterManager::getMonsterSize()
{
    //Create texture and get size of it
    //Better approach would be creating settings xml/json with all monster settings
    Image* image = new Image();
    image->initWithImageFile("images/monsters/snake/snake_head.png");
    
    Texture2D* texture = new Texture2D();
    texture->initWithImage(image);
    
    
    return texture->getContentSize();
}


void MonsterManager::speedUpMonsters()
{
    for (const auto& monster : monsters) {
        monster->speedUp();
    }
    
    
    
}
