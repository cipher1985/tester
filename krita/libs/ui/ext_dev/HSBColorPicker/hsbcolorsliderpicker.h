#ifndef HSBCOLORSLIDERPICKER_H
#define HSBCOLORSLIDERPICKER_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>

// 滑动条滑块实时显示当前颜色
class HSBColorSlider : public QSlider {
    Q_OBJECT
public:
    enum class HSBType
    { H = 0, S, B };
    HSBColorSlider(HSBType type,
        Qt::Orientation orientation = Qt::Horizontal,
        QWidget *parent = nullptr);
    void setHueSlider(HSBColorSlider* hSlider);
private:
    HSBType m_type;
    //Saturation滑动条关联hue对象
    HSBColorSlider* m_hSlider{};
    void paintEvent(QPaintEvent *event) override;
};

// 颜色HSB滑动条设置类
class HSBColorSliderPicker : public QWidget {
    Q_OBJECT
public:
    HSBColorSliderPicker(QWidget *parent = nullptr);
    //设置HSB
    void setHue(int hue);
    void setSaturation(int saturation);
    void setBright(int bright);
    //设置颜色
    void setColor(const QColor &color);
    //获得设置颜色
    QColor getColor() const;
Q_SIGNALS:
    void sigColorChanged(const QColor &color);
private:
    void paintEvent(QPaintEvent *event) override;
    //创建滑动条
    void createSlider(QVBoxLayout* layout,
        HSBColorSlider::HSBType type,
        const QString& label, int min, int max);
    //生成样式
    QString createStyleData(const QString& data);
    //更新饱合度滑动条背景图像
    void updateSaturationBG(int hue);
    HSBColorSlider *m_sliderH;
    HSBColorSlider *m_sliderS;
    HSBColorSlider *m_sliderB;
};


#endif // HSBCOLORSLIDERPICKER_H
