#include "logindialog.h"
#include "registerdialog.h"
#include "dmsqlmanager.h"
#include <QMessageBox>

extern DMSqlManager *dmsqlmanager;
extern int user_type_login;
extern QString phonenumber;

LoginDialog::LoginDialog() {
    phonenumber_l = new QLabel(this);
    phonenumber_l->move(70,80);
    phonenumber_l->setText(tr("手机号："));
    phonenumber_e = new QLineEdit(this);
    phonenumber_e->move(140,80);
    phonenumber_e->setPlaceholderText(tr("请输入手机号"));

    password_l = new QLabel(this);
    password_l->move(70,130);
    password_l->setText(tr("密码："));
    password_e = new QLineEdit(this);
    password_e->move(140,130);
    password_e->setPlaceholderText(tr("请输入密码"));
    password_e->setEchoMode(QLineEdit::Password);

    user_type = new QButtonGroup(this);
    user_type0 = new QRadioButton("管理员",this);
    user_type0->move(50,170);
    user_type1 = new QRadioButton("审核员",this);
    user_type1->move(110,170);
    user_type2 = new QRadioButton("采购员",this);
    user_type2->move(170,170);
    user_type3 = new QRadioButton("销售员",this);
    user_type3->move(230,170);
    user_type->addButton(user_type0,0);
    user_type->addButton(user_type1,1);
    user_type->addButton(user_type2,2);
    user_type->addButton(user_type3,3);

    login_btn = new QPushButton(this);
    login_btn->move(50,200);
    login_btn->setText(tr("登录"));
    reg_btn = new QPushButton(this);
    reg_btn->move(210,200);
    reg_btn->setText(tr("注册"));

    connect(login_btn,&QPushButton::clicked,this,&LoginDialog::login_onclick);
    connect(reg_btn,&QPushButton::clicked,this,&LoginDialog::reg_onclick);
}


LoginDialog::~LoginDialog() {
    phonenumber_l->~QLabel();
    phonenumber_e->~QLineEdit();
    password_l->~QLabel();
    password_e->~QLineEdit();
    user_type->removeButton(user_type0);
    user_type->removeButton(user_type1);
    user_type->removeButton(user_type2);
    user_type->removeButton(user_type3);
    user_type->~QButtonGroup();
    user_type0->~QRadioButton();
    user_type1->~QRadioButton();
    user_type2->~QRadioButton();
    user_type3->~QRadioButton();
    login_btn->~QPushButton();
    reg_btn->~QPushButton();
}

void LoginDialog::login_onclick() {
    if(phonenumber_e->text().isEmpty() || password_e->text().isEmpty() || user_type->checkedId() == -1) {
        QMessageBox::warning(this,tr("提示"),tr("请输入完整信息！"),QMessageBox::Yes);
        return;
    }
    if(dmsqlmanager->login(phonenumber_e->text(),password_e->text(),user_type->checkedId())) {
        phonenumber = phonenumber_e->text();
        user_type_login = user_type->checkedId();
        accept();
    }
    else QMessageBox::warning(this,tr("提示"),tr("登录失败"),QMessageBox::Yes);
}

void LoginDialog::reg_onclick() {
    RegisterDialog rdlg;
    rdlg.exec();
}
