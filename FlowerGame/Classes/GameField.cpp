//
//  GameField.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/8/17.
//
//

#include "GameField.h"
#include "MonsterManager.h"
#include "PlantManager.h"


USING_NS_CC;


GameField* GameField::gameFieldInstance;


GameField* GameField::getInstance()
{
    if (!gameFieldInstance) {
        gameFieldInstance = new GameField();
        gameFieldInstance->initOptions();
    }
    
    return gameFieldInstance;
}


void GameField::initOptions()
{
    winSize = Director::getInstance()->getWinSize();
    
    obstaclesView = std::vector<std::vector<int>>(winSize.height, std::vector<int>(winSize.width, 1) );
    
    
}

float GameField::getMaxMonsterSize()
{
    
    Size monsterSize = MonsterManager::getInstance()->getMonsterSize();
    
    return std::max(monsterSize.width, monsterSize.height);
    
}

void GameField::resetField()
{
    
    //Renew view
    for (int y = borderSize; y < obstaclesView.size()-borderSize; ++y) {
        std::fill(obstaclesView[y].begin()+borderSize, obstaclesView[y].end()-borderSize, 0);
    }
    
    
    
}

void GameField::updateView(std::vector<cocos2d::Sprite*> obstaclesSprites)
{
    
    float monsterSize = getMaxMonsterSize()*1.05f;
    this->resetField();
    
    //Reserve points by monsters monster.position +- half of the monster size
    for (const auto& sprite : obstaclesSprites) {
        
        Vec2 pos = sprite->getPosition();
        
        /*
         Get top left and bottom right points of the reserved area
         */
        Vec2 topLeftPoint;
        topLeftPoint.x = pos.x - monsterSize;
        topLeftPoint.y = pos.y + monsterSize;
        
        Vec2 botRightPoint;
        botRightPoint.x = pos.x + monsterSize;
        botRightPoint.y = pos.y - monsterSize;

        
        for (int y = botRightPoint.y; y < topLeftPoint.y; ++y) {
            
            std::fill(obstaclesView[y].begin()+topLeftPoint.x, obstaclesView[y].begin()+botRightPoint.x, 1);
        }
        
    }

    
    
}



Vec2 GameField::getFreePointForSpawning()
{
    
    Vec2 spawnPoint = Vec2::ZERO;
    
    //Update view for plants and monsters
    std::vector<Sprite*> obstacles = MonsterManager::getInstance()->getSprites();
    std::vector<Sprite*> plants = PlantManager::getInstance()->getSprites();
    obstacles.insert(obstacles.end(), plants.begin(), plants.end());
    
    this->updateView(obstacles);
    

    //Create vector with random free points
    //Note: using custom FieldPoint insted of Vec2 increased performance by 2 times
    std::vector<FieldPoint> freePoints;
    
    
    for (int y = 0; y < obstaclesView.size(); ++y) {
        
        auto first = std::find(obstaclesView[y].begin(), obstaclesView[y].end(), 0);
        
        if (first != obstaclesView[y].end()) {
            freePoints.emplace_back(FieldPoint(first - obstaclesView[y].begin() , y));
        }
        
        auto middle = std::find(obstaclesView[y].begin()+obstaclesView[y].size()/2, obstaclesView[y].end(), 0);
        if (middle != obstaclesView[y].end()) {
            freePoints.emplace_back(FieldPoint(middle - obstaclesView[y].begin() , y));
        }
        
        auto last = std::find(obstaclesView[y].rbegin(), obstaclesView[y].rend(), 0);
        
        if (last != obstaclesView[y].rend()) {
            freePoints.emplace_back(FieldPoint( (last.base()-1) - obstaclesView[y].begin() , y));
        }
        
        
    }
    


    if (freePoints.size() > 0) {
        
        FieldPoint freePoint = freePoints.at(random(0, (int)freePoints.size()));
        
        spawnPoint.x = freePoint.x;
        spawnPoint.y = freePoint.y;
        
    }
    
  
    
    return spawnPoint;
    
}


bool GameField::isFreeForPlant(cocos2d::Point position)
{
    
    
    //this->updateView(std::vector<Sprite*>());

    this->updateView(MonsterManager::getInstance()->getSprites());
    
    float spriteSize = this->getMaxMonsterSize();
    
    //Forbid growing plants near game border
    for (int y = position.y+spriteSize; y > position.y-spriteSize; --y) {
        for (int x = position.x-spriteSize; x < position.x+spriteSize; ++x) {
            if (obstaclesView[y][x] == 1 ) {
                log("Can't grow plant there");
                return false;
            }
            
        }
        
        
    }
    
    
    return true;
}

cocos2d::Vec2 GameField::getFreePointForMove(cocos2d::Vec2 position, float speed, float rotation)
{

    std::vector<Vec2> freePoints;
    for (int i = 1; i < 11; ++i) {
        //Next point random generation
        for (int deltaAngle = -90; deltaAngle <= 90; deltaAngle+=10) {
            
            float newAngle = rotation+deltaAngle;
            Vec2 newPosition = position;
            
            newPosition.x += speed*150.0f/i*cosf(newAngle*M_PI/180.0f);
            newPosition.y += speed*150.0f/i*sinf(newAngle*M_PI/180.0f);
            
            //Check that New position should be within game borders
            if ( (newPosition.x-borderSize) > 0 && (newPosition.x+borderSize) < winSize.width &&
                (newPosition.y-borderSize) > 0 && (newPosition.y+borderSize) < winSize.height) {
                
                    freePoints.push_back(newPosition);
                
                
            }
            
            
        }
        
        
        if (freePoints.size() > 0) {
            break;
            
        }
        
    }
    
    if (freePoints.size() == 0) {
        return position;
        
    }
    return freePoints.at(random(0, (int)freePoints.size()-1));
       
}
