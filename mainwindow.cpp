#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "random"
#include "process.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentTick = 0;
    currentId = 0;

    queue = QueueToMemory(allocator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_nextTick_clicked()
{
    if(ui->possibilityOfIncome->value() > rand()%101){
        queue.AddNew(Process(currentId,
                             currentTick,
                             rand()%11 + 1,
                             rand()%ui->maximumTaskLength->value() + ui->minimumTaskLength->value())
                     );

        currentId++;
    }

    queue.MainCycle();
    ui->processesView->setText(QString::fromStdString(queue.ToString()));

    ui->memoryView->setText(QString::fromStdString(allocator.ToString()));

    currentTick++;
}
