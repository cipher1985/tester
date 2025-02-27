#include "extglobal.h"

#include <QStandardPaths>

#include "extmainframe.h"
// 使用 Q_GLOBAL_STATIC 创建单例实例
Q_GLOBAL_STATIC(ExtGlobal, extGlobalInstance)

ExtGlobal *ExtGlobal::instance()
{
    return extGlobalInstance;
}

ExtGlobal::ExtGlobal()
{
    //m_awesome = new fa::QtAwesome(this);
    //m_awesome->initFontAwesome();
    QString documentPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    m_workPath = QDir(documentPath);
    if (!m_workPath.exists()) {
        m_workPath.mkpath(".");
    }
}

void ExtGlobal::init()
{
    m_mainFrame = new ExtMainFrame;
    m_mainFrame->show();
}

QString ExtGlobal::getResFile(const QString &fileName)
{
    return QString(":/ResExt/mipmap-mdpi/%1").arg(fileName);
}

void ExtGlobal::showGallery()
{
    m_mainFrame->showGallery();
}

void ExtGlobal::switchPainter(const QString &file)
{
    m_mainFrame->switchPainter(file);
}

