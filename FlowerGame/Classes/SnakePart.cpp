//
//  SnakePart.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/7/17.
//
//

#include "SnakePart.h"

SnakePart* SnakePart::createHead() {
    

    SnakePart* pSprite = new SnakePart();
    
    if (pSprite->initWithFile("images/monsters/snake/snake_head.png") )
    {
        
        pSprite->autorelease();

        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
    
}


SnakePart* SnakePart::createBody() {
    
    
    SnakePart* pSprite = new SnakePart();
    
    if (pSprite->initWithFile("images/monsters/snake/snake_body.png") )
    {
        
        pSprite->autorelease();
    
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
    
}
