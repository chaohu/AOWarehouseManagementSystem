#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dmsqlmanager.h"
#include "operatuser.h"
#include "addgood.h"
#include "operatgood.h"
#include "operatdocument.h"
#include "auditdocument.h"
#include <QDebug>

int user_type_login = -1;
QString phonenumber;
extern DMSqlManager *dmsqlmanager;
extern QString user_name;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    users_manage = menuBar()->addMenu(tr("&用户管理"));
    audit_user_btn = new QAction(tr("用户审核"),this);
    connect(audit_user_btn,&QAction::triggered,this,&MainWindow::audit_user);
    delete_user_btn = new QAction(tr("用户删除"),this);
    connect(delete_user_btn,&QAction::triggered,this,&MainWindow::delete_user);
    list_users_btn = new QAction(tr("用户查看"),this);
    connect(list_users_btn,&QAction::triggered,this,&MainWindow::list_users);
    users_manage->addAction(audit_user_btn);
    users_manage->addAction(delete_user_btn);
    users_manage->addAction(list_users_btn);
    goods_manage = menuBar()->addMenu(tr("&物品管理"));
    add_good_btn = new QAction(tr("物品添加"),this);
    connect(add_good_btn,&QAction::triggered,this,&MainWindow::add_good);
    delete_good_btn = new QAction(tr("物品删除"),this);
    connect(delete_good_btn,&QAction::triggered,this,&MainWindow::delete_good);
    list_goods_btn = new QAction(tr("物品查看"),this);
    connect(list_goods_btn,&QAction::triggered,this,&MainWindow::list_goods);
    goods_manage->addAction(add_good_btn);
    goods_manage->addAction(delete_good_btn);
    goods_manage->addAction(list_goods_btn);
    audit_manage = menuBar()->addMenu(tr("&审核管理"));
    audit_in_btn = new QAction(tr("审核进货单"),this);
    connect(audit_in_btn,&QAction::triggered,this,&MainWindow::audit_in);
    audit_out_btn = new QAction(tr("审核出货单"),this);
    connect(audit_out_btn,&QAction::triggered,this,&MainWindow::audit_out);
    audit_lack_btn = new QAction(tr("审核缺货单"),this);
    connect(audit_lack_btn,&QAction::triggered,this,&MainWindow::audit_lack);
    audit_manage->addAction(audit_in_btn);
    audit_manage->addAction(audit_out_btn);
    audit_manage->addAction(audit_lack_btn);
    purchase_manage = menuBar()->addMenu(tr("&采购管理"));
    submit_in_btn = new QAction(tr("提交进货单"),this);
    connect(submit_in_btn,&QAction::triggered,this,&MainWindow::submit_in);
    alter_in_btn = new QAction(tr("修改进货单"),this);
    connect(alter_in_btn,&QAction::triggered,this,&MainWindow::alter_in);
    list_in_btn = new QAction(tr("查看进货单"),this);
    connect(list_in_btn,&QAction::triggered,this,&MainWindow::list_in);
    purchase_manage->addAction(submit_in_btn);
    purchase_manage->addAction(alter_in_btn);
    purchase_manage->addAction(list_in_btn);
    sale_manage = menuBar()->addMenu(tr("&销售管理"));
    submit_out_btn = new QAction(tr("提交出货单"),this);
    connect(submit_out_btn,&QAction::triggered,this,&MainWindow::submit_out);
    alter_out_btn = new QAction(tr("修改出货单"),this);
    connect(alter_out_btn,&QAction::triggered,this,&MainWindow::alter_out);
    list_out_btn = new QAction(tr("查看出货单"),this);
    connect(list_out_btn,&QAction::triggered,this,&MainWindow::list_out);
    alter_lack_btn = new QAction(tr("修改缺货单"),this);
    connect(alter_lack_btn,&QAction::triggered,this,&MainWindow::alter_lack);
    list_lack_btn = new QAction(tr("查看缺货单"),this);
    connect(list_lack_btn,&QAction::triggered,this,&MainWindow::list_lack);
    sale_manage->addAction(submit_out_btn);
    sale_manage->addAction(alter_out_btn);
    sale_manage->addAction(list_out_btn);
    sale_manage->addAction(alter_lack_btn);
    sale_manage->addAction(list_lack_btn);

    switch (user_type_login) {
    case 0: {
        user_type_s = "管理员";
        audit_in_btn->setEnabled(false);
        audit_out_btn->setEnabled(false);
        audit_lack_btn->setEnabled(false);
        submit_in_btn->setEnabled(false);
        alter_in_btn->setEnabled(false);
        submit_out_btn->setEnabled(false);
        alter_out_btn->setEnabled(false);
        alter_lack_btn->setEnabled(false);
        break;
    }
    case 1: {
        user_type_s = "审核员";
        audit_user_btn->setEnabled(false);
        delete_user_btn->setEnabled(false);
        list_users_btn->setEnabled(false);
        add_good_btn->setEnabled(false);
        delete_good_btn->setEnabled(false);
        submit_in_btn->setEnabled(false);
        alter_in_btn->setEnabled(false);
        submit_out_btn->setEnabled(false);
        alter_out_btn->setEnabled(false);
        alter_lack_btn->setEnabled(false);
        break;
    }
    case 2: {
        user_type_s = "采购员";
        audit_user_btn->setEnabled(false);
        delete_user_btn->setEnabled(false);
        list_users_btn->setEnabled(false);
        add_good_btn->setEnabled(false);
        delete_good_btn->setEnabled(false);
        audit_in_btn->setEnabled(false);
        audit_out_btn->setEnabled(false);
        audit_lack_btn->setEnabled(false);
        submit_out_btn->setEnabled(false);
        alter_out_btn->setEnabled(false);
        alter_lack_btn->setEnabled(false);
        break;
    }
    default:
        user_type_s = "销售员";
        audit_user_btn->setEnabled(false);
        delete_user_btn->setEnabled(false);
        list_users_btn->setEnabled(false);
        add_good_btn->setEnabled(false);
        delete_good_btn->setEnabled(false);
        audit_in_btn->setEnabled(false);
        audit_out_btn->setEnabled(false);
        audit_lack_btn->setEnabled(false);
        submit_in_btn->setEnabled(false);
        alter_in_btn->setEnabled(false);
        break;
    }

    name_l = new QLabel(tr("欢迎您：").append(user_name),this);
    name_l->adjustSize();
    name_l->move(100,80);
    qDebug()<<user_name;
    phonenumber_l = new QLabel(tr("手机号：").append(phonenumber),this);
    phonenumber_l->adjustSize();
    phonenumber_l->move(100,130);
    user_type_l = new QLabel(tr("用户类别：").append(user_type_s),this);
    user_type_l->adjustSize();
    user_type_l->move(100,180);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::audit_user() {
    QStringList phonenumber_list,name_list;
    vector<int> usertype_list;
    dmsqlmanager->list_user(&phonenumber_list,&name_list,&usertype_list,0);
    OperatUser *operatuser= new OperatUser(&phonenumber_list,&name_list,&usertype_list,0);
    operatuser->exec();
}

