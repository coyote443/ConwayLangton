#include <QtWidgets>
#include <math.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "antwidget.h"
#include "lifewidget.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_antBoardSize      = QSize(640, 380);
    m_antWidget         = new AntWidget(this);
    m_antCurrentImage   = QImage(m_antBoardSize, QImage::Format_Mono);
    m_antCurrentImage.fill(0);

    m_lifeBoardSize     = QSize(640,380);
    m_lifeWidget        = new AntWidget(this);
    m_lifeCurrentImage  = QImage(m_lifeBoardSize, QImage::Format_Mono);

    m_lifeWidget->setFixedSize(760,450);
    m_lifeWidget->move(20,90);
    m_antWidget->setFixedSize(760,450);
    m_antWidget->move(20,90);

    ui->antWidget = m_antWidget;
    ui->lifeWidget= m_lifeWidget;

}

MainWindow::~MainWindow()
{
    delete ui;
}


//// LIFE CODE

void MainWindow::on_lifeStartStopButton_clicked(bool checked){
    m_lifeIsRunning = !m_lifeIsRunning;
    lifeCalculate();
}

void MainWindow::on_lifeClearButton_clicked(){
    m_lifeCurrentImage.fill(DEAD);
    m_lifeWidget->setImage(m_lifeCurrentImage);
}

void MainWindow::on_lifeRandomPopButton_clicked(){
    qsrand(QTime::currentTime().msec());
    for (int i = 0; i < 10000; ++i) {
        int rx = qrand() % m_lifeBoardSize.width();
        int ry = qrand() % m_lifeBoardSize.height();
        m_lifeCurrentImage.setPixel(rx, ry, ALIVE);
    }
    m_lifeWidget->setImage(m_lifeCurrentImage);
}


void MainWindow::lifeCalculate() {
    int widthSize   = m_lifeCurrentImage.width(),
        heightSize  = m_lifeCurrentImage.height();

    while(m_lifeIsRunning == true){
        qApp->processEvents();          /* Niech GUI przetwarza również zdarzenia! */
        m_lifeNumGeneration++;
        QImage next = m_lifeCurrentImage;
        for(int widPos = 0; widPos < widthSize; widPos++){
            for(int heiPos = 0; heiPos < heightSize; heiPos++){
                int  pixNeighboors = lifeNeighborCount(m_lifeCurrentImage, widPos, heiPos);
                bool isAlive = (m_lifeCurrentImage.pixelIndex(widPos,heiPos) == ALIVE);

                if(isAlive){
                    if(pixNeighboors != 2 && pixNeighboors != 3)
                        next.setPixel(widPos, heiPos, DEAD);
                }
                else
                    if(pixNeighboors == 3)
                       next.setPixel(widPos, heiPos, ALIVE);
            }
        }
        m_lifeCurrentImage = next;
        m_lifeWidget->setImage(m_lifeCurrentImage);
    }
}

int MainWindow::lifeNeighborCount(const QImage& img, int x, int y) {
    int retval = 0;
    if(x > 1 && y > 1 && x < img.width() - 1 && y < img.height() - 1){
        for(int widt = x - 1; widt < x + 2; widt ++){
            for(int heit = y - 1; heit < y + 2; heit ++){
                if(widt == x && heit == y) continue;
                if (ALIVE == img.pixelIndex(widt, heit))
                    retval++;
            }
        }
    }
    return retval;
}

//// END LIFE CODE


//// ANT CODE
void MainWindow::on_antStartStopButton_clicked(bool checked){
    m_antIsRunning = !m_antIsRunning;
    antCalculate();
}

void MainWindow::on_antClearButton_clicked(){
    m_antCurrentImage.fill(DEAD);
    m_antWidget->setImage(m_antCurrentImage);
}

void MainWindow::on_addNewAntButton_clicked(){
    m_antCurrentImage.setPixel(myPos.first, myPos.second, ALIVE);
}


Pos MainWindow::antRotateMe(bool Clockwise){
    if(!Clockwise){
        trybe += 1;
        if(trybe >= 4)
            trybe -= 4;
    }
    else{
        trybe--;
        if(trybe < 0)
            trybe = 3;
    }

    switch (trybe) {
    case 0:
        return {myPos.first - 1, myPos.second};
    case 1:
        return {myPos.first,     myPos.second + 1};
    case 2:
        return {myPos.first + 1, myPos.second};
    case 3:
        return {myPos.first,     myPos.second - 1};
    }
    return{-1,-1};
}

void MainWindow::antMoveForward(){
    int x = lookAt.first - myPos.first;
    int y = lookAt.second- myPos.second;

    if(x == 1){
        myPos.first++;
        lookAt.first++;
    }
    else if(x == -1){
        myPos.first--;
        lookAt.first--;
    }
    else if(y == 1){
        myPos.second++;
        lookAt.second++;
    }
    else if(y == -1){
        myPos.second--;
        lookAt.second--;
    }
}


void MainWindow::antCalculate(){
    enum {LEFT = 0, RIGHT = 1};                   ////    ANT ORIENTED

    while(m_antIsRunning == true){
        qApp->processEvents();          /* Niech GUI przetwarza również zdarzenia! */

        bool isAlive = (m_antCurrentImage.pixelIndex(myPos.first, myPos.second) == ALIVE);
        if(isAlive == true){
            lookAt = antRotateMe(RIGHT);
            m_antCurrentImage.setPixel(myPos.first, myPos.second, DEAD);
        }
        else{
            lookAt = antRotateMe(LEFT);
            m_antCurrentImage.setPixel(myPos.first, myPos.second, ALIVE);
        }
        antMoveForward();
        m_antWidget->setImage(m_antCurrentImage);
    }
}



//// END ANT CODE

void MainWindow::on_TabWidget_tabBarClicked(int index)
{
    switch(index){
    case 0:
        m_lifeWidget->show();
        m_antWidget->hide();
        break;
    case 1:
        m_lifeWidget->hide();
        m_antWidget->show();
        break;
    }
}
