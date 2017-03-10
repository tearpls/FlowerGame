//
//  GameoverGameState.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/6/17.
//
//

#include "Gameover.h"
#include "Gameplay.h"
#include "GameScene.h"

USING_NS_CC;

void Gameover::init()
{
    
    //Init Welcome Message
    gameOverText = Label::createWithSystemFont("Game is Over!\n Please touch anywhere to restart game!", "Helvetica", 32);
    gameOverText->setAlignment(TextHAlignment::CENTER);
    gameOverText->setPosition(Vec2(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height*0.8f));
    
    GameScene::gameNode->addChild(gameOverText);
    
}


void Gameover::cleanup ()
{
    //Delete welcome message
    gameOverText->removeFromParentAndCleanup(true);
    delete this;
}


void Gameover::pause()
{
    //Make text invisible
    gameOverText->setOpacity(0);
}

void Gameover::resume()
{
    //Show text
    gameOverText->setOpacity(255);
    
}


void Gameover::handleTouch(cocos2d::Point touchPoint)
{
    //Change state to gameplay
    Gameplay* gamePlay = new Gameplay();
    GameStateManager::getInstance()->changeState(gamePlay);
}


void Gameover::update(float dt)
{
    //Do nothing
    
}
