#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>

class RegisterDialog : public QDialog
{
public:
    explicit RegisterDialog();
    ~RegisterDialog();

private:
    QLabel *phonenumber_l;
    QLabel *name_l;
    QLabel *password_l;
    QLabel *repassword_l;
    QLineEdit *phonenumber_e;
    QLineEdit *name_e;
    QLineEdit *password_e;
    QLineEdit *repassword_e;
    QButtonGroup *user_type;
    QRadioButton *user_type1;
    QRadioButton *user_type2;
    QRadioButton *user_type3;
    QPushButton *submit;
    QPushButton *cancel;

private slots:
    void reg_submit();

};

#endif // REGISTERDIALOG_H
