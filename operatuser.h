#ifndef AUDITUSER_H
#define AUDITUSER_H
#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <vector>
using std::vector;

class OperatUser : public QDialog
{

private:
    QVBoxLayout *operat_main_layout;
    QHBoxLayout *btn_layout;
    QTableView *apply_user_view;
    QStandardItemModel *apply_user_list;
    vector<QCheckBox*> checkbox;
    QPushButton *submit;
    QPushButton *cancel;
    QStringList *phonenumber_list;
    int op_flag;

public:
    OperatUser(QStringList *phonenumber_list,QStringList *name_list,vector<int> *usertype_list,int op_flag);
    ~OperatUser();


private slots:
    void submit_agree_choice();

};

#endif // AUDITUSER_H
