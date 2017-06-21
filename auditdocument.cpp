#include "auditdocument.h"
#include "dmsqlmanager.h"
#include <QMessageBox>

extern DMSqlManager *dmsqlmanager;

AuditDocument::AuditDocument(vector<int> *dnumber_list, vector<int> *gnumber_list, QStringList *gname_list,
                             QStringList *dtime_list, vector<int> *count_list,vector<int> *state_list, int op_flag) {
    unsigned i = 0;
    this->op_flag = op_flag;
    this->dnumber_list = dnumber_list;
    this->gnumber_list = gnumber_list;
    this->count_list = count_list;
    audit_main_layout = new QVBoxLayout(this);
    this->setGeometry(200,50,700,400);
    audit_document_view = new QTableView();
    audit_document_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    audit_document_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    audit_document_list = new QStandardItemModel();
    if(op_flag == 0 || op_flag == 3) audit_document_list->setHorizontalHeaderItem(0,new QStandardItem(tr("进货单号")));
    else if(op_flag == 1 || op_flag == 4) audit_document_list->setHorizontalHeaderItem(0,new QStandardItem(tr("出货单号")));
    else audit_document_list->setHorizontalHeaderItem(0,new QStandardItem(tr("缺货单号")));
    audit_document_list->setHorizontalHeaderItem(1,new QStandardItem(tr("货品号")));
    audit_document_list->setHorizontalHeaderItem(2,new QStandardItem(tr("货品名")));
    audit_document_list->setHorizontalHeaderItem(3,new QStandardItem(tr("提交日期")));
    audit_document_list->setHorizontalHeaderItem(4,new QStandardItem(tr("货品数量")));
    audit_document_list->setHorizontalHeaderItem(5,new QStandardItem(tr("审核状态")));
    if(op_flag == 0 || op_flag == 1 || op_flag == 2) audit_document_list->setHorizontalHeaderItem(6,new QStandardItem(tr("请选择")));
    audit_document_view->setModel(audit_document_list);
    while(i < dnumber_list->size()) {
        if(op_flag == 0 || op_flag == 1 || op_flag == 2) {
            QStandardItem *dnumber_list_item = new QStandardItem(QString::number(i));
            audit_document_list->setItem(i,6,dnumber_list_item);
            QModelIndex index = audit_document_list->indexFromItem(dnumber_list_item);
            QCheckBox *box = new QCheckBox(audit_document_view);
            checkbox.push_back(box);
            audit_document_view->setIndexWidget(index,box);
        }
        audit_document_list->setItem(i,0,new QStandardItem(QString::number(dnumber_list->at(i))));
        audit_document_list->setItem(i,1,new QStandardItem(QString::number(gnumber_list->at(i))));
        audit_document_list->setItem(i,2,new QStandardItem(gname_list->at(i)));
        audit_document_list->setItem(i,3,new QStandardItem(dtime_list->at(i)));
        audit_document_list->setItem(i,4,new QStandardItem(QString::number(count_list->at(i))));
        audit_document_list->setItem(i,5,new QStandardItem(QString::number(state_list->at(i))));
        i++;
    }
    audit_main_layout->addWidget(audit_document_view);

    btn_layout = new QHBoxLayout();
    if(op_flag == 0 || op_flag == 1 || op_flag == 2) {
        submit = new QPushButton(tr("提交"));
        btn_layout->addWidget(submit);
        connect(submit,&QPushButton::clicked,this,&AuditDocument::submit_audit_info);
    }
    cancel = new QPushButton(tr("取消"));
    btn_layout->addWidget(cancel);
    audit_main_layout->addLayout(btn_layout);

    connect(cancel,&QPushButton::clicked,this,&AuditDocument::close);
}

AuditDocument::~AuditDocument() {

}

void AuditDocument::submit_audit_info() {
    unsigned i = 0;
    while (i < dnumber_list->size()) {
        if(checkbox.at(i)->isChecked()) {
            if(dmsqlmanager->alter_good_count(gnumber_list->at(i),count_list->at(i),op_flag)) {
                if(dmsqlmanager->audit_document(dnumber_list->at(i),op_flag)) {

                }
                else QMessageBox::warning(this,tr("提示"),tr("提交失败"),QMessageBox::Yes);
            }
            else QMessageBox::warning(this,tr("提示"),tr("数据更新失败"),QMessageBox::Yes);
        }
        i++;
    }
    accept();
}
