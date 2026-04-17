#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <InstanceTheme.h>
#include "InstanceDialog.h"

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Fusion");
    QGuiApplication app(argc, argv);

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
