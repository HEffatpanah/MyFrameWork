//
// Created by hossein on 12/13/17.
//

#ifndef RADAR_LOGINGUI_H
#define RADAR_LOGINGUI_H

#include <QtWidgets>
#include "guiWindow.h"
#include "dataBase.h"
#include "welcome.h"

class loginGui:public guiWindow{
Q_OBJECT
private:
    QPushButton loginButton;
    QPushButton exitButton;
    QLabel usernameLabel;
    QLabel passwordLabel;
    QLabel checkLabel;
    QLineEdit usernameLine;
    QLineEdit passwordLine;
    QGridLayout userPassLayout;
    QHBoxLayout checkLayout;
    QHBoxLayout buttonsLayout;
    void createWidgets() override;
    void addToScene() override;
    void setGeometries() override;
    void connector() override;
    dataBase *base;
public slots:
    void on_loginButton_clicked();
    void on_exitButton_clicked();
public:
    loginGui(guiWindow *previousMenu);
    ~loginGui();
};


#endif //RADAR_LOGINGUI_H
