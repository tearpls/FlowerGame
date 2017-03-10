//
//  MoneyManager.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/9/17.
//
//

#include "MoneyManager.h"
#include "GameScene.h"

USING_NS_CC;

MoneyManager* MoneyManager::mmInstance;


MoneyManager* MoneyManager::getInstance()
{
    if (!mmInstance) {
        
        mmInstance = new MoneyManager();
        
    }
    
    return mmInstance;
}


void MoneyManager::reset()
{
    currentMoney = initMoney;
}


void MoneyManager::addUI()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    char buffer[10];
    std::sprintf(buffer, "%d", currentMoney);
    
    //Add coin icon
    auto coinIcon = Sprite::create("images/coin.png");
    coinIcon->setPosition(Vec2(winSize.width*0.85f, winSize.height*0.95f));
    GameScene::gameNode->addChild(coinIcon);
    
    
    //Add label with current money 
    totalMoneyLabel = Label::createWithSystemFont(buffer, "Helvetica", 32);
    totalMoneyLabel->setAlignment(TextHAlignment::LEFT);
    totalMoneyLabel->setColor(Color3B::RED);
    totalMoneyLabel->setPosition(Vec2(coinIcon->getPosition().x + coinIcon->getContentSize().width*1.2f, coinIcon->getPosition().y));
    GameScene::gameNode->addChild(totalMoneyLabel);

    
}

void MoneyManager::addMoney(int money)
{
    currentMoney += money;
    
    char buffer[50];
    std::sprintf(buffer, "%d", currentMoney);
    
    totalMoneyLabel->setString(buffer);
    
    
}
