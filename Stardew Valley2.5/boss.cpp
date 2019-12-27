#include "boss.h"
#include <QPixmap>
#include <QPointF>
void Boss::initp()
{

    addFrame(QPixmap("c:/Qt/map/Images/bossmove/up1.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/up2.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/up3.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/up4.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/up5.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/up6.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/up6.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/down1.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/down2.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/down3.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/down4.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/down5.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/down6.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/down6.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/left1.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/left2.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/left3.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/left4.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/left5.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/left6.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/left6.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/right1.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/right2.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/right3.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/right4.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/right5.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/right6.png"));
    addFrame(QPixmap("c:/Qt/map/Images/bossmove/right6.png"));

    faceDirection = 0;
    paceCount = 0;
    onePaceCount = 0;
    isMoving = true;
    speedX = 0;
    speedY = 0;
    this->setlife(300);
    invincible=false;

}

Boss::~Boss()
{

}
void Boss::move()
{
    if(bindRect.left()+speedX < 0||bindRect.right()+speedX > 1000)
       speedX=-speedX;
    if(bindRect.top()+speedY < 0||bindRect.bottom()+speedY > 700)
       speedY=-speedY;
         bindRect.translate(speedX,0);
        bindRect.translate(0,speedY);
    //static int cnt = 0;
    paceCount++;
}

