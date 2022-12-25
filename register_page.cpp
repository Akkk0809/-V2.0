#include "register_page.h"
#include "ui_register_page.h"
#include "userdate.h"
#include <QLineEdit>
#include <QString>
#include <QDebug>
#include <QMessageBox>

Register_Page::Register_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register_Page)
{
    ui->setupUi(this);
}

Register_Page::~Register_Page()
{
    delete ui;
}

void Register_Page::on_Cancel_released()
{
    close();  //关闭注册界面
}


void Register_Page::on_Ok_released()
{
    regJudgeSlot();
}

void Register_Page::adduserSlot(QString username, QString userpwd, QString phone, QString address,int userAuth)
{
    userdate *newuser = new userdate(username,userpwd,phone,address,0);
    userdate::userlist.push_back(newuser);
}

void Register_Page::regJudgeSlot()
{
    QString username = ui->nameEdit->text();
    QString password = ui->pwdEdit->text();
    QString adr = ui->adrEdit->text();
    QString phone = ui->phoneEdit->text();
    if(username=="") //用户名为空
    {
        QMessageBox::critical(NULL,"错误","用户名为空，请输入用户名");
    }
    else if(password=="")//密码判断
    {
        QMessageBox::critical(NULL,"错误","密码为空，请输入密码");
    }
    else if(password.length()<6)//密码判断
    {
        QMessageBox::critical(NULL,"错误","密码至少为六个字符，请重新输入");
        ui->phoneEdit -> clear();
    }
    else if(adr=="" || phone=="")//电话或住址为空
    {
        QMessageBox::critical(NULL,"错误","联系电话或住址不能为空，请重新输入");
    }
    else
    {
        int i=0;//判断次数
        for(i=0;i<userdate::userlist.size();i++)
        {
            if(username==userdate::userlist.at(i)->getUsername())//名字是否已被注册判断
            {
                QMessageBox::critical(NULL,"错误","此名字已被注册，请重新输入");
                ui->nameEdit->clear();
                ui->pwdEdit->clear();
                ui->phoneEdit->clear();
                ui->adrEdit->clear();
                //光标定位回用户名处
                ui->nameEdit->setFocus();
                break;
            }

        }
        if(i>=userdate::userlist.size())
        {
            adduserSlot(username,password,phone,adr,0);
            QMessageBox::information(NULL,"成功","恭喜您，注册成功！");
            ui->nameEdit->clear();
            ui->pwdEdit->clear();
            ui->phoneEdit->clear();
            ui->adrEdit->clear();
            //光标定位回用户名处
            ui->nameEdit->setFocus();
            close();
        }
    }

}

