//
//  IntroGameState.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/6/17.
//
//

#ifndef Intro_h
#define Intro_h

#include "GameState.h"


class Intro : public GameState
{
    
public:
    
    virtual ~Intro() { };
    
    virtual void init() override;
    virtual void cleanup () override;
    
    virtual void pause() override;
    
    virtual void resume() override;

    virtual void handleTouch(cocos2d::Point touchPoint) override;
    
    virtual void update(float dt) override;
private:
    cocos2d::Label* introText;
    
};

#endif /* IntroGameState_h */
