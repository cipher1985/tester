#include "gallerywidget.h"
#include "ui_gallerywidget.h"

#include "extglobal.h"

//#include <kis_image.h>
//#include <kis_doc2.h>
//#include <kis_loading_shape.h>

GalleryWidget::GalleryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalleryWidget)
{
    ui->setupUi(this);

    setSelectMode(false);
}

GalleryWidget::~GalleryWidget()
{
    delete ui;
}

QImage GalleryWidget::loadKraFile(const QString &filePath)
{
    /*
    // 创建一个 KisDoc2 对象，用于加载文档
    KisDoc2 doc;
    // 尝试加载 .kra 文件
    if (!doc.loadNativeFormat(filePath)) {
        qDebug() << "Failed to load .kra file:" << filePath;
        return QImage();
    }
    // 获取加载的图像
    KisImageSP image = doc.image();
    if (!image) {
        qDebug() << "Failed to get image from .kra file:" << filePath;
        return QImage();
    }
    // 创建一个 QImage 来存储图像数据
    QImage qImage(image->width(), image->height(), QImage::Format_RGBA8888);
    // 获取图像的像素数据
    KisPaintDeviceSP paintDevice = image->projection();
    for (int y = 0; y < image->height(); ++y) {
        for (int x = 0; x < image->width(); ++x) {
            KoColor color;
            paintDevice->pixel(x, y, &color);
            qImage.setPixelColor(x, y, QColor::fromRgba(color.toQColor().rgba()));
        }
    }
    return qImage;
    */
    return QImage();
}

void GalleryWidget::on_toolButton_sel_clicked()
{
    //点击选择
    setSelectMode(true);
}


void GalleryWidget::on_toolButton_close_clicked()
{
    //点击关闭
    setSelectMode(false);
}

void GalleryWidget::setSelectMode(bool selectMode)
{
    ui->toolButton_share->setVisible(selectMode);
    ui->toolButton_copy->setVisible(selectMode);
    ui->toolButton_del->setVisible(selectMode);
    ui->toolButton_close->setVisible(selectMode);

    ui->toolButton_sel->setVisible(!selectMode);
    ui->toolButton_new_image->setVisible(!selectMode);
}


void GalleryWidget::on_toolButton_new_image_clicked()
{
    EXT_GLOBAL().switchPainter("");
}

