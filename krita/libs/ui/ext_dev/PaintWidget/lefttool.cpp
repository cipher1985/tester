#include "lefttool.h"
#include "ui_lefttool.h"

#include <QPainter>

#include "extglobal.h"
LeftTool::LeftTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftTool)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    ui->verticalSlider_brush->setFixedSize(28, 152);
    ui->verticalSlider_alpha->setFixedSize(28, 152);

    ui->toolButton_picker->setIcon(QIcon(EXT_GLOBAL().getResFile("picker_0.png")));
    ui->toolButton_picker->setIcon(QIcon(EXT_GLOBAL().getResFile("picker_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_undo->setIcon(QIcon(EXT_GLOBAL().getResFile("undo_0.png")));
    ui->toolButton_undo->setIcon(QIcon(EXT_GLOBAL().getResFile("undo_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_redo->setIcon(QIcon(EXT_GLOBAL().getResFile("redo_0.png")));
    ui->toolButton_redo->setIcon(QIcon(EXT_GLOBAL().getResFile("redo_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->verticalSlider_brush->setRange(10, 100);
    ui->verticalSlider_brush->setValue(50);
    ui->verticalSlider_alpha->setRange(0, 100);
    ui->verticalSlider_alpha->setValue(100);
    ui->frame_brush_size->hide();
    ui->frame_brush_alpha->hide();

}

LeftTool::~LeftTool()
{
    delete ui;
}

void LeftTool::on_verticalSlider_brush_sliderPressed()
{
    ui->frame_brush_size->show();
}


void LeftTool::on_verticalSlider_brush_sliderReleased()
{
    ui->frame_brush_size->hide();

}


void LeftTool::on_verticalSlider_brush_valueChanged(int value)
{
    ui->label_brush_size_text->setText(QString(u8"尺寸(%1%)").arg(value));
    int R = qMin(ui->label_brush_size_show->width(), ui->label_brush_size_show->height()) * value / 100;
    QPixmap pixmap(R, R);
    pixmap.fill(Qt::transparent);
    QPainter p(&pixmap);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::white);
    p.drawEllipse(0, 0, R, R);
    p.end();
    ui->label_brush_size_show->setPixmap(pixmap);
}


void LeftTool::on_verticalSlider_alpha_sliderPressed()
{
    ui->frame_brush_alpha->show();
}


void LeftTool::on_verticalSlider_alpha_sliderReleased()
{
    ui->frame_brush_alpha->hide();
}


void LeftTool::on_verticalSlider_alpha_valueChanged(int value)
{
    ui->label_brush_alpha_text->setText(QString(u8"不透明度(%1%)").arg(value));
    //ui->label_brush_alpha_show->setPixmap();
    int R = 50;
    float alpha = value / 100.0f;
    QPixmap pixmap(R, R);
    pixmap.fill(Qt::transparent);
    QPainter p(&pixmap);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    QColor color = Qt::white;
    color.setAlphaF(alpha);
    p.setBrush(color);
    p.drawEllipse(0, 0, R, R);
    p.end();
    ui->label_brush_alpha_show->setPixmap(pixmap);
}

