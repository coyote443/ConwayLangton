#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

namespace Ui {
class MainWindow;
}

class LifeWidget;
class AntWidget;
typedef std::pair<int,int> Pos;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    enum {DEAD = 0, ALIVE = 1};
    ~MainWindow();

    static int lifeNeighborCount(const QImage& img, int x, int y);
    void antMoveForward();
    Pos antRotateMe(bool Clockwise);

private slots:
    void on_antStartStopButton_clicked(bool checked);
    void on_antClearButton_clicked();
    void on_addNewAntButton_clicked();
    void antCalculate();

    void on_lifeStartStopButton_clicked(bool checked);
    void on_lifeClearButton_clicked();
    void on_lifeRandomPopButton_clicked();
    void lifeCalculate();

    void on_TabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;

    QSize       m_antBoardSize;
    AntWidget*  m_antWidget;
    QImage      m_antCurrentImage;
    QTime       m_antTimer;
    int         m_antNumGeneration  = 0;
    bool        m_antIsRunning      = false;
    int         trybe          = 0;
    Pos myPos  = Pos(120,120),
        lookAt = Pos(120,120);


    QSize       m_lifeBoardSize;
    AntWidget*  m_lifeWidget;
    QImage      m_lifeCurrentImage;
    QTime       m_lifeTimer;
    int         m_lifeNumGeneration = 0;
    bool        m_lifeIsRunning     = false;
};

#endif // MAINWINDOW_H
