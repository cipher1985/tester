/*
 *  SPDX-FileCopyrightText: 2010 Adam Celarek <kdedev at xibo dot at>
 *  SPDX-FileCopyrightText: 2022 Bourumir Wyngs <bourumir.wyngs@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "kis_color_history.h"
#include "kis_canvas2.h"
#include "KisViewManager.h"
#include "kis_canvas_resource_provider.h"

#include <KoCompositeOpRegistry.h>

#include <QToolButton>
#include <QList>
#include <kis_icon.h>
#include "KisDocument.h"
#include "kis_config_notifier.h"

Q_GLOBAL_STATIC(KisColorHistoryNotifier, s_color_history_change_notifier);

KisColorHistory::KisColorHistory(QWidget *parent)
    : KisColorPatches("lastUsedColors", parent)
    , m_document(0)
    , m_resourceProvider(0)
{
    m_clearButton = new QToolButton(this);
    m_clearButton->setIcon(KisIconUtils::loadIcon("dialog-cancel-16"));
    m_clearButton->setToolTip(i18n("Clear all color history"));
    m_clearButton->setAutoRaise(true);
    updateUserSettings();

    connect(m_clearButton, SIGNAL(clicked()), this, SLOT(clearColorHistory()));
    connect(KisConfigNotifier::instance(), SIGNAL(colorHistoryModeChanged()), this, SLOT(updateUserSettings()));
    connect(s_color_history_change_notifier, SIGNAL(colorHistoryChanged(const QList<KoColor>&)),
            this, SLOT(colorHistoryChanged(const QList<KoColor>&)));

    setAdditionalButtons({m_clearButton});
}

void KisColorHistory::unsetCanvas()
{
    m_resourceProvider = 0;
    m_document = 0;

    KisColorPatches::unsetCanvas();
}

void KisColorHistory::setCanvas(KisCanvas2 *canvas)
{
    if (!canvas) return;

    KisColorPatches::setCanvas(canvas);

    if (m_resourceProvider) {
        m_resourceProvider->disconnect(this);
    }

    m_resourceProvider = canvas->imageView()->resourceProvider();
    m_document = canvas->viewManager()->document();

    setColors(colorHistory());

    connect(m_resourceProvider, SIGNAL(sigFGColorUsed(KoColor)),
            this, SLOT(addColorToHistory(KoColor)), Qt::UniqueConnection);
}

KisColorSelectorBase *KisColorHistory::createPopup() const
{
    KisColorHistory *ret = new KisColorHistory();
    ret->setCanvas(m_canvas);
    ret->setColors(colors());
    return ret;
}

void KisColorHistory::addColorToHistory(const KoColor &color)
{
    // don't add color in erase mode. See https://bugs.kde.org/show_bug.cgi?id=298940
    if (m_resourceProvider && m_resourceProvider->currentCompositeOp() == COMPOSITE_ERASE) return;

    KisColorPatches::addColorPatch(color);

    updateColorHistory(colors());
    s_color_history_change_notifier->notifyColorHistoryChanged(colors());
}

void KisColorHistory::clearColorHistory()
{
    QList<KoColor> empty;
    updateColorHistory(empty);
    s_color_history_change_notifier->notifyColorHistoryChanged(empty);
}

QList<KoColor> KisColorHistory::colorHistory()
{
    if (m_history_per_document && m_document) {
        return m_document->colorHistory();
    } else if (m_resourceProvider) {
        return m_resourceProvider->colorHistory();
    } else {
        return QList<KoColor>();
    }
}

void KisColorHistory::updateColorHistory(const QList<KoColor> &history)
{
    if (m_history_per_document && m_document) {
        m_document->setColorHistory(history);
    }

    /**
     * Resource provider saves the history all the time, whatever the
     * option state is.
     */
    if (m_resourceProvider) {
        m_resourceProvider->setColorHistory(history);
    }

    setColors(history);
}

void KisColorHistory::updateUserSettings()
{

    KisConfig config(true);
    m_history_per_document = config.colorHistoryPerDocument();
    updateColorHistory(colorHistory()); // Show with respect to the current strategy
}

void KisColorHistory::colorHistoryChanged(const QList<KoColor> &history)
{
    KIS_SAFE_ASSERT_RECOVER_RETURN(sender() != this);

    if (m_resourceProvider) {
        m_resourceProvider->setColorHistory(history);
    }
    setColors(history);
}

void KisColorHistoryNotifier::notifyColorHistoryChanged(const QList<KoColor> &history)
{
    Q_EMIT colorHistoryChanged(history);
}
