#include <QPainter>
#include <QThread>
#include <QtConcurrent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrunnable.h"
#include "constants.h"

//-------------------------------------------------------------------
//
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    menu_(new QMenu(this)),
    concurrent_(new QAction("QtConcurrent", this)),
    runnable_(new QAction("QRunnable", this)),
    clear_(new QAction("Clear", this))
{
    ui->setupUi(this);
    createmenu();
    connections();
    //test();
    createWorkers();
}

//-------------------------------------------------------------------
//
MainWindow::~MainWindow()
{
    deleteWorkers();
    delete ui;
}

//-------------------------------------------------------------------
//
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    for (const MyPoint &point : vPoints_)
    {
      point.draw(painter);
    }
}

//-------------------------------------------------------------------
//
void MainWindow::test()
{
    x_ = 10;
    Worker *worker = new Worker(&x_, wk::YSTART, Qt::red, this);
    connect (worker, &Worker::signalAddPoint, this, &MainWindow::slotAddPoint);
    worker->doWork();
}

//-------------------------------------------------------------------
//
void MainWindow::createWorkers()
{

    qRegisterMetaType<MyPoint>("MyPoint");     // зарегистрируем MyPoint тип

    for (int i = 0; i < wk::THREADSCOUNT; ++i)
    {
        Worker *worker = new Worker(&x_, wk::YSTART + i *30, Qt::GlobalColor(Qt::red + i % (Qt::transparent - Qt::red)),
                                    this, wk::COUNT);
        connect (worker, &Worker::signalAddPoint, this, &MainWindow::slotAddPoint, Qt::QueuedConnection); //Qt::QueuedConnection т.к в разных потоках и надо зарегистрировать MyPoint
        vWorkers_.append(worker);
    }
}

//-------------------------------------------------------------------
//
void MainWindow::deleteWorkers()
{
    for (Worker* worker : vWorkers_)
     {
         if (worker)
         {
             delete worker;
             worker = nullptr;
         }
     }
     vWorkers_.clear();
}

//-------------------------------------------------------------------
//
void MainWindow::createmenu()
{
    this->setMinimumSize(QSize(wk::COUNT * wk::THREADSCOUNT + 20, 100 + (wk::THREADSCOUNT + 1) * 30 + ui->threadsCount->height() * 2));

    menu_ = menuBar()->addMenu("Commands");
    menu_->addAction(concurrent_);
    menu_->addAction(runnable_);
    menu_->addAction(clear_);

    ui->threadsCount->setText("Ideal Thread Count: " + QString::number(wk::THREADSCOUNT));
}

//-------------------------------------------------------------------
//
void MainWindow::connections()
{
    connect(clear_, &QAction::triggered, this, &MainWindow::onClear);
    connect(concurrent_, &QAction::triggered, this, &MainWindow::slotQtConcurrent);
    connect(runnable_, &QAction::triggered, this, &MainWindow::slotQRunnable);
}

//-------------------------------------------------------------------
//
void MainWindow::slotAddPoint(MyPoint point)
{
    vPoints_.append(point);
    this->repaint();
}

//-------------------------------------------------------------------
//
void MainWindow::onClear()
{
    vPoints_.clear();
    this->repaint();
}

//-------------------------------------------------------------------
//
void MainWindow::slotQtConcurrent()
{
    onClear();
    x_ = 10;
    for (Worker* worker : vWorkers_)
        QtConcurrent::run(worker, &Worker::doWork);
}

//-------------------------------------------------------------------
//
void MainWindow::slotQRunnable()
{
    onClear();
    x_ = 10;
    for (Worker* worker : vWorkers_)
    {
        MyRunnable *runnableTask = new MyRunnable(worker);
        QThreadPool::globalInstance()->start(runnableTask);
    }
}
