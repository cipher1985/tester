#include "hsbcolorpicker.h"

#include "hsbcolorringpicker.h"
#include "hsbcolorsliderpicker.h"
HSBColorPicker::HSBColorPicker(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    m_picker = new HSBColorRingPicker;
    layout->addWidget(m_picker);
    m_slider = new HSBColorSliderPicker;
    m_slider->setMaximumHeight(74);
    layout->addWidget(m_slider);
    layout->addStretch();
    //setStyleSheet("background-color:rgb(58, 58, 58);");

    m_slider->setStyleSheet("QLabel{"
        "font-family: PingFang SC, PingFang SC; "
        "font-weight: 300; font-size: 12px;color:#C8C8C8;} "
        "QWidget#sliderMain{background:#991B1B1B; border-radius:6px;}");
    connect(m_picker, &HSBColorRingPicker::sigColorChanged,
        this, [this](const QColor& color) {
            m_slider->setColor(color);
            emit sigColorChanged(color);
    });
    connect(m_slider, &HSBColorSliderPicker::sigColorChanged,
        this, [this](const QColor &color) {
            m_picker->setColor(color);
            emit sigColorChanged(color);
    });
}

void HSBColorPicker::setColor(const QColor &color)
{
    m_picker->setColor(color);
    m_slider->setColor(color);
}

QColor HSBColorPicker::getColor()
{
    return m_picker->getColor();
}
