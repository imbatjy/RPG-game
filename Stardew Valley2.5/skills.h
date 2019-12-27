#ifndef SKILLS_H
#define SKILLS_H
#include "moveobjs.h"
#include <vector>
#include <string>
#include <QPainter>
#include <QVector>
#include <QPixmap>
#include <iostream>
using namespace std;
class Skills:public Moveobjs
{
public:
    Skills(string );
    ~Skills();
    void draw(QPainter*);
    int getstart(){return start;}
    int getend(){return end;}
    void setFaceDirection(int);
    int getFaceDirection();
    void startMove(qreal = 0,qreal = 0);
    void endMove();
    void move();
    void logic();
    void setstart(int a){start=a;}
    void setend(int a){end=a;}
    void resetall(){end=0,start=0,timecount1=0,timecount2=0;}
private:
    QVector<QPixmap>hit;//碰撞特效图片
    QVector<QPixmap>moving;//移动特效图片
    QVector<QPixmap>feet;//蓄力特效图片
    int end;//碰撞到物体后触发爆炸特效
    int timecount1,timecount2;
    int start;//触发蓄力特效
    int faceDirection;
    qreal speedX;
    qreal speedY;
    int paceCount;
    bool isMoving;
};

#endif // SKILLS_H
