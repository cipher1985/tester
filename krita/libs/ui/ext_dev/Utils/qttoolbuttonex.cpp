#include "qttoolbuttonex.h"

const QHash<QtToolButtonEx::ButtonState, QVector<QtToolButtonEx::ButtonState>>
    QtToolButtonEx::m_stateFallbackRules = {
        {QtToolButtonEx::BS_NoramlHover,    {QtToolButtonEx::BS_Noraml}},
        {QtToolButtonEx::BS_NormalPressed,  {QtToolButtonEx::BS_Noraml}},
        {QtToolButtonEx::BS_NoramlDisable,  {QtToolButtonEx::BS_Noraml}},
        {QtToolButtonEx::BS_CheckedHover,   {QtToolButtonEx::BS_Checked, QtToolButtonEx::BS_Noraml}},
        {QtToolButtonEx::BS_CheckedPressed, {QtToolButtonEx::BS_Checked, QtToolButtonEx::BS_Noraml}},
        {QtToolButtonEx::BS_CheckedDisable, {QtToolButtonEx::BS_Checked, QtToolButtonEx::BS_Noraml}}
};

QtToolButtonEx::QtToolButtonEx(QWidget *parent)
    : QToolButton{parent}
{}

void QtToolButtonEx::setText(const QString &text, ButtonState state)
{
    if(state >= BS_AllState)
        return;
    m_texts[state] = text;
    updateButtonState();
}

QString QtToolButtonEx::text(ButtonState state) const
{
    return findValidText(state);
}

void QtToolButtonEx::setIcon(const QIcon& icon, ButtonState state)
{
    if(state >= BS_AllState)
        return;
    m_icons[state] = icon;
    updateButtonState();
}

QIcon QtToolButtonEx::icon(ButtonState state) const
{
    return findValidIcon(state);
}

void QtToolButtonEx::setText(const QString &text)
{
    setText(text, BS_Noraml);
}

QString QtToolButtonEx::text() const
{
    return text(BS_Noraml);
}

void QtToolButtonEx::setIcon(const QIcon &icon)
{
    setIcon(icon, BS_Noraml);
}

QIcon QtToolButtonEx::icon() const
{
    return icon(BS_Noraml);
}

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
void QtToolButtonEx::enterEvent(QEnterEvent *e)
#else
void QtToolButtonEx::enterEvent(QEvent *e)
#endif
{
    updateButtonState();
    QToolButton::enterEvent(e);
}

void QtToolButtonEx::leaveEvent(QEvent *e)
{
    updateButtonState();
    QToolButton::leaveEvent(e);
}

void QtToolButtonEx::mousePressEvent(QMouseEvent *e)
{
    QToolButton::mousePressEvent(e);
    updateButtonState();
}

void QtToolButtonEx::mouseReleaseEvent(QMouseEvent *e)
{
    QToolButton::mouseReleaseEvent(e);
    updateButtonState();
}

void QtToolButtonEx::updateButtonState()
{
    const bool isChecked = this->isChecked();
    const bool isHover = underMouse();
    const bool isPressed = this->isDown();
    const bool isEnabled = this->isEnabled();

    // 状态判断逻辑
    if(!isEnabled){
        m_currentState = isChecked ? BS_CheckedDisable : BS_NoramlDisable;
    }else if(isPressed){
        m_currentState = isChecked ? BS_CheckedPressed : BS_NormalPressed;
    }else if(isHover){
        m_currentState = isChecked ? BS_CheckedHover : BS_NoramlHover;
    }else{
        m_currentState = isChecked ? BS_Checked : BS_Noraml;
    }

    QIcon finalIcon = findValidIcon(m_currentState);
    QString finalText = findValidText(m_currentState);

    blockSignals(true);
    QToolButton::setText(finalText);
    QToolButton::setIcon(finalIcon);
    blockSignals(false);
    update();
}

QIcon QtToolButtonEx::findValidIcon(ButtonState state) const
{
    if(!m_icons[state].isNull())
        return m_icons[state];

    if(m_stateFallbackRules.contains(state)){
        for(auto fallback : m_stateFallbackRules[state]){
            if(!m_icons[fallback].isNull())
                return m_icons[fallback];
        }
    }
    return QIcon();
}

QString QtToolButtonEx::findValidText(ButtonState state) const
{
    if(!m_texts[state].isEmpty())
        return m_texts[state];

    if(m_stateFallbackRules.contains(state)){
        for(auto fallback : m_stateFallbackRules[state]){
            if(!m_texts[fallback].isEmpty())
                return m_texts[fallback];
        }
    }
    return QString();
}
