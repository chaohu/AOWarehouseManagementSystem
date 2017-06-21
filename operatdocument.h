#ifndef OPERATINDOCUMENT_H
#define OPERATINDOCUMENT_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <vector>
using std::vector;

class OperatDocument : public QDialog
{

private:
    int op_flag;
    QLabel *number_l;
    QLabel *good_count_l;
    QLineEdit *number_e;
    QLineEdit *good_count_e;
    QPushButton *submit_btn;
    QPushButton *cancel_btn;
    vector<int> *number_list;
    QComboBox *goods_name_list;


public:
    OperatDocument(vector<int> *number_list,QStringList *name_list,int op_flag);
    ~OperatDocument();

private slots:
    void submit_in_document();
};

#endif // OPERATINDOCUMENT_H
