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
    //Get monster size and add 0.05% for free gap
    float monsterSize = getMaxMonsterSize()*1.05f;
    this->resetField();
    
    //Reserve points by monsters (monster.position +- half of the monster size)
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

        //Fill in reserved aread with 1
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
    
    //Update view with plants and monsters to prevent monster spawning on another monster/snake
    this->updateView(obstacles);
    

    //Create vector with random not reserved points
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
        try {

            FieldPoint freePoint = freePoints.at(random(0, (int)freePoints.size()-1));
            
            spawnPoint.x = freePoint.x;
            spawnPoint.y = freePoint.y;

        } catch (const std::out_of_range& exp) {
            log("Out of range");
        }
        
    }
    
  
    return spawnPoint;
    
}


bool GameField::isFreeForPlant(cocos2d::Point position)
{
    
    //Update view with monsters to prevent placing plant on monster
    this->updateView(MonsterManager::getInstance()->getSprites());
    
    float spriteSize = this->getMaxMonsterSize();
    
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
    //Using i for "slicing" distance to the next point for smooth movement
    for (int i = 1; i < 11; ++i) {
        //Next point random generation
        //Angle 180 is chosen, but probably this value should be from the some kind of monster settings
        for (int deltaAngle = -90; deltaAngle <= 90; deltaAngle+=10) {
            
            
            float newAngle = rotation+deltaAngle;
            
            //Calculate new position with current rotation
            Vec2 newPosition = position;
            
            newPosition.x += speed*150.0f/i*cosf(newAngle*M_PI/180.0f);
            newPosition.y += speed*150.0f/i*sinf(newAngle*M_PI/180.0f);
            
            //Check that New position should be within game borders to prevent snake from moving outside game field
            if ( (newPosition.x-borderSize) > 0 && (newPosition.x+borderSize) < winSize.width &&
                (newPosition.y-borderSize) > 0 && (newPosition.y+borderSize) < winSize.height) {
                
                    freePoints.push_back(newPosition);
                
            }
            
            
        }
        
        //Check if some free points are generated to prevent futher slicing
        if (freePoints.size() > 0) {
            break;
        }
        
    }
    
    
    if (freePoints.size() == 0) {
        return position;
        
    }
    return freePoints.at(random(0, (int)freePoints.size()-1));
       
}
