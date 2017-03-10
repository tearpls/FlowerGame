//
//  GameScene.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/5/17.
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "GameStateManager.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    virtual void update(float dt) override;
    
    
    static cocos2d::Node* gameNode;
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
private:
    void initListener();
    
};

#endif /* GameScene_h */
