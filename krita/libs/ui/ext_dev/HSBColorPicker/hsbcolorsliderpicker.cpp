#include "hsbcolorsliderpicker.h"

#include <QPainter>
#include <QStyleOption>
#include <QStyleOptionSlider>
#include <QLabel>
#include <QPainter>

HSBColorSlider::HSBColorSlider(HSBType type,
    Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent), m_type(type) {}

void HSBColorSlider::setHueSlider(HSBColorSlider *hSlider)
{
    m_hSlider = hSlider;
}

void HSBColorSlider::paintEvent(QPaintEvent *event)
{
    // 绘制滑动条
    QSlider::paintEvent(event);
    // 平滑样式
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing);
    // 获取滑块的样式选项
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect handleRect = style()->subControlRect(
        QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    // 获取当前颜色
    QColor color;
    if (this->m_type == HSBType::H) {
        int hue = this->value();
        color = QColor::fromHsv(hue, 255, 255);
    } else if (this->m_type == HSBType::S) {
        int hue = 0;
        if(m_hSlider)
            hue = m_hSlider->value();
        int saturation = this->value();
        color = QColor::fromHsv(hue, saturation * 255 / 100, 255);
    } else if (this->m_type == HSBType::B) {
        int bright = this->value();
        color = QColor::fromHsv(0, 0, bright * 255 / 100);
    }
    // 绘制圆形白边的滑块
    int radius = qMin(handleRect.width(), handleRect.height()) / 2;
    QPoint center(handleRect.center());
    painter.setPen(QPen(Qt::white, 2));
    painter.setBrush(color);
    painter.drawEllipse(center, radius, radius);
}
/////////////////////////////////////////////////////////////////////////
HSBColorSliderPicker::HSBColorSliderPicker(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);

    createSlider(layout, HSBColorSlider::HSBType::H, "H", 0, 359);
    layout->addStretch();
    createSlider(layout, HSBColorSlider::HSBType::S, "S", 0, 100);
    layout->addStretch();
    createSlider(layout, HSBColorSlider::HSBType::B, "B", 0, 100);

    setObjectName("sliderMain");
    setStyleSheet("QWidget{background:transparent;}");
    //setStyleSheet("QLabel{color:rgb(160, 160, 160);} QWidget{background:transparent;}"
    //    "QWidget#main{background:rgba(0, 0, 0, 120); border-radius:4px;}");
}

void HSBColorSliderPicker::setHue(int hue)
{
    m_sliderH->setValue(hue);
}

void HSBColorSliderPicker::setSaturation(int saturation)
{
    m_sliderS->setValue(saturation);
}

void HSBColorSliderPicker::setBright(int bright)
{
    m_sliderB->setValue(bright);
}

void HSBColorSliderPicker::setColor(const QColor &color)
{
    int h, s, v;
    color.getHsv(&h, &s, &v);

    m_sliderH->setValue(h);
    m_sliderS->setValue(qRound(s * 100.0 / 255.0));
    m_sliderB->setValue(qRound(v * 100.0 / 255.0));

    updateSaturationBG(h);
}

QColor HSBColorSliderPicker::getColor() const
{
    return QColor::fromHsv(
        m_sliderH->value(),
        m_sliderS->value() * 255 / 100,
        m_sliderB->value() * 255 / 100);
}

void HSBColorSliderPicker::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void HSBColorSliderPicker::createSlider(QVBoxLayout *layout,
    HSBColorSlider::HSBType type, const QString &label, int min, int max)
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);

    QLabel* labelWidget = new QLabel(label);
    labelWidget->setFixedWidth(20);
    hLayout->addWidget(labelWidget);
    hLayout->addSpacing(10);
    labelWidget->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QLabel* valueLabel = new QLabel("0");
    valueLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    valueLabel->setFixedWidth(30);
    HSBColorSlider* slider = new HSBColorSlider(type, Qt::Horizontal, this);
    slider->setRange(min, max);
    if (type == HSBColorSlider::HSBType::H) {
        QString styleData = createStyleData(
            "background: qlineargradient("
            "x1:0, y1:0, x2:1, y2:0, stop:0 hsv(0, 255, 255), "
            "stop:0.1 hsv(36, 255, 255), stop:0.2 hsv(72, 255, 255), "
            "stop:0.3 hsv(108, 255, 255), stop:0.4 hsv(144, 255, 255), "
            "stop:0.5 hsv(180, 255, 255), stop:0.6 hsv(216, 255, 255), "
            "stop:0.7 hsv(252, 255, 255), stop:0.8 hsv(288, 255, 255), "
            "stop:0.9 hsv(324, 255, 255), stop:1 hsv(359, 255, 255)); ");
        slider->setStyleSheet(styleData);
        connect(slider, &QSlider::valueChanged, this, [this, valueLabel](int value) {
            updateSaturationBG(value);
            valueLabel->setText(QString::number(value).rightJustified(4, ' '));
            emit sigColorChanged(getColor());
        });
        m_sliderH = slider;
    } else if (type == HSBColorSlider::HSBType::S) {
        slider->setHueSlider(m_sliderH);
        QString styleData = createStyleData(QString(
            "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
            "stop:0 hsv(%1, 0, 255), stop:1 hsv(%1, 255, 255));").arg(slider->value()));
        slider->setStyleSheet(styleData);
        connect(slider, &QSlider::valueChanged, this, [this, valueLabel](int value) {
            valueLabel->setText(QString("%1%").arg(QString::number(value).rightJustified(3, ' ')));
            emit sigColorChanged(getColor());
        });
        m_sliderS = slider;
    } else if (type == HSBColorSlider::HSBType::B) {
        QString styleData = createStyleData(
            "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
            "stop:0 hsv(0, 0, 0), stop:1 hsv(0, 0, 255)); ");
        slider->setStyleSheet(styleData);
        connect(slider, &QSlider::valueChanged, this, [this, valueLabel](int value) {
            valueLabel->setText(QString("%1%").arg(QString::number(value).rightJustified(3, ' ')));
            emit sigColorChanged(getColor());
        });
        m_sliderB = slider;
    }
    hLayout->addWidget(slider);
    hLayout->addWidget(valueLabel);

    layout->addLayout(hLayout);
}

QString HSBColorSliderPicker::createStyleData(const QString &data)
{
    return QString("QSlider::groove:horizontal { %1"
        "height: 4px; margin:8px 8px;} QSlider::handle:horizontal {"
        "background: transparent; width: 10px; margin: -10px 0; }").arg(data);
}

void HSBColorSliderPicker::updateSaturationBG(int hue)
{
    QString styleSheet = createStyleData(QString(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "stop:0 hsv(%1, 0, 255), stop:1 hsv(%1, 255, 255));").arg(hue));
    m_sliderS->setStyleSheet(styleSheet);
    m_sliderS->update();
}
