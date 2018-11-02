#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QScrollBar>
#include "detector.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void requestMacs();

protected slots:
    void getMacs(const QStringList &macs);
    void up(const QString &mac);
    void down(const QString &mac);

private:
    Ui::MainWindow *ui;
    QThread *thread;
    Detector *detect;
};

#endif // MAINWINDOW_H
