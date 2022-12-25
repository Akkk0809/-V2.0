#include "userdate.h"

QList<userdate *> userdate::userlist;

userdate::userdate()
{

}

userdate::userdate(QString username, QString userpwd, QString phone, QString address,int userAuth)
{
    this->username = username;
    this->userpwd = userpwd;
    this->phone = phone;
    this->address = address;
    this->userAuth = -1;//新用户
}

void userdate::setUsername(QString username)
{
    this->username = username;
}

QString userdate::getUsername()
{
    return username;
}

void userdate::setUserpwd(QString userpwd)
{
    this->userpwd = userpwd;
}

QString userdate::getUserpwd()
{
    return userpwd;
}

void userdate::setUserphone(QString phone)
{
    this->phone = phone;
}

QString userdate::getUserphone()
{
    return phone;
}

void userdate::setUseradr(QString address)
{
    this->address = address;
}

QString userdate::getUseradr()
{
    return address;
}

int userdate::getuserAuth()
{
    return userAuth;

}

void userdate::setuserAuth(int userAuth)
{
    this->userAuth = userAuth;
}

void userdate::addUser()
{
    userdate *newuser1 = new userdate("admin","123456","110","SJTU1",1);
    userdate *newuser2 = new userdate("user","123456","120","SJTU2",0);
    userdate::userlist.push_back(newuser1);
    userdate::userlist.push_back(newuser2);
}


