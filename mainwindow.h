#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
#pragma pack (1)
class /*alignas(8)*/ MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double** TwoDimArrDbl;
    int arrSize;

    uint8_t* OneDimArrChar;
};

#endif // MAINWINDOW_H
