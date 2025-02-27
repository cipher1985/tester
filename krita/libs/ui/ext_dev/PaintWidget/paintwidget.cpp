#include "paintwidget.h"
#include "ui_paintwidget.h"
#include <QPushButton>

//#include "Utils/qttoolbuttonex.h"
#include "extglobal.h"
#include "lefttool.h"

#include "HSBColorPicker/selectcolorwidget.h"
PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PaintWidget)
{
    ui->setupUi(this);

    ui->toolButton_gallery->setIcon(QIcon(EXT_GLOBAL().getResFile("return_0.png")));
    ui->toolButton_gallery->setIcon(QIcon(EXT_GLOBAL().getResFile("return_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_option->setIcon(QIcon(EXT_GLOBAL().getResFile("option_0.png")));
    ui->toolButton_option->setIcon(QIcon(EXT_GLOBAL().getResFile("option_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_modify->setIcon(QIcon(EXT_GLOBAL().getResFile("modify_0.png")));
    ui->toolButton_modify->setIcon(QIcon(EXT_GLOBAL().getResFile("modify_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_cursor->setIcon(QIcon(EXT_GLOBAL().getResFile("cursor_0.png")));
    ui->toolButton_cursor->setIcon(QIcon(EXT_GLOBAL().getResFile("cursor_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_select->setIcon(QIcon(EXT_GLOBAL().getResFile("select_0.png")));
    ui->toolButton_select->setIcon(QIcon(EXT_GLOBAL().getResFile("select_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_translate->setIcon(QIcon(EXT_GLOBAL().getResFile("translate_0.png")));
    ui->toolButton_translate->setIcon(QIcon(EXT_GLOBAL().getResFile("translate_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_share->setIcon(QIcon(EXT_GLOBAL().getResFile("share_0.png")));
    ui->toolButton_share->setIcon(QIcon(EXT_GLOBAL().getResFile("share_1.png")), QtToolButtonEx::BS_NoramlHover);


    ui->toolButton_shape->setIcon(QIcon(EXT_GLOBAL().getResFile("shape_0.png")));
    ui->toolButton_shape->setIcon(QIcon(EXT_GLOBAL().getResFile("shape_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_paint->setIcon(QIcon(EXT_GLOBAL().getResFile("paint_0.png")));
    ui->toolButton_paint->setIcon(QIcon(EXT_GLOBAL().getResFile("paint_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_brush->setIcon(QIcon(EXT_GLOBAL().getResFile("brush_0.png")));
    ui->toolButton_brush->setIcon(QIcon(EXT_GLOBAL().getResFile("brush_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_layer->setIcon(QIcon(EXT_GLOBAL().getResFile("layer_0.png")));
    ui->toolButton_layer->setIcon(QIcon(EXT_GLOBAL().getResFile("layer_1.png")), QtToolButtonEx::BS_NoramlHover);

    ui->toolButton_color->setIcon(QIcon(EXT_GLOBAL().getResFile("color.png")));

    //左边栏
    m_leftTool = new LeftTool(ui->main_frame);
    ui->main_frame->setMinimumHeight(m_leftTool->height() + 32);
    m_leftTool->move(0, ((ui->main_frame->height() - m_leftTool->height()) >> 1));
}

PaintWidget::~PaintWidget()
{
    delete ui;
}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    m_leftTool->move(0, ((ui->main_frame->height() - m_leftTool->height()) >> 1));
}

void PaintWidget::on_toolButton_gallery_clicked()
{
    EXT_GLOBAL().showGallery();
}


void PaintWidget::on_toolButton_color_clicked()
{
    SelectColorWidget* color = new SelectColorWidget;
    QPoint pt = ui->widget_painter_title->mapToGlobal(
        QPoint(ui->toolButton_color->x() - 228
            + ui->toolButton_color->width() / 2,
        ui->widget_painter_title->height()));
    color->move(pt);
    color->show();
}

