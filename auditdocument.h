#ifndef AUDITDOCUMENT_H
#define AUDITDOCUMENT_H
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QCheckBox>
#include <QPushButton>
#include <vector>
using std::vector;

class AuditDocument : public QDialog
{

private:
    int op_flag;
    QVBoxLayout *audit_main_layout;
    QHBoxLayout *btn_layout;
    QTableView *audit_document_view;
    QStandardItemModel *audit_document_list;
    vector<QCheckBox*> checkbox;
    QPushButton *submit;
    QPushButton *cancel;
    vector<int> *dnumber_list;
    vector<int> *gnumber_list;
    vector<int> *count_list;

public:
    AuditDocument(vector<int> *dnumber_list, vector<int> *gnumber_list, QStringList *gname_list,
                  QStringList *dtime_list, vector<int> *count_list, vector<int> *state_list, int op_flag);
    ~AuditDocument();

private slots:
    void submit_audit_info();
};

#endif // AUDITDOCUMENT_H
