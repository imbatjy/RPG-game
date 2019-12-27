#include "moveobjs.h"

Moveobjs::Moveobjs()
{
    frameCount = 0;//设定加载顺序
    //pixmapListDirection = 0;
}

void Moveobjs::setRect(QRectF rect)
{
    bindRect = rect;
}

void Moveobjs::setRect(qreal x, qreal y, qreal w, qreal h)
{
    bindRect.setRect(x,y,w,h);
}

QRectF& Moveobjs::getBindRect()
{
    return bindRect;
}

void Moveobjs::addFrame(QPixmap pixmap)
{
    if(pixmap.isNull())
        return;
    static int cnt = 0,direction = 0;//设定加载顺序
    if(cnt == 7)
    {
        cnt = 0;
        direction++;
        direction = direction == 4?0:direction;
        //pixmapListDirection++;
    }
    switch(direction)
    {
    case 0:pixmapListUp.append(pixmap);break;
    case 1:pixmapListDown.append(pixmap);break;
    case 2:pixmapListLeft.append(pixmap);break;
    case 3:pixmapListRight.append(pixmap);break;
    default:break;
    }
    cnt++;
    frameCount++;
}

void Moveobjs::clearAllFrame()
{
    //pixmapList.clear();
    frameCount = 0;
}

