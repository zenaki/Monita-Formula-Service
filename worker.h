#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QtScript/QScriptEngine>

#include "utama.h"
#include "mysql.h"
#include "redis.h"
#include "config.h"

class worker : public QObject
{
    Q_OBJECT
public:
    explicit worker(QObject *parent = 0);

private:
    config cfg;
    int interval;
    QString rootFormula;

    redis   rds;
    QString redis_address;
    int     redis_port;

    mysql db_mysql;
    QSqlDatabase db;

    QStringList listTitikukur;
    QStringList listFormula;

    QByteArray readFormula(QString path);

private slots:
    void doWork();
};

#endif // WORKER_H
