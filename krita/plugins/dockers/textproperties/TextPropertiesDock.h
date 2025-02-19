/*
 *  SPDX-FileCopyrightText: 2024 Wolthera van Hövell tot Westerflier <griffinvalley@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef TEXTPROPERTIESDOCK_H
#define TEXTPROPERTIESDOCK_H

#include <QDockWidget>
#include <QIcon>
#include <kis_mainwindow_observer.h>
#include <QPointer>

#include <kis_canvas2.h>

class KoDialog;
class QQuickWidget;

class TextPropertiesDock : public QDockWidget, public KisMainwindowObserver {
    Q_OBJECT
public:
    TextPropertiesDock();
    ~TextPropertiesDock();
    QString observerName() override { return "TextPropertiesDock"; }
    void setViewManager(KisViewManager *kisview) override;
    void setCanvas(KoCanvasBase *canvas) override;
    void unsetCanvas() override;



public Q_SLOTS:
    void slotCanvasTextPropertiesChanged();
    void slotTextPropertiesChanged();
    void connectAutoEnabler(QObject *watched);

private:
    QPointer<KisCanvas2> m_canvas;
    QQuickWidget *m_quickWidget {0};

    struct Private;
    const QScopedPointer<Private> d;
};

#endif // TEXTPROPERTIESDOCK_H
