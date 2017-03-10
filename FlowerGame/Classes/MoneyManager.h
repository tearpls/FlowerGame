//
//  MoneyManager.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/9/17.
//
//

#ifndef MoneyManager_h
#define MoneyManager_h

#include "cocos2d.h"

class MoneyManager
{
public:
    static MoneyManager* getInstance();
    
    void addMoney(int money);
    
    bool isMoneyAvailable(int count) {return currentMoney >= count; };
    
    void addUI();
    
    void reset();
    
    bool isBankrupt() {return currentMoney < moneyMinimum; };
private:
    static MoneyManager* mmInstance;
    
    
    cocos2d::Label* totalMoneyLabel;
    
    const int initMoney = 150;
    
    int currentMoney;
    
    const int moneyMinimum = 50;
    
};

#endif /* MoneyManager_h */
