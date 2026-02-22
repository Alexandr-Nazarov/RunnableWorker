#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QColor>
#include "mypoint.h"

/**
 * @brief Класс, выполняющий работу по формированию текущих координат точки
 */
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(int *x = nullptr, int y = 0, QColor clr = Qt::black, QObject *parent = nullptr, int count = 200);

    /**
     * @brief Формирование координат
     */
    void doWork();

signals:
    /**
     * @brief Сигнал формирования новой точки
     */
    void signalAddPoint(MyPoint);

public slots:

private:
    const int    y_;        //своя координата y для точки
    int         *x_;        //адрес "общего" x
    const QColor color_;    //свой цвет
    int          count_;    //количество точек для отрисовки потоком
};

#endif // WORKER_H
