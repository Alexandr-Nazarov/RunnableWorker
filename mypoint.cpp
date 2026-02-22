#include <QLine>
#include "mypoint.h"

//-------------------------------------------------------------------
//
MyPoint::MyPoint(const QPoint &pt, QColor clr):
    point_(pt),
    color_(clr)
{

}

//-------------------------------------------------------------------
//
void MyPoint::draw(QPainter &painter) const
{
    QPen pen;
    pen.setColor(color_);
    pen.setWidth(3);
    pen.setStyle(Qt::SolidLine);

    painter.setPen(pen);
    const QPoint secondPoint(point_.x(), point_.y() + 20);
    painter.drawLine(QLine(point_, secondPoint));
}

