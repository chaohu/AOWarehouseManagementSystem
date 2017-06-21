#include "operatgood.h"
#include "dmsqlmanager.h"

extern DMSqlManager *dmsqlmanager;

OperatGood::OperatGood(vector<int> *gnumber_list, QStringList *gname_list, QStringList *ginfo_list, vector<int> *gcount_list,
                       int op_flag) {
    int i = 0;
    this->gnumber_list = gnumber_list;
    this->op_flag = op_flag;
    operat_main_layout = new QVBoxLayout(this);
    this->setGeometry(200,50,700,400);
    operat_good_view = new QTableView();
    operat_good_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    operat_good_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    operat_good_list = new QStandardItemModel();
    operat_good_list->setHorizontalHeaderItem(0,new QStandardItem(tr("序号")));
    operat_good_list->setHorizontalHeaderItem(1,new QStandardItem(tr("名称")));
    operat_good_list->setHorizontalHeaderItem(2,new QStandardItem(tr("信息")));
    operat_good_list->setHorizontalHeaderItem(3,new QStandardItem(tr("数量")));
    if(op_flag == 0) operat_good_list->setHorizontalHeaderItem(4,new QStandardItem(tr("选择")));
    operat_good_view->setModel(operat_good_list);
    while(i < (int)gnumber_list->size()) {
        if(op_flag == 0) {
            QStandardItem *c_gnumber_list = new QStandardItem(QString::number(i));
            operat_good_list->setItem(i,4,c_gnumber_list);
            QModelIndex index = operat_good_list->indexFromItem(c_gnumber_list);
            QCheckBox *box = new QCheckBox(operat_good_view);
            checkbox.push_back(box);
            operat_good_view->setIndexWidget(index,box);
        }
        operat_good_list->setItem(i,0,new QStandardItem(QString::number(gnumber_list->at(i))));
        operat_good_list->setItem(i,1,new QStandardItem(gname_list->at(i)));
        operat_good_list->setItem(i,2,new QStandardItem(ginfo_list->at(i)));
        operat_good_list->setItem(i,3,new QStandardItem(QString::number(gcount_list->at(i))));
        i++;
    }
    operat_main_layout->addWidget(operat_good_view);

    btn_layout = new QHBoxLayout();
    if(op_flag == 0) {
        submit = new QPushButton(tr("提交"));
        btn_layout->addWidget(submit);
        connect(submit,&QPushButton::clicked,this,&OperatGood::submit_delete_choice);
    }
    cancel = new QPushButton(tr("取消"));
    btn_layout->addWidget(cancel);
    operat_main_layout->addLayout(btn_layout);

    connect(cancel,&QPushButton::clicked,this,&OperatGood::close);
}

OperatGood::~OperatGood() {

}

void OperatGood::submit_delete_choice() {
    unsigned i = 0;
    while (i < gnumber_list->size()) {
        if(checkbox.at(i)->isChecked()) {
            dmsqlmanager->delete_good(gnumber_list->at(i));
        }
        i++;
    }
    accept();
}
