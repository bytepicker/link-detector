#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icons/icon.png"));

    thread = new QThread;
    detect = new Detector;

    detect->moveToThread(thread);

    connect(this, SIGNAL(requestMacs()), detect, SLOT(getMacs()), Qt::DirectConnection);
    connect(detect, SIGNAL(sendMacs(QStringList)), this, SLOT(getMacs(QStringList)), Qt::DirectConnection);
    emit requestMacs();

    connect(detect, SIGNAL(up(QString)), this, SLOT(up(QString)));
    connect(detect, SIGNAL(down(QString)), this, SLOT(down(QString)));

    connect(thread, SIGNAL(started()), detect, SLOT(watch()));
    thread->start();

    // table styling
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::getMacs(const QStringList &macs)
{
    ui->tableWidget->setRowCount(macs.size());
    ui->tableWidget->setColumnCount(2);

    QStringList labels;
    labels << "MAC" << "Link";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    for(int i = 0; i < macs.size(); i++){
        auto macItem = new QTableWidgetItem(macs.at(i));
        ui->tableWidget->setItem(i, 0, macItem);
    }

    const int rowHeight = ui->tableWidget->rowHeight(0);
    const int scrollHeight = ui->tableWidget->horizontalScrollBar()->height();

    const int totalHeight = rowHeight * macs.size() + (scrollHeight - (macs.size() * (macs.size()-1) - 1));

    ui->tableWidget->setMaximumHeight(totalHeight);
    ui->widget->setMaximumHeight(totalHeight + 10);
    this->setMaximumHeight(totalHeight + 40);

}

void MainWindow::up(const QString &mac)
{
    for(int i = 0; i < ui->tableWidget->rowCount(); i++){
        auto tableMac = ui->tableWidget->model()->data(ui->tableWidget->model()->index(i, 0)).toString();

        if(mac == tableMac){
            auto status = new QTableWidgetItem("Up");
            status->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 1, status);
        }
    }
}

void MainWindow::down(const QString &mac)
{
    for(int i = 0; i < ui->tableWidget->rowCount(); i++){
        auto tableMac = ui->tableWidget->model()->data(ui->tableWidget->model()->index(i, 0)).toString();

        if(mac == tableMac){
            auto status = new QTableWidgetItem("Down");
            status->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 1, status);
        }
    }
}

MainWindow::~MainWindow()
{
    thread->quit();
    this->close();

    delete ui;
}
