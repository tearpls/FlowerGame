//
//  GameStateManager.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/6/17.
//
//

#ifndef GameStateManager_h
#define GameStateManager_h

#include "GameState.h"


class GameStateManager
{
public:
    
    ~GameStateManager() {};
    
    static GameStateManager* getInstance();
    
    //Change current game state
    void changeState(GameState* state);
    
    //Pause and push game state
    void pushState(GameState* state);
    
    //Pop and resume game state
    void popState();
    
    //Switching from gameplay to pause state and backwards
    void switchPause();
    
    void handleTouch(cocos2d::Point touchPoint);
    
    GameState* getCurrentGameState() {return gameStates.back(); };
    
private:
    GameStateManager() {};
    
    static GameStateManager* gsManagerInstance;

    std::vector<GameState*> gameStates;
    
};

#endif /* GameStateManager_h */
