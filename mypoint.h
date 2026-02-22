#ifndef MYPOINT_H
#define MYPOINT_H

#include <QPoint>
#include <QColor>
#include <QPainter>


/**
 * @brief Класс точки
 */
class MyPoint
{
public:
    MyPoint(const QPoint &pt = QPoint(), QColor clr = Qt::black);
    /**
     * @brief Рисование цветной точки
     * @param painter
     */
    void draw(QPainter &painter) const;

    const QPoint& point() const {return point_;}

private:
    QPoint point_;
    QColor color_;
};

#endif // MYPOINT_H
