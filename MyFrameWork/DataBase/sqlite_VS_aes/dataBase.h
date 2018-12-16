//
// Created by hossein on 12/11/17.
//

#ifndef TESTCLASS_LOGIN_H
#define TESTCLASS_LOGIN_H

#include <QApplication>

#include <QtWidgets>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <array>
#include <iostream>
#include "aes.h"

using namespace std;

class dataBase {
private:
    QString  cipher(QString in,bool mode);//0 for encrypt and 1 for decrypt
    QSqlDatabase *db;
    aes aesData;
public:
    dataBase(QString inputDb,QString dataBasePass);
    ~dataBase();
    bool existUser(QString username);
    bool existUserAndPass(QString username ,QString pass);
    bool addUser(QString username ,QString pass);

};


#endif //TESTCLASS_LOGIN_H
