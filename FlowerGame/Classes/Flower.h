//
//  Flower.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/8/17.
//
//

#ifndef Flower_h
#define Flower_h

#include "cocos2d.h"
#include "Plant.h"

class Flower : public cocos2d::Sprite, public Plant
{
public:
    
    ~Flower() {};
    static Flower* create();
    
    
    virtual void update(float dt) override;
    
    virtual std::vector<cocos2d::Sprite*> getSprites() override;
    
    virtual bool checkIntersect(std::vector<cocos2d::Sprite*> monstersSprites) override;
    
    virtual void removeMe() override;
    

    
private:
    Flower() {};
    
    void initOptions();
    
    cocos2d::Vec2 previousPosition;
    float previousRotation;
    
    const float moneyGainfrequency = 3.0f;
    
    float currentMoneyGainTime;
    
    const int moneyGainRate = 5;
    
};

#endif /* Flower_h */
