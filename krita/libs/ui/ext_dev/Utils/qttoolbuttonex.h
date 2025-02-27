#ifndef QTTOOLBUTTONEX_H
#define QTTOOLBUTTONEX_H

#include <QObject>
#include <QHash>
#include <QVector>
#include <QToolButton>
class QtToolButtonEx : public QToolButton
{
    Q_OBJECT
public:
    enum ButtonState
    {
        BS_Noraml = 0,
        BS_NoramlHover,
        BS_NormalPressed,
        BS_NoramlDisable,
        BS_Checked,
        BS_CheckedHover,
        BS_CheckedPressed,
        BS_CheckedDisable,
        BS_AllState
    };
    explicit QtToolButtonEx(QWidget *parent = nullptr);

    void setText(const QString& text, ButtonState state);
    QString text(ButtonState state) const;
    void setIcon(const QIcon& icon, ButtonState state);
    QIcon icon(ButtonState state) const;

    //替换方法
    void setText(const QString &text);
    QString text() const;
    void setIcon(const QIcon &icon);
    QIcon icon() const;
protected:
    //绑定事件
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    void enterEvent(QEnterEvent* e) override;
#else
    void enterEvent(QEvent* e) override;
#endif
    void leaveEvent(QEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
private:
    //更新状态
    void updateButtonState();
    //回退查找
    QIcon findValidIcon(ButtonState state) const;
    QString findValidText(ButtonState state) const;
private:
    QIcon m_icons[BS_AllState];
    QString m_texts[BS_AllState];
    ButtonState m_currentState = BS_Noraml;
    // 状态映射规则
    static const QHash<ButtonState, QVector<ButtonState>> m_stateFallbackRules;
};

#endif // QTTOOLBUTTONEX_H
