//
//  Snake.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/5/17.
//
//

#ifndef Snake_h
#define Snake_h

#include "Monster.h"
#include "SnakePart.h"
#include "cocos2d.h"

class Snake : public Monster
{
public:
    Snake (cocos2d::Point initPosition);
    ~Snake () {};
    
    virtual void update(float dt) override;
    
    virtual bool handleTouch(cocos2d::Point touchLocation) override;
    
    virtual std::vector<cocos2d::Sprite*> getSprites() override;
    
    virtual void speedUp() override;
    
    virtual void deleteMe() override;
private:
    std::vector<SnakePart*> snakeParts;
    
    //Part growth frequency
    const float growthRate = 3.0f;
    
    //Current time to next part growing
    float growthTime;
    
    const int maxParts = 5;
    
    void growPart();
    
    //Move snake
    void move();
    
    //Default snake speed
    const float initialSpeed = 2.0f;
    
    float currentSpeed;
    
    cocos2d::Vec2 nextPoint;
    
    const float turnRate = 0.15f;
    
    float calculateRotation(cocos2d::Vec2 currentPoint, cocos2d::Vec2 nextPoint, float currentAngle);
    
    cocos2d::Vec2 calculatePosition(cocos2d::Vec2 vector1, cocos2d::Vec2 vector2, float deltaDistance);
    
    const float speedUpRate = 2.0f;
    
    const float speedUpTime = 5.0f;
    
    float currentSpeedUpTime;
};

#endif /* Snake_h */
