#include "extmainframe.h"

#include <QApplication>

#include "extglobal.h"
int main1(int argc, char *argv[])
{
    //启用对高DPI的支持
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    //使用高DPI像素图
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    //设置缩放因子不进行舍入
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication a(argc, argv);
    EXT_GLOBAL().init();
    return a.exec();
}
