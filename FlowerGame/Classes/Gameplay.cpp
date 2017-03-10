//
//  GameplayGameState.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/6/17.
//
//

#include "Gameplay.h"
#include "Gameover.h"
#include "GameStateManager.h"
#include "MonsterManager.h"
#include "PlantManager.h"
#include "GameScene.h"
#include "MoneyManager.h"


USING_NS_CC;

void Gameplay::init()
{
    //Get device winSize
    Size winSize = Director::getInstance()->getWinSize();
    
    //Reset managers state
    MoneyManager::getInstance()->reset();
    MonsterManager::getInstance()->reset();
    PlantManager::getInstance()->reset();
    
    
    //Create game background
    auto background = Sprite::create("images/environment/background.png");
    background->setPosition(Vec2::ZERO);
    background->setAnchorPoint(Vec2::ZERO);
    background->setScaleX(winSize.width/background->getContentSize().width);
    background->setScaleY(winSize.height/background->getContentSize().height);
    GameScene::gameNode->addChild(background);
    
    
    MoneyManager::getInstance()->addUI();
    
    //Pause gameplay state on init
    paused = true;
    
}


void Gameplay::cleanup ()
{
    GameScene::gameNode->removeAllChildrenWithCleanup(true);
    
    delete this;
}

void Gameplay::pause()
{
    //Pause current activities
    paused = true;
}

void Gameplay::resume()
{
    //Resume current activities
    paused = false;
    
}



void Gameplay::handleTouch(Point touchPoint)
{
    
    //Check if monster touched
    if (!MonsterManager::getInstance()->handleTouch(touchPoint))
    {
        //Place plant if there is no monster
        PlantManager::getInstance()->spawnFlower(touchPoint);
        
    }
    
    //Unpause all activites by first touch
    if (paused) {
        paused = false;
    }
}

void Gameplay::update(float dt)
{
    
    if (!paused) {
        
        PlantManager::getInstance()->update(dt);
        
        MonsterManager::getInstance()->update(dt);
        
        //Check if game is over
        if (MoneyManager::getInstance()->isBankrupt() && !PlantManager::getInstance()->isPlantsAvailable()) {
            Gameover* goState = new Gameover();
            GameStateManager::getInstance()->changeState(goState);
            
        }
        
        
    }
    
}





