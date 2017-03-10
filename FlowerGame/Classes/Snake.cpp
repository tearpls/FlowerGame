//
//  Snake.cpp
//  FlowerGame
//
//  Created by ievgenii shcherbina on 3/5/17.
//
//

#include "Snake.h"
#include "GameScene.h"
#include "GameField.h"

USING_NS_CC;


Snake::Snake(cocos2d::Point initPosition)
{
    
    growthTime = growthRate;
    
    snakeParts.emplace_back(SnakePart::createHead());
    snakeParts.back()->setPosition(initPosition);
    snakeParts.back()->setRotation(random(0, 360));
    
    GameScene::gameNode->addChild(snakeParts.back());
    
    currentSpeed = initialSpeed;
    
    nextPoint = snakeParts.back()->getPosition();
    
    currentSpeedUpTime = 0;
    
    forDelete = false;
}

void Snake::update(float dt)
{
    //Check if art could be grown and snake is not marked for deletion
    if (snakeParts.size() < maxParts && !forDelete) {
        growthTime -= dt;
        
        if (growthTime <= 0) {
            //Grow part and reset time
            this->growPart();
            growthTime = growthRate;
        }
        
    }
    
    this->move();
    
    
    currentSpeedUpTime -= dt;
    //Check if speed up time is over and reset snake speed to default
    //Probably implementing states would be better approach
    if (currentSpeed > initialSpeed && currentSpeedUpTime <= 0) {
        currentSpeed = initialSpeed;
    }
    
}

bool Snake::handleTouch(cocos2d::Point touchLocation)
{
    bool isTouched = false;;
    //Check if snake is touched and remove last part of it
    for (auto itr = snakeParts.begin(); itr != snakeParts.end(); ++itr) {
        Rect snakeRectBar = (*itr)->getBoundingBox();
        if (snakeRectBar.containsPoint(touchLocation)) {
            
            snakeParts.back()->removeFromParentAndCleanup(true);
            snakeParts.pop_back();
            isTouched = true;
            break;
        }
        
    }
    
    if (snakeParts.size() == 0) {
        forDelete = true;
    }
    
    return isTouched;
}

void Snake::deleteMe()
{
    delete this;
}


void Snake::growPart()
{
    //Get pointer on the snake's tale
    Sprite* lastPart = snakeParts.back();
    
    SnakePart* body = SnakePart::createBody();
    
    //Calculate x and y coordinate for the new part of the snake
    float x = lastPart->getPosition().x - (lastPart->getContentSize().width+5)*cosf(-lastPart->getRotation()*M_PI/180.0f );
    float y = lastPart->getPosition().y - (lastPart->getContentSize().height+5)*sinf(-lastPart->getRotation()*M_PI/180.0f);
    
    
    Size winSize = Director::getInstance()->getWinSize();
    Size spriteSize = body->getContentSize();
    spriteSize.width *= 1.1f;
    spriteSize.height *= 1.1f;
    
    //Prevent growing outside game field
    if ( (x-spriteSize.width) > 0 && (x+spriteSize.width) < winSize.width &&
        (y-spriteSize.height) > 0 && (y+spriteSize.height) < winSize.height) {
        
        snakeParts.push_back(body);
        snakeParts.back()->setPosition( Vec2(x, y) );
        snakeParts.back()->setRotation(lastPart->getRotation());
        GameScene::gameNode->addChild(snakeParts.back());
    }else {
        log("Growing outside!");
    }
    
    
}



float Snake::calculateRotation(cocos2d::Vec2 currentPoint, Vec2 targetPoint, float currentAngle)
{
    //Find resulting vector and angle of it
    Vec2 deltaVector = currentPoint - targetPoint;
    
    Point firstVector = targetPoint-currentPoint;
    float firstRotateAngle = -firstVector.getAngle();
    
    float endAngle = CC_RADIANS_TO_DEGREES(firstRotateAngle);
    
    if (currentAngle > 0) { currentAngle = fmodf(currentAngle, 360.0f); }
    else { currentAngle = fmodf(currentAngle, -360.0f); }
    
    //Find difference between current angle and desired
    float diffAngle = endAngle - currentAngle;
    
    if (diffAngle > 180) {   diffAngle -= 360; }
    if (diffAngle < -180) { diffAngle += 360; }
    
    return currentAngle + diffAngle*turnRate;
    
}


Vec2 Snake::calculatePosition(Vec2 currentPos, Vec2 targetPos, float deltaDistance)
{
    //Get distance between current position and target position
    float distance  = targetPos.distance(currentPos);
    
    //Calculate new point with current speed
    if(distance > deltaDistance){
    
        float offX = currentPos.x -  targetPos.x;
        float offY = currentPos.y -  targetPos.y;
        
        float direction = atan2f(offY, offX);
        
        Vec2 newPosition = Vec2(currentPos.x + cos(direction) * currentSpeed*-1, currentPos.y + sin(direction)* currentSpeed*-1);
        
        
        return newPosition;

    }
    
    
    return currentPos;
}



void Snake::move()
{
    
    SnakePart* head = snakeParts.front();
    
    //Generate next point if snake is arrived to the previous
    if (head->getPosition().distance(nextPoint) < currentSpeed) {
        
        nextPoint = GameField::getInstance()->getFreePointForMove(snakeParts.front()->getPosition(), currentSpeed, snakeParts.front()->getRotation());
        
    }
    
    //Move Head first
    head->setRotation(this->calculateRotation(head->getPosition(), nextPoint, head->getRotation()));
    head->setPosition(this->calculatePosition(head->getPosition(), nextPoint, 0));
    
    //Move remaining body
    for (auto itr = snakeParts.begin()+1; itr != snakeParts.end(); ++itr) {
        
        Sprite* previusPart = *(itr-1);
        Sprite* currentPart = *itr;
        
        currentPart->setRotation(this->calculateRotation(currentPart->getPosition(), previusPart->getPosition(), currentPart->getRotation()));
        
        currentPart->setPosition(this->calculatePosition(currentPart->getPosition(), previusPart->getPosition(), currentPart->getContentSize().width*1.1f));

        
    }


    
    
}


std::vector<Sprite*> Snake::getSprites()
{
    std::vector<Sprite*> snakeSprites;
    for (auto& snakePart : snakeParts) {
        snakeSprites.push_back(snakePart);
    }
    
    return snakeSprites;
}


void Snake::speedUp()
{
    currentSpeedUpTime = speedUpTime;
    currentSpeed = initialSpeed*speedUpRate;
    
}
