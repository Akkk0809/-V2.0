#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "register_page.h"
#include "ui_register_page.h"
#include "userdate.h"
#include "QTableView"
#include "QTableWidget"
#include <QScrollBar>
#include <QLineEdit>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setTableWidget(0,8);
    //显示当前日期时间
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(time_update()));
    timer->start(1000); //1s执行一次,定时器
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::time_update() //显示系统实时时间
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->label->setText(str);
}

void MainWindow::setTableWidget(int, int)  //QTableWidget的初始化
{
        ui->tableWidget->resizeRowsToContents();//调整行内容大小
        ui->tableWidget->setColumnCount(8);//设置列数
        //ui->tableWidget->setRowCount(100);//设置行数
        //设置标题头的文字
        QStringList header;
        header<< tr("物品名称") <<tr("物品类型")<< tr("物品属性") << tr("位置") << tr("电话号码")<< tr("电子邮件")<< tr("添加日期")<<tr("备注信息");
        ui->tableWidget->setHorizontalHeaderLabels(header);
        //设置标题头的字体样式
        QFont font = ui->tableWidget->horizontalHeader()->font();
        font.setBold(true);
        ui->tableWidget->horizontalHeader()->setFont(font);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应宽度
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents); //根据内容使用宽度列表
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
        ui->tableWidget->verticalHeader()->setDefaultSectionSize(10); //设置行距
        ui->tableWidget->setShowGrid(true); //设置显示格子线
        ui->tableWidget->verticalHeader()->setVisible(true); //设置行号列,false为不显示
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
        ui->tableWidget->horizontalHeader()->resizeSection(0,100);//设置表头第一列的宽度为100
        ui->tableWidget->horizontalHeader()->setFixedHeight(30); //设置表头的高度
        ui->tableWidget->setStyleSheet("selection-background-color:rgb(65, 195, 195);"); //设置选中背景色
        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(214, 214, 214);}"); //设置表头背景色

        //设置水平、垂直滚动条样式,添加头文件 #include <QScrollBar>
        ui->tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
                                                              "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                                                              "QScrollBar::handle:hover{background:gray;}"
                                                              "QScrollBar::sub-line{background:transparent;}"
                                                              "QScrollBar::add-line{background:transparent;}");
        ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
                                                            "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                                                            "QScrollBar::handle:hover{background:gray;}"
                                                            "QScrollBar::sub-line{background:transparent;}"
                                                            "QScrollBar::add-line{background:transparent;}");

        ui->tableWidget->clearContents();//清除表格数据区的所有内容，但是不清除表头
}

void MainWindow::tablecurrentitemToline()
{
    int row;
    row = ui->tableWidget->currentRow();
    ui->NameLin->setText(ui->tableWidget->item(row,0)->text());
    ui->TypeBox_2->setCurrentText(ui->tableWidget->item(row,1)->text());
    ui->NumLin->setText(ui->tableWidget->item(row,2)->text());
    ui->AddressLin->setText(ui->tableWidget->item(row,3)->text());
    ui->PhonenumLin->setText(ui->tableWidget->item(row,4)->text());
    ui->EmailLin->setText(ui->tableWidget->item(row,5)->text());
    ui->DayEdit->setDate(QDate::currentDate());
    ui->ExtraLin->setText(ui->tableWidget->item(row,7)->text());
}

void MainWindow::newuserTable()
{
    setTableWidget(0,4);
    QString userName,userPhone,userAdr;
    int userAuth;
    for(int i=0;i<userdate::userlist.size();i++)
    {
        userName = userdate::userlist.at(i)->getUsername();
        userPhone = userdate::userlist.at(i)->getUserphone();
        userAdr = userdate::userlist.at(i)->getUseradr();
        userAuth = userdate::userlist.at(i)->getuserAuth();
        int RowCont;
        RowCont = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(RowCont);//增加一行
        //插入元素
        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(userName));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(userPhone));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(userAdr));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(userAuth));
    }

}

void MainWindow::on_adminSigninBtn_clicked()
{
    QString username = ui->userNameIn->text();
    QString userpwd = ui->passwordIn->text();
    int adminAuth = 0;//管理员权限(管理员权限应该是1，但管理员管理部分没有完成)
    if(username=="") //用户名是否为空
    {
        //弹窗
        QMessageBox::critical(NULL,"错误","用户名为空，请输入用户名");
        ui->userNameIn->clear();
        ui->passwordIn->clear();
        //光标定位回用户名处
        ui->userNameIn->setFocus();
    }
    else if(userpwd=="") //密码是否为空
    {
        QMessageBox::critical(NULL,"错误","密码为空，请输入密码");
        ui->userNameIn->clear();
        ui->passwordIn->clear();
        //光标定位回用户名处
        ui->userNameIn->setFocus();
    }
    else
    {
        int i=0;//判断次数
        for(i=0;i<userdate::userlist.size();i++)
        {
            if(username==userdate::userlist.at(i)->getUsername()&&userpwd==userdate::userlist.at(i)->getUserpwd())//用户密码是否存在相等
            {
                QMessageBox::information(NULL,"成功","登录成功");
                ui->stackedWidget->setCurrentWidget(ui->AdminPage);    //切换到管理员界面
                break;
                /*if(adminAuth==userdate::userlist.at(i)->getuserAuth()) //判断是否有管理员权限
                {
                    QMessageBox::information(NULL,"成功","登录成功");
                    ui->stackedWidget->setCurrentWidget(ui->AdminPage);    //切换到管理员界面
                    break;
                }
                else
                {
                    QMessageBox::information(NULL,"失败","对不起，您没有管理员权限");
                    ui->userNameIn->clear();
                    ui->passwordIn->clear();
                    //光标定位回用户名处
                    ui->userNameIn->setFocus();
                    break;
                }*/
            }
        }
        if(i>=userdate::userlist.size())//没有找到匹配用户密码存在
        {
            QMessageBox::critical(NULL,"错误","用户或密码错误请重新输入");
            ui->userNameIn->clear();
            ui->passwordIn->clear();
            //光标定位回用户名处
            ui->userNameIn->setFocus();
        }
    }
}

