//
// Created by hossein on 12/11/17.
//

#include "dataBase.h"

#include <utility>


dataBase::dataBase(QString inputDb,QString dataBasePass) {
    this->db= new QSqlDatabase (QSqlDatabase::addDatabase("QSQLCIPHER"));
    this->db->setHostName("Hossein");
    this->db->setDatabaseName(inputDb);
    aesData.aes_set_key(aes::default_key, 128);
    if (!db->open()) {
        qDebug() << "Error while opening" << endl;
        exit(1);
    }
    QSqlQuery query;
    if (!query.exec("PRAGMA key='"+dataBasePass+"';")) {
        qDebug() << query.lastError().text() << endl;
        exit(1);
    }
    if (!query.exec(" CREATE TABLE IF NOT EXISTS login(user,pass)")) {
        qDebug() << query.lastError().text() << endl;
        exit(1);
    }
}

bool dataBase::existUser(QString username) {
    QSqlQuery query;
    if (!query.exec("select * from login where user='"+ username+"'" )) {
        qDebug() << query.lastError().text() << endl;
        exit(1);
    }
    return query.next();
}

bool dataBase::existUserAndPass(QString username ,QString pass) {
    QSqlQuery query;
    QString encryptPass=this->cipher(pass, false);
    if (!query.exec("SELECT * FROM login WHERE user='"+ username+"' AND pass='"+encryptPass+"'" )) {
        qDebug() << query.lastError().text() << endl;
        exit(1);
    }
    return query.next();
}

dataBase::~dataBase() {
    db->close();
}

bool dataBase::addUser(QString username,QString pass) {
    QSqlQuery query;
    QString encryptPass=this->cipher(pass, false);
    if(!this->existUser(username)) {
        if (!query.exec("INSERT INTO login (user,pass) VALUES('" + username + "','" + encryptPass + "');")) {
            qDebug() << query.lastError().text() << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

QString dataBase::cipher(QString in, bool mode) {
    unsigned char val[16]={0};
    strcpy((char *)val,in.toStdString().c_str());
    if(!mode){
        aesData.aes_encrypt(val, val);
    }
    else {
        aesData.aes_decrypt(val, val);
    }
    unsigned char tmp[17];
    memcpy(tmp,val,16);
    tmp[16]='\0';
    return QString::fromStdString(string((char*)tmp));
}