
#include "calc_tf.h"
#include "QFile"

#include <QApplication>


int main(int argc, char* argv[]) {
#ifdef Q_OS_WIN32
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
    QApplication a(argc, argv);
//    CalcTF w;
//    w.show();
//    return a.exec();
    QFile qss(":/Resource/Qss/custom.qss");
    qss.open(QFile::ReadOnly);
    if(qss.isOpen()) {
        a.setStyleSheet(qss.readAll());
        qss.close();
    }
    CalcTF w;
    w.show();
    return a.exec();
}
