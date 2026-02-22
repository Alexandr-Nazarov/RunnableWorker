#include "myrunnable.h"

//-------------------------------------------------------------------
//
MyRunnable::MyRunnable(Worker *worker):
    worker_(worker)
{

}

//-------------------------------------------------------------------
//
void MyRunnable::run()
{
    worker_->doWork();
}
