#ifndef MYSQL_H
#define MYSQL_H

#include "utama.h"

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QFile>
#include <QSettings>

class mysql
{
public:
    mysql();

    QString host;
    QString db_name;
    QString username;
    QString password;

    QSqlDatabase connect_db(QString name);
    void close(QSqlDatabase db);

    QStringList read(QSqlDatabase db, QString query, QStringList parameter);
    void write(QSqlDatabase db, QString query, QStringList parameter);
};

#endif // MYSQL_H
