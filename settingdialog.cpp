#include "ui_settingdialog.h"
#include "settingdialog.h"
#include "mainwindow.h"

int SettingDialog::block = 45;
int SettingDialog::height = 8;
int SettingDialog::width = 8;

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("设置");
    this->ui->spinBox_height->setValue(SettingDialog::height);
    this->ui->spinBox_block->setValue(SettingDialog::block);
    this->ui->spinBox_width->setValue(SettingDialog::width);
    this->ui->spinBox_block->setRange(10, 80);
    this->ui->spinBox_width->setRange(2, 10);
    this->ui->spinBox_height->setRange(2, 10);
}


SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButton_clicked()
{
    MainWindow *ptr = static_cast<MainWindow*>(parentWidget());
    SettingDialog::block = this->ui->spinBox_block->value();
    SettingDialog::height = this->ui->spinBox_height->value();
    SettingDialog::width = this->ui->spinBox_width->value();
    msg.setText("修改成功!");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.exec();


    ptr->initial();
    this->close();
}

void SettingDialog::on_pushButton_2_clicked()
{
    this->close();
}
