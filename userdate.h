#ifndef USERDATE_H
#define USERDATE_H
#include<QString>//字符串
#include<QList>  //用户链表

class userdate
{
public:
    userdate();
    userdate(QString username, QString userpwd, QString phone, QString address,int userAuth);//带参构造 - 直接初始化用户信息
    void setUsername(QString username);
    QString getUsername();
    void setUserpwd(QString userpwd);
    QString getUserpwd();
    void setUserphone(QString phone);
    QString getUserphone();
    void setUseradr(QString address);
    QString getUseradr();
    //获取用户状态
    int getuserAuth();
    void setuserAuth(int userAuth);
    //定义用户链表
    static QList<userdate *> userlist;
    static void addUser();//初始化链表
    QString username;  //用户名
    QString userpwd;   //密码
    QString phone;     //电话
    QString address;   //住址
    int userAuth;     //用户权限 -1新用户 0普通用户 1管理员
};

#endif // USERDATE_H
