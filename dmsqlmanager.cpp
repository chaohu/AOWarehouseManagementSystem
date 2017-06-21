#include "dmsqlmanager.h"
#include <QDebug>

DMSqlManager *dmsqlmanager = new DMSqlManager();
QString user_name;

DMSqlManager::DMSqlManager() {
    ret = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&henv);
    ret = SQLSetEnvAttr(henv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
    ret = SQLAllocHandle(SQL_HANDLE_DBC,henv,&hdbc);
    ret = SQLConnect(hdbc,(SQLCHAR*)"AOWMS",SQL_NTS,(SQLCHAR*)"SYSDBA",SQL_NTS,(SQLCHAR*)"SYSDBA",SQL_NTS);
    if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        qDebug("数据库连接失败");
        exit(0);
    }
}

DMSqlManager::~DMSqlManager() {
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC,hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV,henv);

}

boolean DMSqlManager::login(QString phonenumber, QString password, int user_type) {
    boolean flag;
    char szname[20];
    long cbname = 0;
    QString password_md5;
    QByteArray bb = QCryptographicHash::hash(password.toLocal8Bit(),QCryptographicHash::Md5);
    password_md5.append(bb.toHex());
    qDebug()<<phonenumber<<password_md5<<user_type;
    sprintf(strSQL,"SELECT NAME FROM AOWMS.USERS WHERE PHONENUMBER='%s' AND PASSWORD='%s' AND USERTYPE=%d AND STATE=1;",
            phonenumber.toLocal8Bit().data(),password_md5.toLocal8Bit().data(),user_type);
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    SQLBindCol(hstmt,1,SQL_C_CHAR,szname,sizeof(szname),&cbname);
    SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    ret = SQLFetchScroll(hstmt,SQL_FETCH_NEXT,0);
    if(ret == SQL_NO_DATA_FOUND) flag = false;
    else {
        user_name= user_name.fromLocal8Bit(szname);
        flag = true;
    }
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}

boolean DMSqlManager::reg(QString phonenumber, QString name, QString password, int user_type) {
    boolean flag;
    QString password_md5;
    QByteArray bb = QCryptographicHash::hash(password.toLocal8Bit(),QCryptographicHash::Md5);
    password_md5.append(bb.toHex());
    qDebug()<<phonenumber<<name<<password_md5<<user_type;
    sprintf(strSQL,"INSERT INTO AOWMS.USERS VALUES('%s','%s','%s',%d,0);",phonenumber.toLocal8Bit().data(),
            name.toLocal8Bit().data(),password_md5.toLocal8Bit().data(),user_type);
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    ret = SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    if(ret == SQL_SUCCESS) flag = true;
    else flag = false;
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}

