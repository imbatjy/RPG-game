#include "monster.h"
#include <QPointF>
void Monster::initm(){
   if(type=="wolf"){
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 119.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 121.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 123.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 125.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 127.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 129.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 149.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 61.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 63.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 65.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 67.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 69.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 81.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 141.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 95.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 97.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 99.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 101.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 103.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 105.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 145.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 200.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 201.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 202.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 203.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 204.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 205.png"));
    this->addFrame(QPixmap("c:/Qt/map/Images/monster1_move/Image 143.png"));
           this->setlife(40);
   }
    faceDirection = 0;
    paceCount = 0;
    onePaceCount = 0;
    isMoving = true;
    speedX = 0;
    speedY = 0;

    invincible=false;
}
void Monster::logic(){
    if(isMoving)
        move();
    if(life==0)
        bindRect.translate(QPointF(4000,4000));
}
