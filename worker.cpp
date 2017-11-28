#include "worker.h"

worker::worker(QObject *parent) : QObject(parent)
{
    QStringList result = cfg.read("CONFIG");
    interval = result.at(0).toInt();
    rootFormula = result.at(1);

    result = cfg.read("REDIS");
    redis_address = result.at(0);
    redis_port = result.at(1).toInt();

    db = db_mysql.connect_db("Monita_Formula");
    result = db_mysql.read(db, "call get_formula()", QStringList());
    for (int i = 0; i < result.length(); i+=2) {
        listTitikukur.append(result.at(i));
        listFormula.append(result.at(i+1));
    }

    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(doWork()));
    t->start(interval);
}

void worker::doWork()
{
    for (int i = 0; i < listTitikukur.length(); i++) {
        if (!listTitikukur.at(i).isEmpty() && !listFormula.at(i).isEmpty()) {
            QByteArray jsonFile = readFormula(rootFormula + listFormula.at(i));
            QJsonDocument JsonDoc = QJsonDocument::fromJson(jsonFile);
            QJsonObject object = JsonDoc.object();
            QJsonObject monita_formula = object.value("monita_formula").toObject();

            QString titik_ukur = monita_formula.value("titik_ukur").toString();
            QJsonValue parameter = monita_formula.value("parameter");
            QStringList par;
            if (parameter.isArray()) {
                foreach (const QJsonValue & v,  parameter.toArray()) {
                    par.append(v.toString());
                }
            } else {
                par.append(parameter.toString());
            }
            QString formula = "(function(){" +
                    monita_formula.value("formula").toString()
                    + "})";
            for (int j = 0; j < par.length(); j++) {
                QString query = par.at(j);
                QStringList result = db_mysql.read(db, query, QStringList());
                if (result.length() > 0) {
                    par[j] = result.at(0);
                } else {
                    par[j] = "0";
                }
                formula = formula.replace(":p"+QString::number(j), par.at(j));
            }
            double value = QScriptEngine().evaluate(formula).call().toNumber();
            rds.reqRedis("hset monita_service:realtime FORMULA;" +
                         titik_ukur +
                         " " +
                         QString::number(QDateTime::currentDateTime().toTime_t()) + ";" +
                         QString::number(value),
                    redis_address, redis_port);
        }
    }
}

QByteArray worker::readFormula(QString path)
{
    QFile formula_json_file(path);
    if (formula_json_file.open(QIODevice::ReadWrite)) {
        QByteArray readFile = formula_json_file.readAll();
        return readFile;
    } else {
        return QByteArray();
    }
}
