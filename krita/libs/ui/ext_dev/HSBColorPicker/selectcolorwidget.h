#ifndef SELECTCOLORWIDGET_H
#define SELECTCOLORWIDGET_H

#include <QWidget>

class SelectColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectColorWidget(QWidget *parent = nullptr);
private:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // SELECTCOLORWIDGET_H
