#ifndef RPGOBJ_H
#define RPGOBJ_H
#include <QImage>
#include <QPainter>
#include <string>
#include <icon.h>
#include <map>
#include <QRectF>
using namespace std;
class RPGObj
{
public:
    RPGObj(){}

    void initObj(string type);
    void show(QPainter * painter);

    void setPosX(int x){this->_pos_x=x;}
    void setPosY(int y){this->_pos_y=y;}
    void setRect(qreal,qreal,qreal,qreal);//设定碰撞体积，碰撞逻辑判断以边框为准

    int getPosX() const{return this->_pos_x;}
    int getPosY() const{return this->_pos_y;}
    int getHeight() const{return this->_icon.getHeight();}
    int getWidth() const{return this->_icon.getWidth();}
    QRectF getBindRect(){return this->range;}//返回边框

    bool canCover() const{return this->_coverable;}//能否站上去
    bool canEat() const{return this->_eatable;}//能否被吃掉
    bool canDead() const{return this->_deadable;}//碰到是否会减血
    bool cantalk(){return this->_talkable;}//碰到后是否会触发对话
    bool canBang(){return this->_bang;}//碰到后是否会反弹
    string talks(){return this->_talk;}//储存触发的对话内容
    string getObjType() const{return this->_icon.getTypeName();}//返回类名

protected:
    //所有坐标，单位均为游戏中的格

    QImage _pic;
    int _pos_x, _pos_y;//该物体在游戏中当前位置（左上角坐标）
    ICON _icon;//可以从ICON中获取对象的素材，尺寸等信息
    bool _coverable;
    bool _eatable;
    bool _deadable;
    bool _bang=false;
    string _talk="0";
    bool _talkable;
    QRectF range;
};

#endif // RPGOBJ_H
