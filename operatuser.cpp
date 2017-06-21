#include "operatuser.h"
#include "dmsqlmanager.h"

extern DMSqlManager *dmsqlmanager;

OperatUser::OperatUser(QStringList *phonenumber_list,QStringList *name_list,vector<int> *usertype_list,int op_flag) {
    int i = 0;
    this->phonenumber_list = phonenumber_list;
    this->op_flag = op_flag;
    operat_main_layout = new QVBoxLayout(this);
    this->setGeometry(200,50,700,400);
    apply_user_view = new QTableView();
    apply_user_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    apply_user_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    apply_user_list = new QStandardItemModel();
    apply_user_list->setHorizontalHeaderItem(0,new QStandardItem(tr("手机号")));
    apply_user_list->setHorizontalHeaderItem(1,new QStandardItem(tr("姓名")));
    apply_user_list->setHorizontalHeaderItem(2,new QStandardItem(tr("用户类别")));
    if(op_flag == 0 || op_flag == 1) apply_user_list->setHorizontalHeaderItem(3,new QStandardItem(tr("请选择")));
    apply_user_view->setModel(apply_user_list);
    while(i < phonenumber_list->size()) {
        if(op_flag == 0 || op_flag == 1) {
            QStandardItem *number_list = new QStandardItem(QString::number(i));
            apply_user_list->setItem(i,3,number_list);
            QModelIndex index = apply_user_list->indexFromItem(number_list);
            QCheckBox *box = new QCheckBox(apply_user_view);
            checkbox.push_back(box);
            apply_user_view->setIndexWidget(index,box);
        }
        apply_user_list->setItem(i,0,new QStandardItem(phonenumber_list->at(i)));
        apply_user_list->setItem(i,1,new QStandardItem(name_list->at(i)));
        switch (usertype_list->at(i)) {
        case 1: apply_user_list->setItem(i,2,new QStandardItem("审核员"));break;
        case 2: apply_user_list->setItem(i,2,new QStandardItem("采购员"));break;
        case 3: apply_user_list->setItem(i,2,new QStandardItem("销售员"));break;
        default:
            break;
        }
        i++;
    }
    operat_main_layout->addWidget(apply_user_view);

    btn_layout = new QHBoxLayout();
    if(op_flag == 0 || op_flag == 1) {
        submit = new QPushButton(tr("提交"));
        btn_layout->addWidget(submit);
        connect(submit,&QPushButton::clicked,this,&OperatUser::submit_agree_choice);
    }
    cancel = new QPushButton(tr("取消"));
    btn_layout->addWidget(cancel);
    operat_main_layout->addLayout(btn_layout);

    connect(cancel,&QPushButton::clicked,this,&OperatUser::close);
}

OperatUser::~OperatUser() {

}

void OperatUser::submit_agree_choice() {
    int i = 0;
    while (i < phonenumber_list->size()) {
        if(checkbox.at(i)->isChecked()) {
            if(op_flag == 0) dmsqlmanager->agree_apply_user(phonenumber_list->at(i));
            else if(op_flag == 1) dmsqlmanager->delete_user(phonenumber_list->at(i));
        }
        i++;
    }
    accept();
}
