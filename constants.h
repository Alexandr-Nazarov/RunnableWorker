#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QThread>
namespace wk {
    const int THREADSCOUNT = QThread::idealThreadCount() + 1;   //количество потоков
    const int YSTART = 100;                                     //координата y с которой начнут строиться графики
    const int COUNT = 1000 / THREADSCOUNT;                      //количество циклов для Worker
    const int TIMEOUT = 1000000000;                             //используется длязамедления работы Worker
}

#endif // CONSTANTS_H
