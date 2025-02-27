#ifndef LEFTTOOL_H
#define LEFTTOOL_H

#include <QWidget>

namespace Ui {
class LeftTool;
}

class LeftTool : public QWidget
{
    Q_OBJECT

public:
    explicit LeftTool(QWidget *parent = nullptr);
    ~LeftTool();

private Q_SLOTS:
    void on_verticalSlider_brush_sliderPressed();
    void on_verticalSlider_brush_sliderReleased();
    void on_verticalSlider_brush_valueChanged(int value);

    void on_verticalSlider_alpha_sliderPressed();
    void on_verticalSlider_alpha_sliderReleased();
    void on_verticalSlider_alpha_valueChanged(int value);
private:
    Ui::LeftTool *ui;
};

#endif // LEFTTOOL_H