void MainWindow::delete_user() {
    QStringList phonenumber_list,name_list;
    vector<int> usertype_list;
    dmsqlmanager->list_user(&phonenumber_list,&name_list,&usertype_list,1);
    OperatUser *operatuser= new OperatUser(&phonenumber_list,&name_list,&usertype_list,1);
    operatuser->exec();
}

void MainWindow::list_users() {
    QStringList phonenumber_list,name_list;
    vector<int> usertype_list;
    dmsqlmanager->list_user(&phonenumber_list,&name_list,&usertype_list,1);
    OperatUser *operatuser= new OperatUser(&phonenumber_list,&name_list,&usertype_list,2);
    operatuser->exec();

}

void MainWindow::add_good() {
    AddGood addgood;
    addgood.exec();
}

void MainWindow::delete_good() {
    vector<int> gnumber_list,gcount_list;
    QStringList gname_list,ginfo_list;
    dmsqlmanager->list_goods(&gnumber_list,&gname_list,&ginfo_list,&gcount_list);
    OperatGood *operatgood = new OperatGood(&gnumber_list,&gname_list,&ginfo_list,&gcount_list,0);
    operatgood->exec();
}

void MainWindow::list_goods() {
    vector<int> gnumber_list,gcount_list;
    QStringList gname_list,ginfo_list;
    dmsqlmanager->list_goods(&gnumber_list,&gname_list,&ginfo_list,&gcount_list);
    OperatGood *operatgood = new OperatGood(&gnumber_list,&gname_list,&ginfo_list,&gcount_list,1);
    operatgood->exec();
}

void MainWindow::audit_in() {
    vector<int> inumber_list,gnumber_list,icount_list,istate_list;
    QStringList gname_list,itime_list;
    dmsqlmanager->list_document(&inumber_list,&gnumber_list,&gname_list,&itime_list,&icount_list,&istate_list,0);
    AuditDocument *auditdocument = new AuditDocument(&inumber_list,&gnumber_list,&gname_list,&itime_list,&icount_list,&istate_list,0);
    auditdocument->exec();
}

