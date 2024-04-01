#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QDebug>
#include <cmath>
#include <cstdio>

double TwoDimNormalDistrib(double a, double sigma, double xBegin, double xEnd, int arrSize, double** arr);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    arrSize = 8;

    TwoDimArrDbl = (double**)malloc(sizeof(double*) * (arrSize+1));
    for(int i = 0; i < (arrSize+1); i++)
        TwoDimArrDbl[i] = (double*)malloc(sizeof(double) * (arrSize+1));

    double a = 0.0;
    double sigma = 1.0;
    double xBegin = -3.0;
    double xEnd = 3.0;

    double maxValue = TwoDimNormalDistrib(a, sigma, xBegin, xEnd, arrSize, TwoDimArrDbl);

    OneDimArrChar = (uint8_t*)malloc((arrSize+1)*(arrSize+1));

    int limits;
    if(arrSize%2)
        limits = arrSize + 1;
    else
        limits = arrSize;

    for(int i = 0; i < limits; i++)
    {
        for(int j = 0; j <limits; j++)
        {
            OneDimArrChar[i*(limits) + j] = (uint8_t)(255.0*TwoDimArrDbl[i][j]/maxValue);
            printf("%d ", OneDimArrChar[i*(limits) + j]);
        }
        printf("\n");
    }

    //QImage image;
    //image.load("../normalDistrib.png");
    //bool result = image.loadFromData(OneDimArrChar, (arrSize+1)*(arrSize+1), nullptr);
    QImage image(&OneDimArrChar[0], (arrSize), (arrSize), QImage::Format_Grayscale8);

    qDebug() << image << endl;
    ui->label->setPixmap(QPixmap::fromImage(image));

}

MainWindow::~MainWindow()
{
    for(int i = 0; i < (arrSize+1); i++)
        free(TwoDimArrDbl[i]);
    free(TwoDimArrDbl);

    free(OneDimArrChar);

    delete ui;
}

double NormalDistrib(double a, double sigma, double x)
{
    double power = - (pow((x - a), 2.0))/(2.0 * sigma*sigma);
    double mult = 1.0/(sigma*sqrt(2.0 * M_PI));
    double result = mult * pow(M_E, power);
    return result;
}

void OneDimNormalDistrib(double a, double sigma, double xBegin, double xEnd, int arrSize, double* arr)
{
    double xStep = (xEnd - xBegin)/((double)(arrSize));
    double x = xBegin;

    int limits;
    if(arrSize%2)
        limits = arrSize + 1;
    else
        limits = arrSize;

    for(int i = 0; i < arrSize; i++)
    {
        arr[i] = NormalDistrib(a, sigma, x);
        x += xStep;
    }
}

double TwoDimNormalDistrib(double a, double sigma, double xBegin, double xEnd, int arrSize, double** arr)
{
    double* arrX = new double[arrSize+1];
    double* arrY = new double[arrSize+1];

    OneDimNormalDistrib(a, sigma, xBegin, xEnd, arrSize, arrX);
    OneDimNormalDistrib(a, sigma, xBegin, xEnd, arrSize, arrY);

    double maxValue = arrX[0] * arrY[0];
    int limits;
    if(arrSize%2)
        limits = arrSize + 1;
    else
        limits = arrSize;

    for(int i = 0; i < arrSize; i++)
    {
        for(int j = 0; j < arrSize; j++)
        {
            arr[i][j] = arrX[i] * arrY[j];
            if(arr[i][j] > maxValue)
                maxValue = arr[i][j];
        }
    }

    delete []arrX;
    delete []arrY;
    return maxValue;
}
