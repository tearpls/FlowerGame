//
//  Monster.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/7/17.
//
//

#ifndef Monster_h
#define Monster_h

class Monster
{
public:
    virtual ~Monster() {};
    
    virtual void update(float dt) = 0;
    
    virtual bool handleTouch(cocos2d::Point touchLocation) = 0;
    
    virtual std::vector<cocos2d::Sprite*> getSprites() = 0;
    
    virtual void speedUp() = 0;
    
    void killMonster () {forDelete = true; };
    
    bool isDead () {return forDelete; };
    
    virtual void deleteMe() = 0;
protected:
    bool forDelete;
    
};

#endif /* Monster_h */
