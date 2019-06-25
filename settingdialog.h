#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
    static int width;
    static int height;
    static int block;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SettingDialog *ui;
    QMessageBox msg;
};

#endif // SETTINGDIALOG_H