boolean DMSqlManager::list_user(QStringList *phonenumber_list,QStringList *name_list,vector<int> *usertype_list,int op_flag) {
    boolean flag = false;
    QString name_s;
    char szphonenumber[13],szname[20];
    int szusertype;
    long cbphonenumber = 0,cbname = 0,cbusertype = 0;
    if(op_flag == 0) sprintf(strSQL,"SELECT PHONENUMBER,NAME,USERTYPE FROM AOWMS.USERS WHERE PHONENUMBER<>'00000000000' AND STATE=0;");
    else sprintf(strSQL,"SELECT PHONENUMBER,NAME,USERTYPE FROM AOWMS.USERS WHERE PHONENUMBER<>'00000000000' AND STATE=1;");
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    SQLBindCol(hstmt,1,SQL_C_CHAR,szphonenumber,sizeof(szphonenumber),&cbphonenumber);
    SQLBindCol(hstmt,2,SQL_C_CHAR,szname,sizeof(szname),&cbname);
    SQLBindCol(hstmt,3,SQL_C_SHORT,&szusertype,sizeof(szusertype),&cbusertype);
    SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    for(;;) {
        ret = SQLFetchScroll(hstmt,SQL_FETCH_NEXT,0);
        if(ret == SQL_NO_DATA_FOUND) break;
        else {
            phonenumber_list->push_back(szphonenumber);
            name_s = name_s.fromLocal8Bit(szname);
            name_list->push_back(name_s);
            usertype_list->push_back(szusertype);
            qDebug()<<szphonenumber<<name_s<<szusertype;
            flag = true;
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}

boolean DMSqlManager::agree_apply_user(const QString phonenumber) {
    boolean flag = false;
    sprintf(strSQL,"UPDATE AOWMS.USERS SET STATE=1 WHERE PHONENUMBER='%s';",phonenumber.toLocal8Bit().data());
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    ret = SQLFetchScroll(hstmt,SQL_FETCH_NEXT,0);
    if(ret == SQL_SUCCESS) flag = true;
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}


boolean DMSqlManager::delete_user(const QString phonenumber) {
    boolean flag = false;
    sprintf(strSQL,"DELETE FROM AOWMS.USERS WHERE PHONENUMBER='%s';",phonenumber.toLocal8Bit().data());
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    ret = SQLFetchScroll(hstmt,SQL_FETCH_NEXT,0);
    if(ret == SQL_SUCCESS) flag = true;
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}

boolean DMSqlManager::add_good(QString good_name, QString good_info) {
    boolean flag = false;
    sprintf(strSQL,"INSERT INTO AOWMS.GOODS(GNAME,GINFO,GCOUNT) VALUES('%s','%s',0);",good_name.toLocal8Bit().data(),
            good_info.toLocal8Bit().data());
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    ret = SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    if(ret == SQL_SUCCESS) flag = true;
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}

boolean DMSqlManager::list_goods(vector<int> *gnumber_list, QStringList *gname_list, QStringList *ginfo_list, vector<int> *gcount_list) {
    boolean flag = false;
    QString gname_s;
    QString ginfo_s;
    int szgnumber;
    char szgname[20],szginfo[30];
    int szgcount;
    long cbgnumber = 0,cbgname = 0,cbginfo = 0,cbgcount = 0;
    sprintf(strSQL,"SELECT GNUMBER,GNAME,GINFO,GCOUNT FROM AOWMS.GOODS");
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    SQLBindCol(hstmt,1,SQL_C_LONG,&szgnumber,sizeof(szgnumber),&cbgnumber);
    SQLBindCol(hstmt,2,SQL_C_CHAR,szgname,sizeof(szgname),&cbgname);
    SQLBindCol(hstmt,3,SQL_C_CHAR,szginfo,sizeof(szginfo),&cbginfo);
    SQLBindCol(hstmt,4,SQL_C_LONG,&szgcount,sizeof(szgcount),&cbgcount);
    SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    for(;;) {
        ret = SQLFetchScroll(hstmt,SQL_FETCH_NEXT,0);
        if(ret == SQL_NO_DATA_FOUND) break;
        else {
            gnumber_list->push_back(szgnumber);
            gname_s = gname_s.fromLocal8Bit(szgname);
            gname_list->push_back(gname_s);
            ginfo_s = ginfo_s.fromLocal8Bit(szginfo);
            ginfo_list->push_back(ginfo_s);
            gcount_list->push_back(szgcount);
            qDebug()<<szgnumber<<gname_s<<ginfo_s<<szgcount;
            flag = true;
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}

boolean DMSqlManager::get_good_count(int gnumber,int *gcount) {
    boolean flag;
    long cbgcount = 0;
    sprintf(strSQL,"SELECT GCOUNT FROM AOWMS.GOODS WHERE GNUMBER=%d",gnumber);
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    SQLBindCol(hstmt,1,SQL_C_LONG,gcount,sizeof(gcount),&cbgcount);
    SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    ret = SQLFetchScroll(hstmt,SQL_FETCH_NEXT,0);
    if(ret == SQL_NO_DATA_FOUND) flag = false;
    else {
        flag = true;
    }
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}

boolean DMSqlManager::delete_good(int gnumber) {
    boolean flag = false;
    sprintf(strSQL,"DELETE FROM AOWMS.GOODS WHERE GNUMBER=%d;",gnumber);
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    ret = SQLFetchScroll(hstmt,SQL_FETCH_NEXT,0);
    if(ret == SQL_SUCCESS) flag = true;
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}

boolean DMSqlManager::audit_document(int dnumber,int op_flag) {
    boolean flag = false;
    if(op_flag == 0) sprintf(strSQL,"UPDATE AOWMS.INDOCUMENT SET ISTATE=1 WHERE INUMBER=%d;",dnumber);
    else if(op_flag == 1) sprintf(strSQL,"UPDATE AOWMS.OUTDOCUMENT SET OSTATE=1 WHERE ONUMBER=%d;",dnumber);
    else sprintf(strSQL,"UPDATE AOWMS.LACKDOCUMENT SET LSTATE=1 WHERE LNUMBER=%d;",dnumber);
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    ret = SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    if(ret == SQL_SUCCESS) flag = true;
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}

boolean DMSqlManager::alter_good_count(int gnumber, int count, int op_flag) {
    boolean flag = false;
    if(op_flag == 0) sprintf(strSQL,"UPDATE AOWMS.GOODS SET GCOUNT=GCOUNT+%d WHERE GNUMBER=%d;",count,gnumber);
    else if(op_flag == 1) sprintf(strSQL,"UPDATE AOWMS.GOODS SET GCOUNT=GCOUNT-%d WHERE GNUMBER=%d;",count,gnumber);
    else sprintf(strSQL,"UPDATE AOWMS.GOODS SET GCOUNT=GCOUNT-%d WHERE GNUMBER=%d;",count,gnumber);
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    ret = SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    if(ret == SQL_SUCCESS) flag = true;
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}

boolean DMSqlManager::operat_document(int number, int count, int op_flag) {
    boolean flag = false;
    if(op_flag == 0) sprintf(strSQL,"INSERT INTO AOWMS.INDOCUMENT(GNUMBER,ICOUNT,ISTATE) VALUES(%d,%d,0);",number,count);
    else if(op_flag == 2) sprintf(strSQL,"INSERT INTO AOWMS.OUTDOCUMENT(GNUMBER,OCOUNT,OSTATE) VALUES(%d,%d,0);",number,count);
    else if(op_flag == 4) sprintf(strSQL,"INSERT INTO AOWMS.LACKDOCUMENT(GNUMBER,LCOUNT,LSTATE) VALUES(%d,%d,0);",number,count);
    else if(op_flag == 1) sprintf(strSQL,"UPDATE AOWMS.INDOCUMENT SET ICOUNT=%d WHERE INUMBER=%d;",count,number);
    else if(op_flag == 3) sprintf(strSQL,"UPDATE AOWMS.OUTDOCUMENT SET OCOUNT=%d WHERE ONUMBER=%d;",count,number);
    else sprintf(strSQL,"UPDATE AOWMS.LACKDOCUMENT SET LCOUNT=%d WHERE LNUMBER=%d;",count,number);
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    ret = SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    if(ret == SQL_SUCCESS) flag = true;
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}

boolean DMSqlManager::list_document(vector<int> *dnumber_list, vector<int> *gnumber_list, QStringList *gname_list,
                                    QStringList *dtime_list, vector<int> *count_list,vector<int> *state_list, int op_flag) {
    boolean flag = false;
    QString gname_s,dtime_s;
    int szdnumber,szgnumber,szcount,szstate;
    char szgname[20],szdtime[20];
    long cbdnumber = 0,cbgnumber = 0,cbgname = 0,cbdtime = 0,cbcount = 0,cbstate = 0;
    if(op_flag == 0) sprintf(strSQL,"SELECT INDOCUMENT.INUMBER,INDOCUMENT.GNUMBER,GOODS.GNAME,INDOCUMENT.ITIME,INDOCUMENT.ICOUNT,INDOCUMENT.ISTATE "
                                    " FROM AOWMS.INDOCUMENT,AOWMS.GOODS WHERE ISTATE=0 AND GOODS.GNUMBER=INDOCUMENT.GNUMBER "
                                    " ORDER BY INDOCUMENT.ITIME ASC");
    else if(op_flag == 1) sprintf(strSQL,"SELECT OUTDOCUMENT.ONUMBER,OUTDOCUMENT.GNUMBER,GOODS.GNAME,OUTDOCUMENT.OTIME,OUTDOCUMENT.OCOUNT,OUTDOCUMENT.OSTATE "
                                         " FROM AOWMS.OUTDOCUMENT,AOWMS.GOODS WHERE OSTATE=0 AND GOODS.GNUMBER=OUTDOCUMENT.GNUMBER "
                                         " ORDER BY OUTDOCUMENT.OTIME ASC");
    else if(op_flag == 2) sprintf(strSQL,"SELECT LACKDOCUMENT.LNUMBER,LACKDOCUMENT.GNUMBER,GOODS.GNAME,LACKDOCUMENT.LTIME,LACKDOCUMENT.LCOUNT,LACKDOCUMENT.LSTATE "
                                         " FROM AOWMS.LACKDOCUMENT,AOWMS.GOODS WHERE LSTATE=0 AND GOODS.GNUMBER=LACKDOCUMENT.GNUMBER "
                                         " ORDER BY LACKDOCUMENT.LTIME ASC");
    else if(op_flag == 3) sprintf(strSQL,"SELECT INDOCUMENT.INUMBER,INDOCUMENT.GNUMBER,GOODS.GNAME,INDOCUMENT.ITIME,INDOCUMENT.ICOUNT,INDOCUMENT.ISTATE "
                                         " FROM AOWMS.INDOCUMENT,AOWMS.GOODS WHERE GOODS.GNUMBER=INDOCUMENT.GNUMBER "
                                         " ORDER BY INDOCUMENT.ITIME ASC");
    else if(op_flag == 4) sprintf(strSQL,"SELECT OUTDOCUMENT.ONUMBER,OUTDOCUMENT.GNUMBER,GOODS.GNAME,OUTDOCUMENT.OTIME,OUTDOCUMENT.OCOUNT,OUTDOCUMENT.OSTATE "
                                         " FROM AOWMS.OUTDOCUMENT,AOWMS.GOODS WHERE GOODS.GNUMBER=OUTDOCUMENT.GNUMBER "
                                         " ORDER BY OUTDOCUMENT.OTIME ASC");
    else sprintf(strSQL,"SELECT LACKDOCUMENT.LNUMBER,LACKDOCUMENT.GNUMBER,GOODS.GNAME,LACKDOCUMENT.LTIME,LACKDOCUMENT.LCOUNT,LACKDOCUMENT.LSTATE "
                        " FROM AOWMS.LACKDOCUMENT,AOWMS.GOODS WHERE GOODS.GNUMBER=LACKDOCUMENT.GNUMBER "
                        " ORDER BY LACKDOCUMENT.LTIME ASC");
    //申请一个语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    SQLBindCol(hstmt,1,SQL_C_LONG,&szdnumber,sizeof(szdnumber),&cbdnumber);
    SQLBindCol(hstmt,2,SQL_C_LONG,&szgnumber,sizeof(szgnumber),&cbgnumber);
    SQLBindCol(hstmt,3,SQL_C_CHAR,szgname,sizeof(szgname),&cbgname);
    SQLBindCol(hstmt,4,SQL_C_CHAR,szdtime,sizeof(szdtime),&cbdtime);
    SQLBindCol(hstmt,5,SQL_C_LONG,&szcount,sizeof(szcount),&cbcount);
    SQLBindCol(hstmt,6,SQL_C_LONG,&szstate,sizeof(szstate),&cbstate);
    SQLExecDirect(hstmt,(SQLCHAR*)strSQL,SQL_NTS);
    for(;;) {
        ret = SQLFetchScroll(hstmt,SQL_FETCH_NEXT,0);
        if(ret == SQL_NO_DATA_FOUND) break;
        else {
            dnumber_list->push_back(szdnumber);
            gnumber_list->push_back(szgnumber);
            gname_s = gname_s.fromLocal8Bit(szgname);
            gname_list->push_back(gname_s);
            dtime_s = dtime_s.fromLocal8Bit(szdtime);
            dtime_list->push_back(dtime_s);
            count_list->push_back(szcount);
            state_list->push_back(szstate);
            flag = true;
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    return flag;
}
