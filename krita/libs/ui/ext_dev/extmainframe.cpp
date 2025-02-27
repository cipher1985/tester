#include "extmainframe.h"

#include <QHBoxLayout>
#include "extglobal.h"

#include "Gallery/gallerywidget.h"
#include "PaintWidget/paintwidget.h"
ExtMainFrame::ExtMainFrame(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_galleryWidget = new GalleryWidget;
    layout->addWidget(m_galleryWidget);

    m_paintWidget = new PaintWidget;
    layout->addWidget(m_paintWidget);

    showGallery();
}
#include <QTimer>
void ExtMainFrame::showGallery()
{
    m_galleryWidget->show();
    m_paintWidget->hide();
//    m_layout->setCurrentIndex(0);
}

void ExtMainFrame::switchPainter(const QString& file)
{
    m_galleryWidget->hide();
    m_paintWidget->show();
}
