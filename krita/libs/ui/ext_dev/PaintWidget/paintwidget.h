#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class PaintWidget;
}

QT_END_NAMESPACE

class LeftTool;
class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget();

    void resizeEvent(QResizeEvent *event) override;
private Q_SLOTS:
    void on_toolButton_gallery_clicked();

    void on_toolButton_color_clicked();

private:
    Ui::PaintWidget *ui;
    LeftTool* m_leftTool{};

};
#endif // PAINTWIDGET_H
