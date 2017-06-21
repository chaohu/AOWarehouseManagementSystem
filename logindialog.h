#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>

class LoginDialog : public QDialog
{
public:
    LoginDialog();
    ~LoginDialog();

private:
    QLabel *phonenumber_l;
    QLabel *password_l;
    QLineEdit *phonenumber_e;
    QLineEdit *password_e;
    QButtonGroup *user_type;
    QRadioButton *user_type0;
    QRadioButton *user_type1;
    QRadioButton *user_type2;
    QRadioButton *user_type3;
    QPushButton *login_btn;
    QPushButton *reg_btn;

private slots:
    void login_onclick();
    void reg_onclick();

};

#endif // LOGINDIALOG_H
