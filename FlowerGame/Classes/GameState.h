//
//  GameState.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/6/17.
//
//

#ifndef GameState_h
#define GameState_h

#include "cocos2d.h"

class GameState
{
public:
    virtual ~GameState() {};
    
    virtual void init() = 0;
    virtual void cleanup () = 0;
    
    virtual void pause() = 0;
    
    virtual void resume() = 0;
    
    virtual void handleTouch(cocos2d::Point touchPoint) = 0;
    
    //Calls every frame
    virtual void update(float dt) = 0;
    

};

#endif /* GameState_h */
