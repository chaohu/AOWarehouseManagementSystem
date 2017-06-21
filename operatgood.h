#ifndef DELETEGOOD_H
#define DELETEGOOD_H
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QStandardItem>
#include <QCheckBox>
#include <QPushButton>
#include <vector>
using std::vector;

class OperatGood : public QDialog
{

private:
    int op_flag;
    QVBoxLayout *operat_main_layout;
    QHBoxLayout *btn_layout;
    QTableView *operat_good_view;
    QStandardItemModel *operat_good_list;
    vector<QCheckBox*> checkbox;
    QPushButton *submit;
    QPushButton *cancel;
    vector<int> *gnumber_list;

public:
    OperatGood(vector<int> *gnumber_list, QStringList *gname_list, QStringList *ginfo_list, vector<int> *gcount_list, int op_flag);
    ~OperatGood();

private slots:
    void submit_delete_choice();
};

#endif // DELETEGOOD_H
