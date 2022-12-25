#ifndef REGISTER_PAGE_H
#define REGISTER_PAGE_H

#include <QWidget>
#include <userdate.h>
#include <QMessageBox>

namespace Ui {
class Register_Page;
}

class Register_Page : public QWidget
{
    Q_OBJECT

public:
    explicit Register_Page(QWidget *parent = nullptr);
    ~Register_Page();

private slots:
    void on_Cancel_released();
    void on_Ok_released();
    void adduserSlot(QString username,QString userpwd, QString phone, QString address,int userAuth);        //注册成功添加用户
    void regJudgeSlot();       //注册是否成功

private:
    Ui::Register_Page *ui;

};

#endif // REGISTER_PAGE_H
