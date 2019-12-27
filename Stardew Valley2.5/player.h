#ifndef PLAYER_H
#define PLAYER_H
#include "rpgobj.h"
#include <vector>
#include <string>
#include "moveobjs.h"
#include "icon.h"
#include "skills.h"

class Player: public Moveobjs
{
protected:
    int faceDirection;//人物朝向
    int paceCount;//人物脚步
    int onePaceCount;
    int life;//生命值
    bool isMoving;
    qreal speedX;//x移动速度
    qreal speedY;//y移动速度
    //int blood;
    bool invincible;//是否无敌
public:
    Player(){}
    void initp();
    void draw(QPainter*);
    void logic();//相关逻辑判断
    void setFaceDirection(int);//设定朝向
    int getFaceDirection();
    void startMove(qreal = 0,qreal = 0);//设定x、y速度
    void endMove();//停止移动
    void move();//移动人物
    void set_invincible(bool a){invincible=a;}
    void setlife(int a){life=a;}
    int getlife(){return life;}
    bool get_invincible(){return invincible;}
    QRectF trans(int a,int b){return bindRect.translated(a,b);}//移动碰撞边框
    void transed(int a,int b){bindRect.translate(a,b);}
    //void attackSignal(Player*);
    //void skillSignal(Player*);
    //void attacked(int);
    //void skilled(int);
};

#endif // PLAYER_H
