#include "skills.h"
static int x=96;
Skills::Skills(string a)
{
    if(a=="fire"){
        QPixmap map1("C:\\Qt\\map\\Images\\skills\\firehit.png");
        moving.append(map1.copy(QRect(2*x,2*x,x,x)));
        for(int i=0;i<24;i++)
            hit.append(map1.copy(QRect(i%5*x,i/5*x,x,x)));
        QPixmap map2("c:\\Qt\\map\\Images\\skills\\firefeet.png");
        for(int i=0;i<16;i++)
            feet.append(map2.copy(QRect(i%5*x,i/5*x,x,x)));
    }else if(a=="thunder"){
        QPixmap map1("c:\\Qt\\map\\Images\\skills\\thunderhit.png");
        moving.append(map1.copy(2*x,0,x,x));
        for(int i=0;i<7;i++){
            hit.append(map1.copy(QRect(i%5*x,i/5*x,x,x)));
            hit.append(map1.copy(QRect(i%5*x,i/5*x,x,x)));
        }
         QPixmap map2("c:\\Qt\\map\\Images\\skills\\thunderfeet.png");
        for(int i=0;i<16;i++){
            feet.append(map2.copy(QRect(i%5*x,i/5*x,x,x)));
        }
    }
    start=3;
    paceCount=0;
    timecount1=0;
    timecount2=0;
    end=0;
    speedX = 0;
    speedY = 0;
    isMoving=false;
}

Skills::~Skills()
{

}
void Skills::draw(QPainter *painter){

    if(timecount1==feet.count()){
        timecount1=0;
        start=1;
    }
    if(timecount2==hit.count()){
        timecount2=0;
        end=0;
        start=3;
    }
    if(start==1){
        painter->drawPixmap(bindRect.topLeft()-QPointF(32,32),moving[paceCount]);
    }else if(start==0){
        painter->drawPixmap(bindRect.topLeft(),feet[timecount1]);
        timecount1++;
    }
    if(end==1){
        painter->drawPixmap(bindRect.topLeft(),hit[timecount2]);
        timecount2++;
    }

    //painter->drawPixmap(bindRect.topLeft(),feet[0]);
    painter->restore();
}
void Skills::setFaceDirection(int fd)
{

    faceDirection = fd;
}

int Skills::getFaceDirection()
{
    return faceDirection;
}

void Skills::startMove(qreal dx,qreal dy)
{
    isMoving = true;
    speedX = dx;
    speedY = dy;
}

void Skills::endMove()
{
    isMoving = false;
    speedX = 0;
    speedY = 0;
}

void Skills::move()
{
    bindRect.translate(speedX,0);
    bindRect.translate(0,speedY);
    //static int cnt = 0;
    //paceCount++;
}
void Skills::logic(){
    if(isMoving&&start==1)
        move();
    if(end==0&&start==3)
        bindRect.translate(QPointF(4000,1000));//结束后将碰撞边框去除
}
