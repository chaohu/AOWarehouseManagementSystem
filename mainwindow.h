#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <vector>
using std::vector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMenu *users_manage;
    QAction *audit_user_btn;
    QAction *delete_user_btn;
    QAction *list_users_btn;
    QMenu *goods_manage;
    QAction *add_good_btn;
    QAction *delete_good_btn;
    QAction *list_goods_btn;
    QMenu *audit_manage;
    QAction *audit_in_btn;
    QAction *audit_out_btn;
    QAction *audit_lack_btn;
    QMenu *purchase_manage;
    QAction *submit_in_btn;
    QAction *alter_in_btn;
    QAction *list_in_btn;
    QMenu *sale_manage;
    QAction *submit_out_btn;
    QAction *alter_out_btn;
    QAction *list_out_btn;
    QAction *alter_lack_btn;
    QAction *list_lack_btn;
    QLabel *phonenumber_l;
    QLabel *name_l;
    QLabel *user_type_l;
    QString user_type_s;


private slots:
    void audit_user();
    void delete_user();
    void list_users();
    void add_good();
    void delete_good();
    void list_goods();
    void audit_in();
    void audit_out();
    void audit_lack();
    void submit_in();
    void alter_in();
    void list_in();
    void submit_out();
    void alter_out();
    void list_out();
    void alter_lack();
    void list_lack();
};

#endif // MAINWINDOW_H
