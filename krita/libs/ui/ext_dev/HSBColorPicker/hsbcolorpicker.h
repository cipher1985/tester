#ifndef HSBCOLORPICKER_H
#define HSBCOLORPICKER_H

#include <QWidget>

class HSBColorRingPicker;
class HSBColorSliderPicker;
// 颜色HSB选择器类
class HSBColorPicker : public QWidget
{
    Q_OBJECT
public:
    HSBColorPicker(QWidget* parent = nullptr);
    void setColor(const QColor& color);
    QColor getColor();
Q_SIGNALS:
    void sigColorChanged(const QColor &color);
private:
    HSBColorRingPicker* m_picker{};
    HSBColorSliderPicker* m_slider{};
};

#endif // HSBCOLORPICKER_H
