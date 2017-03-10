//
//  Flower.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/8/17.
//
//

#include "Flower.h"
#include "MoneyManager.h"


Flower* Flower::create() {
    
    Flower* pSprite = new Flower();
    
    if (pSprite->initWithFile("images/plants/flower/flower.png") )
    {
        
        pSprite->autorelease();
        pSprite->initOptions();
        
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
    
}

void Flower::initOptions()
{
    
    eaten = false;
    currentMoneyGainTime = moneyGainfrequency;
    
}

void Flower::update(float dt)
{
    currentMoneyGainTime -= dt;
    if (currentMoneyGainTime <= 0 && !eaten) {
        
        MoneyManager::getInstance()->addMoney(moneyGainRate);
        currentMoneyGainTime = moneyGainfrequency;
    }
    
    
}

std::vector<cocos2d::Sprite*> Flower::getSprites()
{
    std::vector<cocos2d::Sprite*> sprites;
    sprites.push_back(this);
    
    return sprites;
}


bool Flower::checkIntersect(std::vector<cocos2d::Sprite*> monstersSprites)
{
    
    cocos2d::Rect flowerRectBar = this->getBoundingBox();
    
    for (const auto& sprite : monstersSprites) {
        
        cocos2d::Rect monsterRectBar = sprite->getBoundingBox();
        monsterRectBar.size.width *= 0.7f;
        monsterRectBar.size.height *= 0.7f;
        
        if (flowerRectBar.intersectsRect(monsterRectBar)) {

            return true;

        }

    }
    
    return false;
}


void Flower::removeMe()
{
    this->removeFromParentAndCleanup(true);
}