void MainWindow::on_userSigninBtn_clicked()
{
    QString username = ui->userNameIn->text();
    QString userpwd = ui->passwordIn->text();
    //int userAuth = 0; //用户员权限
    //int adminAuth = 1;//管理员权限
    if(username=="") //用户名是否为空
    {
        //弹窗
        QMessageBox::critical(NULL,"错误","用户名为空，请输入用户名");
        ui->userNameIn->clear();
        ui->passwordIn->clear();
        //光标定位回用户名处
        ui->userNameIn->setFocus();
    }
    else if(userpwd=="") //密码是否为空
    {
        QMessageBox::critical(NULL,"错误","密码为空，请输入密码");
        ui->userNameIn->clear();
        ui->passwordIn->clear();
        //光标定位回用户名处
        ui->userNameIn->setFocus();
    }
    else
    {
        int i=0;//判断次数
        for(i=0;i<userdate::userlist.size();i++)
        {
            if(username==userdate::userlist.at(i)->getUsername()&&userpwd==userdate::userlist.at(i)->getUserpwd())//用户密码是否存在相等
            {
                QMessageBox::information(NULL,"成功","登录成功");
                ui->stackedWidget->setCurrentWidget(ui->UserPage);    //切换到用户界面
                break;
                /*if(userAuth==userdate::userlist.at(i)->getuserAuth() ||adminAuth==userdate::userlist.at(i)->getuserAuth() ) //判断是否有管理员或用户权限
                {
                    QMessageBox::information(NULL,"成功","登录成功");
                    ui->stackedWidget->setCurrentWidget(ui->UserPage);    //切换到用户界面
                    break;
                }
                else
                {
                    QMessageBox::information(NULL,"失败","对不起，您用户注册申请还没通过，请耐心等待");
                    ui->userNameIn->clear();
                    ui->passwordIn->clear();
                    //光标定位回用户名处
                    ui->userNameIn->setFocus();
                    break;
                }*/
            }
        }
        if(i>=userdate::userlist.size())//没有找到匹配用户密码存在
        {
            QMessageBox::critical(NULL,"错误","用户或密码错误请重新输入");
            ui->userNameIn->clear();
            ui->passwordIn->clear();
            //光标定位回用户名处
            ui->userNameIn->setFocus();
        }
    }
}

void MainWindow::on_ExitBtn_released()
{
    close();                              //退出系统
}


void MainWindow::on_backBtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);    //切换到主页面
}

void MainWindow::on_ExitBtn_2_released()
{
    close();                              //退出系统
}

void MainWindow::on_ExitBtn_3_clicked()
{
    close();                              //退出系统
}

void MainWindow::on_PreviewBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->UserPage);    //切换到用户界面
}

void MainWindow::on_RegisterBtn_clicked()
{
    //打开注册窗口
    Register_Page *regist = new Register_Page;
    regist->show();
}
void MainWindow::on_SearchBtn_released()
{
    //搜索物品信息
    QString itemtype = ui->TypeBox->currentText();//要搜索的物品类型
    QString item1 = ui->lineEdit->text(); //要搜索的物品关键信息
    //if(itemtype == "全部") //物品类型为“全部”
    //{
        if(item1 == "")
        {
            QMessageBox::information(NULL,"提示","请输入要搜索的物品关键信息");
            return;
        }
        QList<QTableWidgetItem *>   items;
        QTableWidgetItem            *item;

        items  = ui->tableWidget->findItems(item1, Qt::MatchExactly);//在表格中查找数据项

        //找到了这个数据项
        if(!items.isEmpty())
        {
            item = items[0];//获取到数据项
            int r = item->row();//获取所在行
            ui->tableWidget->verticalScrollBar()->setSliderPosition(r);//滚动条定位到数据所在位置
            ui->tableWidget->setCurrentItem(item);//将这个数据所在行设置为表格的当前行
        }
    //}
    /*else
    {
        if(item1 == "")
        {
            QMessageBox::information(NULL,"提示","请输入要搜索的物品关键信息");
            return;
        }
        else
        {
            QList<QTableWidgetItem *>   items;
            QList<QTableWidgetItem *>   items1;
            QTableWidgetItem            *item;
            items1  = ui->tableWidget->findItems(itemtype, Qt::MatchContains);
            items  = ui->tableWidget->findItems(item1, Qt::MatchContains);//在表格中查找数据项
            //找到了这个数据项
            if(!items.isEmpty() && items==items1)
            {
                item = items[0];//获取到数据项
                int r = item->row();//获取所在行
                ui->tableWidget->verticalScrollBar()->setSliderPosition(r);//滚动条定位到数据所在位置
                ui->tableWidget->setCurrentItem(item);//将这个数据所在行设置为表格的当前行
            }
            else
            {
                QMessageBox::information(NULL,"提示","你要搜索的物品不存在！");
            }
        }
    }*/
}

