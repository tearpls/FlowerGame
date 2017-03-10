//
//  GameField.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/8/17.
//
//

#ifndef GameField_h
#define GameField_h

#include "cocos2d.h"
#include "Monster.h"
#include "Plant.h"

class GameField
{
public:
    
    
    
    static GameField* getInstance();
    
    ~GameField() {};
    
    //Generate 1 for the occuped pixels and 0 for free pixels
    void updateView(std::vector<cocos2d::Sprite*> obstaclesSprites);
    
    //Generate random free points on the game field for spawning new monster
    cocos2d::Vec2 getFreePointForSpawning();
    
    //Check if plant can be placed on the desired position
    bool isFreeForPlant(cocos2d::Point position);
    
    
    cocos2d::Vec2 getFreePointForMove(cocos2d::Vec2 position, float speed, float rotation);
    
private:
    GameField() {};
    
    struct FieldPoint
    {
        FieldPoint(int x, int y) : x(x), y(y) {};
        int x;
        int y;
        
    };
    
    void initOptions();
    
    cocos2d::Size winSize;
    
    static GameField* gameFieldInstance;
    
    //Current Game Field view
    std::vector<std::vector<int> > obstaclesView;
    
    void resetField();
    
    
    const int borderSize = 50;
    
    float getMaxMonsterSize();
    
};

#endif /* GameField_h */
