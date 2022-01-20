#include "model.hh"
#include "control.hh"
#include "view.hh"

#include <memory>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // setup the dependencies required by the passive MCV model
    auto model{ std::make_shared<Model>() };
    auto view{ std::make_shared<View>(model) };
    auto control{ std::make_shared<Control>(model, view) };

    //give the QML side acces to the view and controller components
    auto context{ engine.rootContext() };
    context->setContextProperty("view", view.get());
    context->setContextProperty("control", control.get());


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
