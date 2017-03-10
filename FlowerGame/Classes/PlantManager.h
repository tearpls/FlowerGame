//
//  PlantManager.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/8/17.
//
//

#ifndef PlantManager_h
#define PlantManager_h

#include "Plant.h"
#include "Flower.h"
#include "cocos2d.h"

class PlantManager
{
public:
    static PlantManager* getInstance();
    
    void reset();
    
    void update (float dt);
    
    std::vector<cocos2d::Sprite*> getSprites();
    
    void spawnFlower(cocos2d::Point position);
    
    //Check if there any plants on the game field
    bool isPlantsAvailable () {return plants.size() > 0;};
    
private:
    static PlantManager* pmInstance;
    
    std::vector<Plant*> plants;
    
    const int flowerPrice = 50;
    
    
};

#endif /* PlantManager_h */
