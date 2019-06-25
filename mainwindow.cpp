#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <cstring>
#include <QMessageBox>
#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("迷宫寻路 _最终版");

    this->ui->pushButton_start->setEnabled(false);
    this->ui->pushButton_setBegin->setEnabled(true);
    this->ui->pushButton_setEnd->setEnabled(false);
    this->ui->pushButton_addObstacle_1->setEnabled(false);
    this->ui->pushButton_addObstacle_2->setEnabled(false);

    this->sc = new MyScene(this);
    this->ui->graphicsView->setScene(sc);

    connect(this->ui->pushButton_setBegin, &QPushButton::clicked, this->sc, &MyScene::setBegin);
    connect(this->ui->pushButton_setEnd, &QPushButton::clicked, this->sc, &MyScene::setEnd);
    connect(this->ui->pushButton_addObstacle_1, &QPushButton::clicked, this->sc, &MyScene::addObstacle1);
    connect(this->ui->pushButton_addObstacle_2, &QPushButton::clicked, this->sc, &MyScene::addObstacle2);

    this->ui->instructions->adjustSize();

    this->ui->graphicsView->setCursor(Qt::CrossCursor);
}

void MainWindow::setSatausBar(QString s)
{
    this->statusBar()->showMessage(s);
}

void MainWindow::setStartEnable(bool b)
{
    this->ui->pushButton_start->setEnabled(b);
}

void MainWindow::setEndEnable(bool b)
{
this->ui->pushButton_setEnd->setEnabled(b);
}

void MainWindow::setBeginEnable(bool b)
{
this->ui->pushButton_setBegin->setEnabled(b);
}

void MainWindow::setObs1Enable(bool b)
{
this->ui->pushButton_addObstacle_1->setEnabled(b);
}

