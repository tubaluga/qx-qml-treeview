#include <QDir>
#include <QFileSystemModel>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "exampletreeitemmodel.h"

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QGuiApplication application(argc, argv);

    application.setOrganizationName("org.qx");
    application.setApplicationName("qx-treeview-example");
    application.setApplicationDisplayName(QObject::tr("Qt treeview example"));
    application.setApplicationVersion("1.0.0");

    qmlRegisterType<TreeItemModel>("Example", 1, 0, "ExampleTreeItemModel");

    QFileSystemModel *fs_model = new QFileSystemModel;
    fs_model->setRootPath(QDir::homePath());

    QQmlApplicationEngine *engine = new QQmlApplicationEngine;

    QQmlContext *context = engine->rootContext();

    context->setContextProperty("exampleModel", fs_model);

    engine->load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return application.exec();
}
