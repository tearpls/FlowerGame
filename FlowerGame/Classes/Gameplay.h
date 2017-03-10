//
//  GameplayGameState.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/6/17.
//
//

#ifndef Gameplay_h
#define Gameplay_h


#include "GameState.h"

class Gameplay : public GameState
{
    
public:

    virtual ~Gameplay() {};
    
    virtual void init() override;
    
    virtual void cleanup () override;
    
    virtual void pause() override;
    
    virtual void resume() override;
    
    virtual void handleTouch(cocos2d::Point touchPoint) override;
    
    //Invokes every frame, dt - time passed from last invoke
    virtual void update(float dt) override;
    
private:
    //Bool to control "update" method
    bool paused;

};



#endif /* GameplayGameState_h */
