#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <InstanceTheme.h>
#include "InstanceDialog.h"
#include <QIcon>

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Fusion");
    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon("qrc:/ic_wan_cheng_logo.png"));

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    const auto instanceTheme = InstanceTheme::getInstance();
    qmlRegisterSingletonInstance<InstanceTheme>("InstanceTheme", 1, 0, "InstanceTheme", instanceTheme);
    qmlRegisterSingletonInstance<InstanceDialog>("InstanceDialog", 1, 0, "InstanceDialog", InstanceDialog::getInstance());

    engine.loadFromModule("WanchengsBatchMobileNumberOrganization", "Main");

    return QCoreApplication::exec();
}
