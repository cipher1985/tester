#include "hsbcolorringpicker.h"
#include <QMouseEvent>
#include <QPainterPath>
#include <QPainter>
#include <QtMath>
HSBColorRingPicker::HSBColorRingPicker(QWidget *parent) : QWidget(parent)
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    setMinimumSize(150, 150);
}

void HSBColorRingPicker::setColor(const QColor &color)
{
    m_hue = color.hsvHueF() * 360;
    m_saturation = color.saturationF();
    m_bright = color.valueF();
    createBSImage(m_radius, m_hue);
    update();
}

void HSBColorRingPicker::setHSB(int hue, int saturation, int bright)
{
    m_hue = hue;
    m_saturation = saturation / 100.0f;
    m_bright = bright / 100.0f;
    createBSImage(m_radius, m_hue);
    update();
}

QColor HSBColorRingPicker::getColor()
{
    return QColor::fromHsvF(m_hue / 359.0f, m_saturation, m_bright);
}

void HSBColorRingPicker::createHueRing(int r, int width)
{
    int R = (r << 1);
    m_imgHue = QImage(R, R, QImage::Format_ARGB32);
    m_imgHue.fill(Qt::transparent);
    QPainter painter(&m_imgHue);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    int centerX = r;
    int centerY = r;
    int outerRadius = r;
    int innerRadius = r - width;
    QPainterPath path;
    // 添加外圆
    path.addEllipse(QPointF(centerX,centerY), outerRadius, outerRadius);
    // 减去内圆，形成圆环
    QPainterPath innerPath;
    innerPath.addEllipse(QPointF(centerX,centerY), innerRadius, innerRadius);
    path -= innerPath;
    //生成hue径向渐变色
    QConicalGradient gradient(centerX, centerY, 0);
    for (int i = 0; i < 360; ++i) {
        QColor color;
        color.setHsvF(i / 360.0, 1.0, 1.0);
        gradient.setColorAt(i / 360.0, color);
    }
    //绘制圆环
    painter.fillPath(path, gradient);
    painter.drawPath(path);
}

void HSBColorRingPicker::createBSImage(int r, int hue)
{
    int R = qMax(2, r << 1);
    m_imgBS = QImage(R, R, QImage::Format_ARGB32);
    float h = hue / 359.0f;
    // 生成每个像素的颜色
    for (int y = 0; y < R; ++y) {
        for (int x = 0; x < R; ++x) {
            // 计算S和B的值（S随x增加，B随y减少）
            float s = x / float(R - 1);
            float b = 1.0f - y / float(R - 1);
            // 创建颜色并设置到像素
            QColor color;
            color.setHsvF(h, s, b);
            m_imgBS.setPixelColor(x, y, color);
        }
    }
}

void HSBColorRingPicker::processIndicator(QPoint pos)
{
    QPointF center = rect().center();
    QPointF offset = pos - center;
    float distance = std::hypot(offset.x(), offset.y());
    // 判断点击区域
    if(m_clickState == CS_None) {
        int R = (m_radius << 1);
        if(R >= distance && distance >= (R - (m_hueRadius << 1)))
            m_clickState = CS_Hue;
        else if(distance <= m_radius)
            m_clickState = CS_BS;
    }

    // 更新颜色值
    if(m_clickState == CS_Hue) {
        float angle = std::atan2(-offset.y(), offset.x()) * 180 / M_PI;
        m_hue = (angle < 0) ? angle + 360 : angle;
        createBSImage(m_radius, m_hue);
    }
    else if(m_clickState == CS_BS) {
        m_saturation = qBound(0.0f, (float)((offset.x()+m_radius)/(2*m_radius)), 1.0f);
        m_bright = qBound(0.0f, (float)(1.0 - (offset.y()+m_radius)/(2*m_radius)), 1.0f);
    }

    update();
    QColor color = getColor();
    emit sigColorChanged(color);
}

