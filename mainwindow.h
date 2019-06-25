
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MyScene;  //防止重复包含
#include <QMainWindow>
#include "myscene.h"
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QList>


struct node{
    int x;
    int y;
};

struct way{
    node p[110];  //坐标
    int ncount = 0;   //步数
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public slots:


public:
    QStandardItemModel *ItemModel;
    void initial();
    void dfs(int x, int y, int n, way& tmpway);
    explicit MainWindow(QWidget *parent = nullptr);
    void setSatausBar(QString s);
    void setStartEnable(bool b);
    void setEndEnable(bool b);
    void setBeginEnable(bool b);
    void setObs1Enable(bool b);
    void setObs2Enable(bool b);



    ~MainWindow();

private slots:

    void on_pushButton_setBegin_clicked();

    void on_pushButton_setEnd_clicked();

    void on_pushButton_addObstacle_1_clicked();


    void on_pushButton_start_clicked();

    void on_listView_clicked(const QModelIndex &index);


    void on_action_3_triggered();

    void on_pushButton_addObstacle_2_clicked();

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    MyScene * sc;
    QStringListModel *model;
    QList<way> list;
    QMessageBox msg;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
