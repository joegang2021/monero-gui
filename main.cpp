#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "clipboardAdapter.h"
#include "filter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    filter *eventFilter = new filter;
    app.installEventFilter(eventFilter);

    qmlRegisterType<clipboardAdapter>("moneroComponents", 1, 0, "Clipboard");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirectory", QApplication::applicationDirPath());
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    QObject *rootObject = engine.rootObjects().first();

    QObject::connect(eventFilter, SIGNAL(sequencePressed(QVariant,QVariant)), rootObject, SLOT(sequencePressed(QVariant,QVariant)));
    QObject::connect(eventFilter, SIGNAL(sequenceReleased(QVariant,QVariant)), rootObject, SLOT(sequenceReleased(QVariant,QVariant)));
    QObject::connect(eventFilter, SIGNAL(mousePressed(QVariant,QVariant,QVariant)), rootObject, SLOT(mousePressed(QVariant,QVariant,QVariant)));
    QObject::connect(eventFilter, SIGNAL(mouseReleased(QVariant,QVariant,QVariant)), rootObject, SLOT(mouseReleased(QVariant,QVariant,QVariant)));

    return app.exec();
}