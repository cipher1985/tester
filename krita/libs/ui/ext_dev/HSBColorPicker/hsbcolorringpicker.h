#ifndef HSBCOLORRINGPICKER_H
#define HSBCOLORRINGPICKER_H

#include <QWidget>

class HSBColorRingPicker : public QWidget
{
    Q_OBJECT
public:
    HSBColorRingPicker(QWidget* parent = nullptr);
    //设置颜色
    void setColor(const QColor& color);
    //设置颜色(hue:0-359,saturation:0-100%,bright:0-100%)
    void setHSB(int hue, int saturation, int bright);
    //获得颜色
    QColor getColor();
Q_SIGNALS:
    //获得颜色
    void sigColorChanged(const QColor& color);
private:
    //生成Hue环(环半径，环宽度)
    void createHueRing(int r, int width);
    //生成bs矩形图
    void createBSImage(int r, int hue);
    //点击状态
    enum ClickState {
        CS_None,
        CS_Hue,
        CS_BS
    };
    ClickState m_clickState = CS_None;
    //处理选择器
    void processIndicator(QPoint pos);
    //更新尺寸重新创建图像
    void updateSize();
    //绘制bs选择区域圆
    void drawBsCircle(QPainter* p);
    //绘制bs指示器
    void drawBsIndicator(QPainter* p);
    //绘制hue选择区域环
    void drawHueRing(QPainter* p);
    //绘制hue指示器
    void drawHueSelect(QPainter* p);
private:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
private:
    //色域范围(0-360)
    int m_hue = 0;
    //饱合度范围(0-1)
    float m_saturation = 0.5f;
    //亮度范围(0-1)
    float m_bright = 0.5f;

    //bs选择器半径
    float m_bsRadius;
    //hue选择器半径
    int m_hueRadius;
    //中心点
    QPointF m_center;
    //内圆半径
    int m_radius = 0;
    //距边缘位置
    int m_border = 10;
    //选择器边缘大小
    int m_selectBorder = 2;

    //生成hue环图像
    QImage m_imgHue;
    //生成的bs形状图像
    QImage m_imgBS;
};





#endif // HSBCOLORRINGPICKER_H
