#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtGui>
#include <QtQml>
#include <QTime>

#include "ftimer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    //FTimer workerTimer;
    qmlRegisterType<FTimer>("Frumkin.FTimer", 1, 0, "FTimer");


//    QString test = QStringLiteral("15+64359sgfsg*8 +safs66");
//    QStringList partsOfExpression = test.split(QRegExp("^(\\d{1,4}|\\*|\\+*)"));
//    QStringList partsOfExpression = test.split(QRegExp("[^\\*\\+\\D]"), QString::SkipEmptyParts);

    //qDebug() << partsOfExpression;



    // use this during development
    // for PUBLISHING, use the entry point below

    // use this instead of the above call to avoid deployment of the qml files and compile them into the binary with qt's resource system qrc
    // this is the preferred deployment option for publishing games to the app stores, because then your qml files and js files are protected
    // to avoid deployment of your qml files and images, also comment the DEPLOYMENTFOLDERS command in the .pro file
    // also see the .pro file for more details
    // vplay.setMainQmlFileName(QStringLiteral("qrc:/qml/Main.qml"));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
