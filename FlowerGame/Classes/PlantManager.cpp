//
//  PlantManager.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/8/17.
//
//

#include "PlantManager.h"
#include "MonsterManager.h"
#include "GameField.h"
#include "Flower.h"
#include "MoneyManager.h"


USING_NS_CC;

PlantManager* PlantManager::pmInstance;

PlantManager* PlantManager::getInstance()
{
    if (!pmInstance) {
        pmInstance = new PlantManager();
        
        
        
    }
    
    return pmInstance;
}

void PlantManager::reset()
{
    
    plants.clear();
}

void PlantManager::spawnFlower(cocos2d::Point position)
{
    if (MoneyManager::getInstance()->isMoneyAvailable(flowerPrice) && GameField::getInstance()->isFreeForPlant(position)) {
        
        MoneyManager::getInstance()->addMoney(-flowerPrice);
        
        Flower* flower = Flower::create();
        flower->setPosition(position);
        GameScene::gameNode->addChild(flower);
        
        plants.push_back(flower);
    }


    
}

void PlantManager::update(float dt)
{
    
    std::vector<Sprite*> monstersSprites = MonsterManager::getInstance()->getSprites();
    
    for (const auto& plant : plants)
    {
        plant->update(dt);
        
        if (plant->checkIntersect(monstersSprites)) {
            plant->eatPlant();
            MonsterManager::getInstance()->speedUpMonsters();
        }
    }
    
    auto plantItr = std::find_if(plants.begin(), plants.end(),  [](Plant* plant) {return plant->isEaten(); });
    if (plantItr != plants.end()) {
        
        (*plantItr)->removeMe();
        plants.erase(plantItr);
    }
    
    
    
    
}

std::vector<cocos2d::Sprite*> PlantManager::getSprites()
{
    std::vector<Sprite*> plantSprites;
    
    for (auto& plant: plants) {
        std::vector<Sprite*> sprites = plant->getSprites();
        plantSprites.insert(plantSprites.end(), sprites.begin(),  sprites.end());
    }
    
    return std::move(plantSprites);
    
}




cocos2d::Size PlantManager::getPlantSize()
{
    //Create texture and get size of it
    //Better approach would be creating settings xml/json with all plants settings
    Image* image = new Image();
    image->initWithImageFile("images/plants/flower/flower.png");
    
    Texture2D* texture = new Texture2D();
    texture->initWithImage(image);
    
    return texture->getContentSize();
}
