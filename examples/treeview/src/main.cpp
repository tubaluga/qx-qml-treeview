#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char **argv)
{
    QGuiApplication application(argc, argv);

    application.setOrganizationName("org.qx");
    application.setApplicationName("qx-treeview-example");
    application.setApplicationDisplayName(QObject::tr("Qt treeview example"));
    application.setApplicationVersion("1.0.0");

    QQmlApplicationEngine *engine = new QQmlApplicationEngine;
    engine->load(QUrl(QLatin1String("qrc:/qml/ApplicationWindow.qml")));

    return application.exec();
}
