#ifndef MOVEOBJS_H
#define MOVEOBJS_H
#include<QObject>
#include<QPainter>
#include<QRectF>
#include<QPixmap>
#include<QVector>

class Moveobjs
{

public:
    Moveobjs();
    ~Moveobjs(){}
    void setRect(QRectF);
    void setRect(qreal,qreal,qreal,qreal);//设定碰撞边框
    QRectF& getBindRect();
    void addFrame(QPixmap);//将图片储存到对应方向上的Qvector里面
    void clearAllFrame();
protected:
    QRectF bindRect;
    int frameCount;
    QVector<QPixmap> pixmapListUp;//储存向上的所有动作图片
    QVector<QPixmap> pixmapListDown;//储存向下的所有动作图片
    QVector<QPixmap> pixmapListLeft;//储存向左的所有动作图片
    QVector<QPixmap> pixmapListRight;//储存向右的所有动作图片
    //int pixmapListDirection;
};

#endif // MOVEOBJS_H
