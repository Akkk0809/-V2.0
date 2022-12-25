#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "register_page.h"
#include "userdate.h"
#include <QTimer>
#include <QFile>
#include <QList>
#include <QString>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QDateEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ExitBtn_released();
    void on_backBtn_released();
    void on_ExitBtn_2_released();
    void on_SearchBtn_released();
    void on_delBtn_released();
    void on_addBtn_clicked();
    void on_adminSigninBtn_clicked();
    void on_userSigninBtn_clicked();
    void on_ExitBtn_3_clicked();
    void on_PreviewBtn_clicked();
    void on_RegisterBtn_clicked();
    void on_changeBtn_pressed();
    void time_update(void);
    void on_refresh_released();
private:
    Ui::MainWindow *ui;

private:
    void setTableWidget(int ,int);
    void tablecurrentitemToline(); //表格中选中的行的内容读取到信息框中
    void newuserTable();//新用户注册信息表
};

#endif // MAINWINDOW_H
