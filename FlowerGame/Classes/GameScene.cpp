//
//  GameScene.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/5/17.
//
//

#include "GameScene.h"
#include "Intro.h"


USING_NS_CC;


Node* GameScene::gameNode;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    gameNode = this;
    
    Intro* introState = new Intro();
    GameStateManager::getInstance()->changeState(introState);
    
    //init touch listener
    this->initListener();
    
    this->scheduleUpdate();
    
    return true;
}


void GameScene::initListener() {
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){
        
        
        return true; // if you are consuming it
    };
    
    
    
    // trigger when you let up
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        
        Point touchLocation = touch->getLocationInView();
        touchLocation = Director::getInstance()->convertToGL(touchLocation);
        Point convertedTouchPos =this->convertToNodeSpace(touchLocation);
        
        GameStateManager::getInstance()->handleTouch(convertedTouchPos);
        
       
    };
    
    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
}


void GameScene::update(float dt)
{
    //Call update every frame for current game state
    GameStateManager::getInstance()->getCurrentGameState()->update(dt);
    
}

