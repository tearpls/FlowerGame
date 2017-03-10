//
//  GameStateManager.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/6/17.
//
//

#include "GameStateManager.h"

GameStateManager* GameStateManager::gsManagerInstance;


GameStateManager* GameStateManager::getInstance()
{
    if (!gsManagerInstance) {
        gsManagerInstance = new GameStateManager();
    }
    
    return gsManagerInstance;
    
}


void GameStateManager::changeState(GameState* state)
{
    //Clean and delete current state
    if (!gameStates.empty()) {
        gameStates.back()->cleanup();
        gameStates.pop_back();
    }
    
    //Init and push the new state
    state->init();
    gameStates.push_back(state);
    
}

void GameStateManager::pushState(GameState* state) {
    //Pause current game state
    if(!gameStates.empty()) {
        gameStates.back()->pause();
    }
    
    //Init new game state
    gameStates.push_back(state);
    state->init();
    
    
}

void GameStateManager::popState()
{
    //Clean and remove current state
    gameStates.back()->cleanup();
    gameStates.pop_back();
    
    //Resume previous state
    if (!gameStates.empty()) {
        gameStates.back()->resume();
    }
    
}



void GameStateManager::handleTouch(cocos2d::Point touchPoint)
{
    if (!gameStates.empty()) {
        gameStates.back()->handleTouch(touchPoint);
    }
    
}
