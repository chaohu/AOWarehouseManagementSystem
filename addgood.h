#ifndef ADDGOOD_H
#define ADDGOOD_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class AddGood : public QDialog
{

private:
    QLabel *good_name_l;
    QLabel *good_info_l;
    QLineEdit *good_name_e;
    QLineEdit *good_info_e;
    QPushButton *submit_btn;
    QPushButton *cancel_btn;

public:
    AddGood();
    ~AddGood();


private slots:
    void submit();
};

#endif // ADDGOOD_H
