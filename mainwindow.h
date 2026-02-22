#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mypoint.h"
#include "worker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    /**
     * @brief Меню
     */
    void createmenu();
    /**
     * @brief Сигналы-слоты
     */
    void connections();
    /**
     * @brief тестовая функция отрисовки
     */
    void test();
    /**
     * @brief Создание объектов Worker
     */
    void createWorkers();
    /**
     * @brief Удаление Workers
     */
    void deleteWorkers();

private slots:
    /**
     * @brief Слот добавления точки
     * @param point
     */
    void slotAddPoint(MyPoint point);
    /**
     * @brief Очистить
     */
    void onClear();
    /**
     * @brief Слот запуска QtConcurrent
     */
    void slotQtConcurrent();
    /**
     * @brief Слот запуска от QRunnable
     */
    void slotQRunnable();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow   *ui;
    QMenu            *menu_;
    QAction          *concurrent_;
    QAction          *runnable_;
    QAction          *clear_;
    QVector<MyPoint> vPoints_;
    int              x_;            //общая координата для всех потоков
    QVector< Worker*> vWorkers_;
};

#endif // MAINWINDOW_H
