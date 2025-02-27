#ifndef EXTMAINFRAME_H
#define EXTMAINFRAME_H

#include <QWidget>

#if defined(EXT_DEV_LIBRARY)
#  define EXT_DEV_EXPORT Q_DECL_EXPORT
#else
#  define EXT_DEV_EXPORT Q_DECL_IMPORT
#endif
//主界面框架
class EXT_DEV_EXPORT ExtMainFrame : public QWidget
{
    Q_OBJECT
public:
    explicit ExtMainFrame(QWidget *parent = nullptr);
    //显示图库
    void showGallery();
    //显示画板
    void switchPainter(const QString& file);
private:
    QWidget* m_galleryWidget{};
    QWidget* m_paintWidget{};
};

#endif // EXTMAINFRAME_H
