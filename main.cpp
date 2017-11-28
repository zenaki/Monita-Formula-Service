#include <QCoreApplication>
//#include <QtScript/QScriptEngine>
#include "worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    QString expression_string("(function() {"
//                              "var a = 3 + Math.sqrt(25) + Math.pow(3,2) + Math.log(1024) / Math.log(2); "
//                              "var b = a+2; "
//                              "return b;})");
//    QScriptEngine expression;
//    double my_val=expression.evaluate(expression_string).call().toNumber();

    worker w;

    return a.exec();
}
