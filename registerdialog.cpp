#include "registerdialog.h"
#include "dmsqlmanager.h"
#include <QMessageBox>

extern DMSqlManager *dmsqlmanager;

RegisterDialog::RegisterDialog() {
    phonenumber_l = new QLabel(tr("手机号"),this);
    phonenumber_l->move(70,70);
    phonenumber_e = new QLineEdit(this);
    phonenumber_e->move(160,70);
    phonenumber_e->setPlaceholderText(tr("请输入手机号"));
    name_l = new QLabel(tr("姓名"),this);
    name_l->move(70,100);
    name_e = new QLineEdit(this);
    name_e->move(160,100);
    name_e->setPlaceholderText("请输入姓名");
    password_l = new QLabel(tr("密码"),this);
    password_l->move(70,130);
    password_e = new QLineEdit(this);
    password_e->move(160,130);
    password_e->setPlaceholderText("请输入密码");
    password_e->setEchoMode(QLineEdit::Password);
    repassword_l = new QLabel(tr("确认密码"),this);
    repassword_l->move(70,160);
    repassword_e = new QLineEdit(this);
    repassword_e->move(160,160);
    repassword_e->setPlaceholderText(tr("请再次输入密码"));
    repassword_e->setEchoMode(QLineEdit::Password);
    user_type = new QButtonGroup(this);
    user_type1 = new QRadioButton(tr("审核员"),this);
    user_type1->move(70,190);
    user_type2 = new QRadioButton(tr("采购员"),this);
    user_type2->move(150,190);
    user_type3 = new QRadioButton(tr("销售员"),this);
    user_type3->move(230,190);
    user_type->addButton(user_type1,1);
    user_type->addButton(user_type2,2);
    user_type->addButton(user_type3,3);
    submit = new QPushButton(tr("提交"),this);
    submit->move(70,220);
    cancel = new QPushButton(tr("取消"),this);
    cancel->move(220,220);

    connect(submit,&QPushButton::clicked,this,&RegisterDialog::reg_submit);
    connect(cancel,&QPushButton::clicked,this,&RegisterDialog::close);
}

RegisterDialog::~RegisterDialog() {

}

void RegisterDialog::reg_submit() {
    if(phonenumber_e->text().isEmpty() || name_e->text().isEmpty() ||password_e->text().isEmpty() ||
            repassword_e->text().isEmpty() ||user_type->checkedId() == -1) {
        QMessageBox::warning(this,tr("提示"),tr("请输入完整信息！"),QMessageBox::Yes);
        return;
    }
    if(password_e->text() != repassword_e->text()) {
        QMessageBox::warning(this,tr("提示"),tr("两次密码不匹配！"),QMessageBox::Yes);
        return;
    }
    if(dmsqlmanager->reg(phonenumber_e->text(),name_e->text(),password_e->text(),user_type->checkedId())) {
        accept();
    }
    else QMessageBox::warning(this,tr("提示"),tr("提交失败！"),QMessageBox::Yes);
}
