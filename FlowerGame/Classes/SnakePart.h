//
//  SnakePart.h
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/7/17.
//
//

#ifndef SnakePart_h
#define SnakePart_h

#include "cocos2d.h"

class SnakePart : public cocos2d::Sprite
{
public:
    
    ~SnakePart() {};
    static SnakePart* createHead();
    static SnakePart* createBody();
    
private:
    SnakePart() {};

};


#endif /* SnakePart_h */
