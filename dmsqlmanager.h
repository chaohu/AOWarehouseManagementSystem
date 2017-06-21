#ifndef DMSQLMANAGER_H
#define DMSQLMANAGER_H

#include <windows.h>
#include <stdio.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <odbcss.h>
#include <QString>
#include <QCryptographicHash>
#include <vector>
using std::vector;

class DMSqlManager
{
private:
    SQLHENV henv = SQL_NULL_HENV;
    SQLHDBC hdbc = SQL_NULL_HDBC;
    SQLHSTMT hstmt = SQL_NULL_HSTMT;
    RETCODE ret;
    char strSQL[1024];

public:
    DMSqlManager();
    ~DMSqlManager();
    boolean login(QString phonenumber,QString password,int user_type);
    boolean reg(QString phonenumber,QString name,QString password,int user_type);
    boolean list_user(QStringList *phonenumber_list,QStringList *name_list,vector<int> *usertype_list,int op_flag);
    boolean agree_apply_user(const QString phonenumber);
    boolean delete_user(const QString phonenumber);
    boolean add_good(QString good_name,QString good_info);
    boolean list_goods(vector<int> *gnumber_list,QStringList *gname_list,QStringList *ginfo_list,vector<int> *gcount_list);
    boolean get_good_count(int gnumber,int *gcount);
    boolean delete_good(int gnumber);
    boolean audit_document(int dnumber,int op_flag);
    boolean alter_good_count(int gnumber,int count,int op_flag);
    boolean operat_document(int number,int count,int op_flag);
    boolean list_document(vector<int> *dnumber_list, vector<int> *gnumber_list, QStringList *gname_list,
                          QStringList *dtime_list,vector<int> *count_list,vector<int> *state_list, int op_flag);
};

#endif // DMSQLMANAGER_H
