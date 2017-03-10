//
//  Plant.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/8/17.
//
//

#ifndef Plant_h
#define Plant_h

class Plant
{
public:
    virtual ~Plant() {};
    
    virtual void update(float dt) = 0;
    
    virtual std::vector<cocos2d::Sprite*> getSprites() = 0;

    virtual bool checkIntersect(std::vector<cocos2d::Sprite*> monstersSprites) = 0;
    
    virtual void removeMe() = 0;
    
    void eatPlant() {eaten = true; };
    
    bool isEaten() {return eaten; };
protected:

    bool eaten;
    
};

#endif /* Plant_h */
