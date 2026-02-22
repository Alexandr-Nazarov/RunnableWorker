#ifndef MYRUNNABLE_H
#define MYRUNNABLE_H

#include <QRunnable>
#include "worker.h"

class MyRunnable : public QRunnable
{
public:
    MyRunnable(Worker *worker);
    /**
     * @brief Виртуальный перегруженный run
     */
    void run();

private:
    Worker *worker_;

};

#endif // MYRUNNABLE_H
