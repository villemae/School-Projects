#include <QApplication>
#include "engine.hh"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    StudentSide::Engine* engine = new StudentSide::Engine();
    //engine->createGame();


    return a.exec();
}


