#ifndef EXTGLOBAL_H
#define EXTGLOBAL_H

#include <QObject>
#include <QGlobalStatic>
#include <QDir>

class ExtMainFrame;
class ExtGlobal : public QObject
{
    Q_OBJECT
public:
    static ExtGlobal* instance();
    //初始化
    void init();
    //获得资源文件名
    QString getResFile(const QString& fileName);
    //显示图库
    void showGallery();
    //显示画板
    void switchPainter(const QString& file);
public:
    ExtGlobal();
    ~ExtGlobal() = default;
private:
    Q_DISABLE_COPY(ExtGlobal)
private:
    QDir m_workPath;
    ExtMainFrame* m_mainFrame{};
};

#define EXT_GLOBAL() (*ExtGlobal::instance())
//#define EXT_AWESOME() (*ExtGlobal::instance()->m_awesome)
#endif // EXTGLOBAL_H