void MainWindow::on_delBtn_released()
{
    int row;
    row = ui->tableWidget->currentRow();
    if(row < 0)
    {
        QMessageBox::information(NULL,"提示","请先选中要删除的项！");
        return ;
    }
    else
    {
        ui->tableWidget->removeRow(row);
        QMessageBox::information(NULL,"成功","物品信息删除成功！");
    }
}

void MainWindow::on_addBtn_clicked()
{
    QString Name,Type,Num,Address,Day,Email,Phonenum,Extra;
    //读取lineedit的内容
    Name=ui->NameLin->text();
    Type=ui->TypeBox_2->currentText();
    Email=ui->EmailLin->text();
    Phonenum=ui->PhonenumLin->text();
    Extra=ui->ExtraLin->text();
    Num=ui->NumLin->text();
    Address=ui->AddressLin->text();
    Day=ui->DayEdit->date().toString();
    if(Name.length()==0 || Type.length()==0 || Email.length()==0 || Phonenum.length()==0 || Num.length()==0 || Address.length()==0 || Day.length()==0)
    {
        //备注信息之外其他任意信息为空时，提示补充
        QMessageBox::warning(NULL,"警告","物品信息不能为空，请补充！");
    }
    else
    {
        int RowCont;
        RowCont = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(RowCont);//增加一行
        //插入元素
        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(Name));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(Type));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(Num));
        ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem(Address));
        ui->tableWidget->setItem(RowCont,4,new QTableWidgetItem(Phonenum));
        ui->tableWidget->setItem(RowCont,5,new QTableWidgetItem(Email));
        ui->tableWidget->setItem(RowCont,6,new QTableWidgetItem(Day));
        ui->tableWidget->setItem(RowCont,7,new QTableWidgetItem(Extra));
        QMessageBox::information(NULL,"成功","恭喜您，添加物品信息成功！");
    }
}

void MainWindow::on_changeBtn_pressed()
{
    int row;
    row = ui->tableWidget->currentRow();
    if(row < 0)
    {
        QMessageBox::warning(NULL,"警告","请先选中要修改的项！");
        return ;
    }
    else
    {
        QString Name,Type,Num,Address,Day,Email,Phonenum,Extra;
        //读取lineedit的内容
        Name=ui->NameLin->text();
        Type=ui->TypeBox_2->currentText();
        Email=ui->EmailLin->text();
        Phonenum=ui->PhonenumLin->text();
        Extra=ui->ExtraLin->text();
        Num=ui->NumLin->text();
        Address=ui->AddressLin->text();
        Day=ui->DayEdit->date().toString();
        if(Name.length()==0 || Type.length()==0 || Email.length()==0 || Phonenum.length()==0 || Num.length()==0 || Address.length()==0 || Day.length()==0)
        {
            //备注信息之外其他任意信息为空时，提示补充
            QMessageBox::warning(NULL,"警告","物品信息不能为空，请补充！");
        }
        else
        {
            //把修改的内容写进去
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(Name));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(Type));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(Num));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(Address));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(Phonenum));
            ui->tableWidget->setItem(row,5,new QTableWidgetItem(Email));
            ui->tableWidget->setItem(row,6,new QTableWidgetItem(Day));
            ui->tableWidget->setItem(row,7,new QTableWidgetItem(Extra));
            //清空输入框

            QMessageBox::information(NULL,"成功","恭喜您，物品信息修改成功！");
        }
    }
}


void MainWindow::on_refresh_released()
{
    newuserTable();
}


/*void MainWindow::on_changeauth_released()
{
    QString username;
    int auth;
    auth = ui->authEdit->text.toInt();
    int row;
    row = ui->userTable->currentRow();
    if(row < 0)
    {
        QMessageBox::information(NULL,"提示","请先选中用户！");
        return ;
    }
    else
    {
        username =ui->userTable->item(row,0)->text().toStdString();
        if(auth!=0 || auth!=1 ||auth!=-1)
        {
            QMessageBox::information(NULL,"提示","用户权限不能为空！");
        }
        else
        {
            for(int i=0;i<userdate::userlist.size();i++)
            {
                if(username == userdate::userlist.at(i)->getUsername)//用户是存在相等
                {
                    userdate::userlist.at(i)->setuserAuth(auth);
                    QMessageBox::information(NULL,"成功","用户权限修改成功");
                    break;
                }
            }
        }
    }

}*/