void MainWindow::audit_out() {
    vector<int> onumber_list,gnumber_list,ocount_list,ostate_list;
    QStringList gname_list,otime_list;
    dmsqlmanager->list_document(&onumber_list,&gnumber_list,&gname_list,&otime_list,&ocount_list,&ostate_list,1);
    AuditDocument *auditdocument = new AuditDocument(&onumber_list,&gnumber_list,&gname_list,&otime_list,&ocount_list,&ostate_list,1);
    auditdocument->exec();
}

void MainWindow::audit_lack() {
    vector<int> lnumber_list,gnumber_list,lcount_list,lstate_list;
    QStringList gname_list,ltime_list;
    dmsqlmanager->list_document(&lnumber_list,&gnumber_list,&gname_list,&ltime_list,&lcount_list,&lstate_list,2);
    AuditDocument *auditdocument = new AuditDocument(&lnumber_list,&gnumber_list,&gname_list,&ltime_list,&lcount_list,&lstate_list,2);
    auditdocument->exec();
}

void MainWindow::submit_in() {
    vector<int> gnumber_list,gcount_list;
    QStringList gname_list,ginfo_list;
    dmsqlmanager->list_goods(&gnumber_list,&gname_list,&ginfo_list,&gcount_list);
    OperatDocument *operatdocument = new OperatDocument(&gnumber_list,&gname_list,0);
    operatdocument->exec();
}

void MainWindow::alter_in() {
    vector<int> inumber_list,gnumber_list,icount_list,istate_list;
    QStringList gname_list,itime_list;
    dmsqlmanager->list_document(&inumber_list,&gnumber_list,&gname_list,&itime_list,&icount_list,&istate_list,0);
    OperatDocument *operatdocument = new OperatDocument(&inumber_list,&gname_list,1);
    operatdocument->exec();
}

void MainWindow::list_in() {
    vector<int> inumber_list,gnumber_list,icount_list,istate_list;
    QStringList gname_list,itime_list;
    dmsqlmanager->list_document(&inumber_list,&gnumber_list,&gname_list,&itime_list,&icount_list,&istate_list,3);
    AuditDocument *auditdocument = new AuditDocument(&inumber_list,&gnumber_list,&gname_list,&itime_list,&icount_list,&istate_list,3);
    auditdocument->exec();
}

void MainWindow::submit_out() {
    vector<int> gnumber_list,gcount_list;
    QStringList gname_list,ginfo_list;
    dmsqlmanager->list_goods(&gnumber_list,&gname_list,&ginfo_list,&gcount_list);
    OperatDocument *operatdocument = new OperatDocument(&gnumber_list,&gname_list,2);
    operatdocument->exec();
}

void MainWindow::alter_out() {
    vector<int> onumber_list,gnumber_list,ocount_list,ostate_list;
    QStringList gname_list,otime_list;
    dmsqlmanager->list_document(&onumber_list,&gnumber_list,&gname_list,&otime_list,&ocount_list,&ostate_list,1);
    OperatDocument *operatdocument = new OperatDocument(&onumber_list,&gname_list,3);
    operatdocument->exec();
}

void MainWindow::list_out() {
    vector<int> onumber_list,gnumber_list,ocount_list,ostate_list;
    QStringList gname_list,otime_list;
    dmsqlmanager->list_document(&onumber_list,&gnumber_list,&gname_list,&otime_list,&ocount_list,&ostate_list,4);
    AuditDocument *auditdocument = new AuditDocument(&onumber_list,&gnumber_list,&gname_list,&otime_list,&ocount_list,&ostate_list,4);
    auditdocument->exec();
}

void MainWindow::alter_lack() {
    vector<int> lnumber_list,gnumber_list,lcount_list,lstate_list;
    QStringList gname_list,ltime_list;
    dmsqlmanager->list_document(&lnumber_list,&gnumber_list,&gname_list,&ltime_list,&lcount_list,&lstate_list,2);
    OperatDocument *operatdocument = new OperatDocument(&lnumber_list,&gname_list,5);
    operatdocument->exec();
}

void MainWindow::list_lack() {
    vector<int> lnumber_list,gnumber_list,lcount_list,lstate_list;
    QStringList gname_list,ltime_list;
    dmsqlmanager->list_document(&lnumber_list,&gnumber_list,&gname_list,&ltime_list,&lcount_list,&lstate_list,5);
    AuditDocument *auditdocument = new AuditDocument(&lnumber_list,&gnumber_list,&gname_list,&ltime_list,&lcount_list,&lstate_list,5);
    auditdocument->exec();
}
