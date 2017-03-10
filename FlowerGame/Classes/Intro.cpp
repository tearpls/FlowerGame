//
//  IntroGameState.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/6/17.
//
//

#include "Intro.h"
#include "Gameplay.h"
#include "GameStateManager.h"
#include "GameScene.h"

USING_NS_CC;

void Intro::init()
{
    
    //Init Welcome Message
    introText = Label::createWithSystemFont("Welcome to the Flower Game! \n Please touch anywhere to start the game!", "Helvetica", 32);
    introText->setAlignment(TextHAlignment::CENTER);
    introText->setPosition(Vec2(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height*0.8f));
    
    GameScene::gameNode->addChild(introText);
    
}


void Intro::cleanup ()
{
    //Delete welcome message
    introText->removeFromParentAndCleanup(true);
    delete this;
}


void Intro::pause()
{
    //Make text invisible
    introText->setOpacity(0);
}

void Intro::resume()
{
    //Show text
    introText->setOpacity(255);

}



void Intro::handleTouch(cocos2d::Point touchPoint)
{
    //Change state to gameplay
    Gameplay* gameplayState = new Gameplay();
    GameStateManager::getInstance()->changeState(gameplayState);
}


void Intro::update(float dt)
{
    //Do nothing
    
}
