#include "selectcolorwidget.h"

#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Utils/qttools.h"
#include "Utils/qttoolbuttonex.h"

#include "extglobal.h"
#include "hsbcolorpicker.h"
SelectColorWidget::SelectColorWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(248, 498);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 16, 8, 8);

    QLabel* title = new QLabel(u8"调色板");
    title->setStyleSheet(
        "QLabel{background:transparent;"
        "font-family: PingFang SC, PingFang SC;"
        "font-weight: 500; font-size: 18px; "
        "color: #FFFFFF; line-height: 22px;}"
        "QToolButton{background:transparent;}");
    QHBoxLayout* titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(0, 0, 0, 0);
    title->setLayout(titleLayout);
    QtToolButtonEx* bnConfig = new QtToolButtonEx;
    bnConfig->setFixedSize(24, 24);
    bnConfig->setToolButtonStyle(Qt::ToolButtonIconOnly);
    bnConfig->setIconSize(QSize(24, 24));
    bnConfig->setIcon(QIcon(EXT_GLOBAL().getResFile("color_config_0.png")));
    bnConfig->setIcon(QIcon(EXT_GLOBAL().getResFile("color_config_1.png")), QtToolButtonEx::BS_NoramlHover);

    titleLayout->addWidget(bnConfig, 0, Qt::AlignRight | Qt::AlignVCenter);

    layout->addWidget(title);

    HSBColorPicker* colorPicker = new HSBColorPicker;
    colorPicker->setFixedHeight(480);
    layout->addWidget(colorPicker);

    layout->addStretch();
}

void SelectColorWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path = QtTools::CreateBubblePath(
        this->width(), this->height() - 8, 8,
        QtTools::PopArrowDir::Top, 228, 8, 220, 236);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(36, 36, 36, 230));
    p.drawPath(path);
}
