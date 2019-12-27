#include "player.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "moveobjs.h"
using namespace std;
//direction =1,2,3,4 for 上下左右
void Player::initp()
{

    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 119.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 121.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 123.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 125.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 127.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 129.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 149.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 71.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 73.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 75.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 77.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 79.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 81.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 141.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 95.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 97.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 99.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 101.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 103.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 105.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 143.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 200.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 201.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 202.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 203.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 204.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 205.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/heromove/Image 145.png"));
    faceDirection = 0;
    paceCount = 0;
    onePaceCount = 0;
    isMoving = false;
    speedX = 0;
    speedY = 0;

    //blood = 100;
    invincible=true;
}

void Player::setFaceDirection(int fd)
{

    faceDirection = fd;
}

int Player::getFaceDirection()
{
    return faceDirection;
}

void Player::startMove(qreal dx,qreal dy)
{
    isMoving = true;
    speedX = dx;
    speedY = dy;
}

void Player::endMove()
{
    isMoving = false;
    speedX = 0;
    speedY = 0;
}

void Player::move()
{
    bindRect.translate(speedX,0);
    bindRect.translate(0,speedY);
    //static int cnt = 0;
    if(onePaceCount == 6)
    {
        onePaceCount = 0;
        paceCount++;
    }
    onePaceCount++;
}

/*void Player::attack()
{
    emit attackSignal(this);
}

void Player::skill()
{
    emit skillSignal(this);
}*/

void Player::draw(QPainter* painter)
{
    painter->save();
    //static int cnt = 0;
    paceCount = (paceCount == 6?0:paceCount);//没六步重置一次图片使动作连贯
    switch(faceDirection)
    {
    case 1:{
        if(this->life>0)painter->drawPixmap(bindRect.topLeft(),pixmapListUp[paceCount]);
        else painter->drawPixmap(bindRect.topLeft(),pixmapListUp[6]);//如果死了show出死亡图片
                break;
    }
    case 2:{
        if(life>0)painter->drawPixmap(bindRect.topLeft(),pixmapListDown[paceCount]);
        else painter->drawPixmap(bindRect.topLeft(),pixmapListDown[6]);
        break;}
    case 3:{
        if(life>0)painter->drawPixmap(bindRect.topLeft(),pixmapListLeft[paceCount]);
        else painter->drawPixmap(bindRect.topLeft(),pixmapListLeft[6]);
        break;
    }
    case 4:{
        if(life>0)painter->drawPixmap(bindRect.topLeft(),pixmapListRight[paceCount]);
        else painter->drawPixmap(bindRect.topLeft(),pixmapListRight[6]);
        break;}
    default:break;
    }
    if(invincible){painter->setPen(QColor(Qt::red));
    painter->drawRect(this->bindRect);}
    painter->restore();
}

void Player::logic()
{

    if(isMoving)
        move();

    /*if(bindRect.intersects(enemyAttack->getBindRect()))
        emit attacked(3);
    if(bindRect.intersects(enemySkill->getBindRect()))
        emit skilled(8);*/
}
