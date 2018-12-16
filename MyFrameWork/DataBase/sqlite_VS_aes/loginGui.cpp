//
// Created by hossein on 12/13/17.
//

#include "loginGui.h"

loginGui::loginGui(guiWindow *previousMenu):guiWindow(previousMenu) {
    base =new dataBase("login.sqlite", "password");
    createWidgets();
    addToScene();
    setGeometries();
    connector();
}

loginGui::~loginGui() {
    free(base);
    base= nullptr;

}

void loginGui::createWidgets() {
    usernameLabel.setText("Username:");
    passwordLabel.setText("Password:");
    passwordLine.setEchoMode(QLineEdit::Password);
    loginButton.setText("Login");
    exitButton.setText("Exit");
    checkLabel.setText("");
}

void loginGui::addToScene() {
    userPassLayout.addWidget(&usernameLabel,0,0);
    userPassLayout.addWidget(&usernameLine,0,1);
    userPassLayout.addWidget(&passwordLabel,1,0);
    userPassLayout.addWidget(&passwordLine,1,1);
    scene->addLayout(&userPassLayout);
    checkLayout.addWidget(&checkLabel);
    scene->addLayout(&checkLayout);
    buttonsLayout.addWidget(&loginButton);
    buttonsLayout.addWidget(&exitButton);
    scene->addLayout(&buttonsLayout);

}

void loginGui::setGeometries() {
    int WinWidth = 250;
    int WinHeight = 100;
    QRect rec=QApplication::desktop()->screenGeometry();
    this->setGeometry((rec.width()-WinWidth)/2,(rec.height()-WinHeight)/2,WinWidth,WinHeight);
}

void loginGui::connector() {
    connect(&loginButton,SIGNAL(clicked()),this,SLOT(on_loginButton_clicked()));
    connect(&exitButton,SIGNAL(clicked()),this,SLOT(on_exitButton_clicked()));
}

void loginGui::on_exitButton_clicked() {
    //exit(0);
    checkLabel.setText("correct");
    if(child== nullptr) {
        child = new guiWindow*[1];
        child[0] = new welcome(this);
    }
    this->stopView();
    child[0]->runView();
}

void loginGui::on_loginButton_clicked() {
    if(base->existUserAndPass(usernameLine.text(),passwordLine.text())) {
        checkLabel.setText("correct");
        if(child== nullptr) {
            child = new guiWindow*[1];
            child[0] = new welcome(this);
        }
        this->stopView();
        child[0]->runView();
    }
    else
        checkLabel.setText("username or password is incorrect");
}
