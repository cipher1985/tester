#ifndef GALLERYWIDGET_H
#define GALLERYWIDGET_H

#include <QWidget>

namespace Ui {
class GalleryWidget;
}

class GalleryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryWidget(QWidget *parent = nullptr);
    ~GalleryWidget();
    QImage loadKraFile(const QString& filePath);
private Q_SLOTS:
    void on_toolButton_sel_clicked();
    void on_toolButton_close_clicked();
    void on_toolButton_new_image_clicked();
private:
    void setSelectMode(bool selectMode);
    Ui::GalleryWidget *ui;
};

#endif // GALLERYWIDGET_H
