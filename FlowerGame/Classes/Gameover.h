//
//  GameoverGameState.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/6/17.
//
//

#ifndef Gameover_h
#define Gameover_h

#include "GameState.h"

class Gameover : public GameState
{
    
public:
    
    virtual ~Gameover() { };
    
    virtual void init() override;
    
    virtual void cleanup () override;
    
    virtual void pause() override;
    
    virtual void resume() override;
    
    virtual void handleTouch(cocos2d::Point touchPoint) override;
    
    virtual void update(float dt) override;
private:
    cocos2d::Label* gameOverText;
    
};



#endif /* GameoverGameState_h */