void MainWindow::setObs2Enable(bool b)
{
this->ui->pushButton_addObstacle_2->setEnabled(b);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_setBegin_clicked()
{
        this->ui->statusBar->showMessage("设置起点");
}

void MainWindow::on_pushButton_setEnd_clicked()
{
    this->ui->statusBar->showMessage("设置终点");
}

void MainWindow::on_pushButton_addObstacle_1_clicked()
{
    this->ui->statusBar->showMessage("手动设置障碍");
}

int dest[4][2] = {  //用于dfs的四个方向
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

void MainWindow::initial()  //初始化
{
     MyScene::beginx = -1;
     MyScene::beginy = -1;
     MyScene::endx = -1;
     MyScene::endy = -1;
     MyScene::isBegin = false;
     MyScene::isEnd = false;
     MyScene::isObstacle = false;
     memset(MyScene::book, 0, sizeof(MyScene::book));
     MyScene::ObstacleCount = 0;
     this->list.clear();

     this->ui->pushButton_start->setEnabled(false);
     this->ui->pushButton_setBegin->setEnabled(true);
     this->ui->pushButton_setEnd->setEnabled(false);
     this->ui->pushButton_addObstacle_1->setEnabled(false);
     this->ui->pushButton_addObstacle_2->setEnabled(false);

     sc->clear();  //清除左边迷宫
     for(int i=0;i<SettingDialog::height;i++) //重新生成迷宫
     {
         for(int j=0;j<SettingDialog::width;j++)
         {
             sc->item[i][j] = new MyItem;
             sc->item[i][j]->setPos(j*SettingDialog::block, i*SettingDialog::block);
             sc->addItem(sc->item[i][j]);
         }
     }
    if(MyScene::alln != 0)
    {
         ItemModel->clear(); //清除右边listview的item
         MyScene::alln = 0;
    }

}
////////////////////////////////////
void MainWindow::dfs(int x, int y, int n, way &tmpway)
{
    if(x < 0 || x >=SettingDialog::height || y < 0 || y >= SettingDialog::width)
    {
        return;  //终止
    }
    if(x == MyScene::endx && y  == MyScene::endy)
    {
                //找到终点的处理办法
        MyScene::alln++;
        tmpway.ncount = n-1;
        MainWindow::list.append(tmpway);
        return;
    }
    tmpway.p[n].y = x;
    tmpway.p[n].x = y;
    for(int i=0;i<4;i++)
    {
        int tx = x + dest[i][0];
        int ty = y + dest[i][1];
        if(MyScene::book[tx][ty] == 0)
        {
            MyScene::book[tx][ty] = 1;
            dfs(tx, ty, n+1, tmpway);
            MyScene::book[tx][ty] = 0;
        }
    }
}

///////////////////////////////

void MainWindow::on_pushButton_start_clicked()
{
        MyScene::isObstacle = false;
        MyScene::add(MyScene::beginx, MyScene::beginy);  //将起点添加为不可走点
        if(MyScene::beginx == -1 || MyScene::endx == -1)    //起点或终点未被初始化
        {
            this->ui->statusBar->showMessage("终点或起点未确定");
            return;
        }

        this->ui->pushButton_addObstacle_1->setEnabled(false);
        this->ui->pushButton_addObstacle_2->setEnabled(false);
        this->ui->pushButton_start->setEnabled(false);

        way tmpway;

                //开始dfs
        dfs(MyScene::beginx, MyScene::beginy, 0, tmpway);

        //从小到大排序
        qSort(list.begin(), list.end(),
             [](const way t1, const way t2)
              {
                return t1.ncount < t2.ncount;
              }
             );

        if(MyScene::alln == 0)   //可行路径为0
        {
            statusBar()->showMessage("此迷宫无解！！！");
            QString s = "此迷宫无解!";
            msg.setText(s);
            msg.setStandardButtons(QMessageBox::Ok);
            msg.exec();
            return;
        }
        statusBar()->showMessage("选择右边列表即可显示路径");


        //将路径的步数保存到listview
        ItemModel = new QStandardItemModel(this);
        QStringList strList;

        for(int i=0;i<MyScene::alln;i++)
        {
            strList.append("步数:" + QString::number(list.at(i).ncount+1));
        }

        for(int i=0;i<MyScene::alln;i++)
        {
            QString string = static_cast<QString>(strList.at(i));
            QStandardItem *item = new QStandardItem(string);
            ItemModel->appendRow(item);
        }
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers); //让右边的listview不能被编辑
        ui->listView->setModel(ItemModel);
        if(MyScene::alln != 0)
        {
            QString s = "搜索完成，共有" + QString::number(MyScene::alln) + "组解";
            msg.setText(s);
            msg.setStandardButtons(QMessageBox::Ok);
            msg.exec();
        }
}


void MainWindow::on_listView_clicked(const QModelIndex &index)   //右边的listview被单击选中了
{
    sc->clear();   //先把左边清空了  重新画
    for(int i=0;i<SettingDialog::height;i++)
    {
        for(int j=0;j<SettingDialog::width;j++)
        {
            sc->item[i][j] = new MyItem;
            sc->item[i][j]->setPos(j*SettingDialog::block, i*SettingDialog::block);
            sc->addItem(sc->item[i][j]);
        }
    }
    int k = index.row();
    for(int i=0;i<SettingDialog::height;i++)
    {
        for(int j=0;j<SettingDialog::width;j++)
        {
            if(MyScene::book[i][j] == 1)
            {
                sc->item[i][j]->setBlockType(MyItem::BOBSTACLE);
            }
        }
    }
    sc->item[MyScene::beginx][MyScene::beginy]->setBlockType(MyItem::BSTART);   //起点和终点
    sc->item[MyScene::endx][MyScene::endy]->setBlockType(MyItem::BEND);
    sc->item[MyScene::endx][MyScene::endy]->setNum(list.at(k).ncount+1);
    for(int i=1;i<=list.at(k).ncount;i++)
    {
       sc->item[list.at(k).p[i].y][list.at(k).p[i].x]->setBlockType(MyItem::BPATH);

       sc->item[list.at(k).p[i].y][list.at(k).p[i].x]->setNum(i);

    }
}


void MainWindow::on_action_3_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    bool exit = QMessageBox::question(this,
                                          "Quit",
                                          "你确定要退出吗？",
                                          QMessageBox::Yes | QMessageBox::No,
                                          QMessageBox::No) == QMessageBox::Yes;
            if (exit) {
                event->accept();
            } else {
                event->ignore();
}
}

void MainWindow::on_pushButton_addObstacle_2_clicked()
{
            this->ui->statusBar->showMessage("随机设置障碍");
}

void MainWindow::on_action_6_triggered()
{
    MainWindow::initial();
}

void MainWindow::on_action_7_triggered()
{
    QMessageBox::about(this, "关于本程序",
                       "本程序历时两天，主要用于C++和数据结构的大作业。经过了各种bug修复(虽然现在还有),三次大改,但总算成型了。"
                       "第一次加上了数字，第二次加上了可改变迷宫尺寸,第三次修改了按钮的逻辑。"
                        "在学长的指导下完成了数字的添加，"
                       "虽然看上去还是很low。"
                       "今天母亲节，祝妈妈母亲节快乐！-20190512\n"
                       "博客：www.oylong.com\n"
                       "QQ1048998272"
                       );
}

void MainWindow::on_action_triggered()
{
    SettingDialog *set = new SettingDialog(this);
    set->exec();
}
