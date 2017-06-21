#include "operatdocument.h"
#include "dmsqlmanager.h"
#include <QMessageBox>
#include <QDebug>

extern DMSqlManager *dmsqlmanager;

OperatDocument::OperatDocument(vector<int> *number_list,QStringList *name_list,int op_flag) {
    this->op_flag = op_flag;
    this->number_list = number_list;
    number_l = new QLabel(this);
    number_l->move(70,80);
    if(op_flag == 0 || op_flag == 2 || op_flag == 4) number_l->setText(tr("商品："));
    else if(op_flag == 1)number_l->setText(tr("进货单号："));
    else if(op_flag == 3)number_l->setText(tr("出货单号："));
    else number_l->setText(tr("缺货单号："));
//    number_e = new QLineEdit(this);
//    number_e->move(140,80);
//    if(op_flag == 0 || op_flag == 2 || op_flag == 4) number_e->setPlaceholderText(tr("请输入商品号"));
//    else if(op_flag == 1) number_e->setPlaceholderText(tr("请输入进货单号"));
//    else if(op_flag == 3) number_e->setPlaceholderText(tr("请输入出货单号"));
//    else number_e->setPlaceholderText(tr("请输入缺货单号"));

    goods_name_list = new QComboBox(this);
    goods_name_list->move(140,80);
    if(op_flag == 0 || op_flag == 2 || op_flag == 4) goods_name_list->addItems(*name_list);
    else {
        unsigned i = 0;
        while(i < number_list->size()) {
            goods_name_list->addItem(QString::number(number_list->at(i)));
            i++;
        }
    }

    good_count_l = new QLabel(this);
    good_count_l->move(70,130);
    good_count_l->setText(tr("货品数量："));
    good_count_e = new QLineEdit(this);
    good_count_e->move(140,130);
    good_count_e->setPlaceholderText(tr("请输入货品数量"));

    submit_btn = new QPushButton(tr("提交"),this);
    submit_btn->move(50,200);
    cancel_btn = new QPushButton(tr("取消"),this);
    cancel_btn->move(210,200);

    connect(submit_btn,&QPushButton::clicked,this,&OperatDocument::submit_in_document);
    connect(cancel_btn,&QPushButton::clicked,this,&OperatDocument::close);

}

OperatDocument::~OperatDocument() {

}

void OperatDocument::submit_in_document() {
    if(good_count_e->text().isEmpty()) {
        QMessageBox::warning(this,tr("提示"),tr("请输入完整信息！"),QMessageBox::Yes);
        return;
    }
    if(op_flag == 2 || op_flag == 3) {
        int zz = 1;
        dmsqlmanager->get_good_count(number_list->at(goods_name_list->currentIndex()),&zz);
        if(zz - good_count_e->text().toInt() < 0) {
//            QMessageBox::warning(this,tr("提示"),tr("仓库货品不足"),QMessageBox::Yes,QMessageBox::No);
            QMessageBox lack_warning(QMessageBox::NoIcon,"提示","仓库货品不足,是否提交缺货单",QMessageBox::Yes|QMessageBox::No,this);
            if(lack_warning.exec() == QMessageBox::No) return;
            else op_flag = 4;
        }
    }
    if(dmsqlmanager->operat_document(number_list->at(goods_name_list->currentIndex()),good_count_e->text().toInt(),op_flag)) {
        accept();
    }
    else QMessageBox::warning(this,tr("提示"),tr("提交失败"),QMessageBox::Yes);
}
