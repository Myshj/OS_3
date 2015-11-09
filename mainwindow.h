#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sectionedmemoryallocator.h"

#include "queuetomemory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_nextTick_clicked();

private:
    Ui::MainWindow *ui;

    SectionedMemoryAllocator allocator;

    QueueToMemory queue;

    unsigned int currentTick;
    unsigned int currentId;
};

#endif // MAINWINDOW_H
