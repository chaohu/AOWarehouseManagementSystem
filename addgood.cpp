#include "addgood.h"
#include "dmsqlmanager.h"
#include <QMessageBox>

extern DMSqlManager *dmsqlmanager;

AddGood::AddGood() {
    good_name_l = new QLabel(this);
    good_name_l->move(70,80);
    good_name_l->setText(tr("商品名："));
    good_name_e = new QLineEdit(this);
    good_name_e->move(140,80);
    good_name_e->setPlaceholderText(tr("请输入商品名"));

    good_info_l = new QLabel(this);
    good_info_l->move(70,130);
    good_info_l->setText(tr("货品信息："));
    good_info_e = new QLineEdit(this);
    good_info_e->move(140,130);
    good_info_e->setPlaceholderText(tr("请输入货品信息"));

    submit_btn = new QPushButton(tr("提交"),this);
    submit_btn->move(50,200);
    cancel_btn = new QPushButton(tr("取消"),this);
    cancel_btn->move(210,200);

    connect(submit_btn,&QPushButton::clicked,this,&AddGood::submit);
    connect(cancel_btn,&QPushButton::clicked,this,&AddGood::close);
}

AddGood::~AddGood() {

}


void AddGood::submit() {
    if(good_name_e->text().isEmpty() || good_info_e->text().isEmpty()) {
        QMessageBox::warning(this,tr("提示"),tr("请输入完整信息！"),QMessageBox::Yes);
        return;
    }
    if(dmsqlmanager->add_good(good_name_e->text(),good_info_e->text())) {
        accept();
    }
    else QMessageBox::warning(this,tr("提示"),tr("添加货品失败"),QMessageBox::Yes);
}
