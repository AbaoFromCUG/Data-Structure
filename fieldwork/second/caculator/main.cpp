#include"list/stack.h"
#include"stable.h"
#include"stack"
#include"caculator.h"
#include"lib/qml/framelesswindowhelper.h"
#include"caculator.h"


int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QGuiApplication app(argc,argv);

    qmlRegisterType<FramelessWindowHelper>("FramelessWindowHelper", 1, 0, "FramelessWindowHelper");
    qmlRegisterType<Caculator>("Caculator.abaopro.me",1,0,"Caculator");
    QQmlApplicationEngine engine;
    engine.addImportPath( ":/qml2/" );
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