void HSBColorRingPicker::updateSize()
{
    m_center = rect().center();
    //内圆半径
    m_radius = (qMin(width(), height()) - m_border) / 4;
    //选择bs值圆半径
    m_bsRadius = m_radius / 5;
    //选择hue值圆半径
    m_hueRadius = (m_radius << 1) / 5;
    //创建hue环
    createHueRing((m_radius << 1), (m_hueRadius << 1));
    //创建bs图像
    createBSImage(m_radius, m_hue);
}

void HSBColorRingPicker::drawBsCircle(QPainter *p)
{
    // 创建圆形遮罩
    QPointF offset(m_center.x() - m_radius,
        m_center.y() - m_radius);
    p->translate(offset.x(), offset.y());
    QPainterPath path;
    path.addEllipse(QRectF(0, 0, m_imgBS.width(), m_imgBS.height()));
    p->setClipPath(path);
    //绘制BS图像
    p->setPen(Qt::NoPen);
    p->drawImage(0, 0, m_imgBS);
    p->resetTransform();
    p->setClipRect(this->rect());
}

void HSBColorRingPicker::drawBsIndicator(QPainter *p)
{
    //绘制BS选中指示器
    float r = m_radius; // BS圆的实际半径
    // 将s/b转换为笛卡尔坐标（考虑圆边界约束）
    float x = (m_saturation * 2 - 1) * r; // [-r, r]
    float y = ((1 - m_bright) * 2 - 1) * r;
    float distance = std::hypot(x, y);
    // 超出圆时投影到边缘
    if (distance > r) {
        x *= r / distance;
        y *= r / distance;
    }
    QPointF bsPos(m_center.x() + x, m_center.y() + y);
    QColor bsColor = QColor::fromHsvF(m_hue / 359.0f, m_saturation, m_bright);
    p->setPen(QPen(QColor(255, 255, 255, 200), m_selectBorder));
    p->setBrush(bsColor);
    p->drawEllipse(bsPos, m_bsRadius - m_selectBorder, m_bsRadius - m_selectBorder);
}

void HSBColorRingPicker::drawHueRing(QPainter *p)
{
    //绘制Hue圆环
    QPointF offset(m_center.x() - m_imgHue.width() / 2.0f,
        m_center.y() - m_imgHue.height() / 2.0f);
    p->translate(offset.x(), offset.y());
    p->drawImage(0, 0, m_imgHue);
    p->resetTransform();
}

void HSBColorRingPicker::drawHueSelect(QPainter *p)
{
    //绘制Hue选中指示器
    const float outerRadius = (m_radius << 1); // Hue环外半径
    const float middleRadius = outerRadius - m_hueRadius; // 环中心线半径
    //计算色相标记点坐标（考虑Qt坐标系Y轴向下）
    qreal angle = qDegreesToRadians((float)m_hue);
    float hueX = m_center.x() + middleRadius * std::cos(angle);
    float hueY = m_center.y() - middleRadius * std::sin(angle); // Y轴取反
    //绘制指示器颜色
    QColor hueColor = QColor::fromHsv(m_hue, 255, 255);
    p->setPen(QPen(QColor(255, 255, 255, 200), m_selectBorder));
    p->setBrush(hueColor);
    p->drawEllipse(QPointF(hueX, hueY),
        m_hueRadius - m_selectBorder, m_hueRadius - m_selectBorder);
}

void HSBColorRingPicker::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing);

    drawBsCircle(&painter);
    drawBsIndicator(&painter);

    drawHueRing(&painter);
    drawHueSelect(&painter);
}

void HSBColorRingPicker::resizeEvent(QResizeEvent *)
{
    updateSize();
}

void HSBColorRingPicker::mousePressEvent(QMouseEvent *event)
{
    processIndicator(event->pos());
}

void HSBColorRingPicker::mouseMoveEvent(QMouseEvent *event)
{
    processIndicator(event->pos());
}

void HSBColorRingPicker::mouseReleaseEvent(QMouseEvent *)
{
    m_clickState = CS_None;
}
