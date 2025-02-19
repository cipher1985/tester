/*
 *  SPDX-FileCopyrightText: 2024 Wolthera van Hövell tot Westerflier <griffinvalley@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */
import QtQuick 2.15
import QtQuick.Controls 2.0
import org.krita.flake.text 1.0

Item {
    width: firstColumnWidth;
    height: firstColumnWidth;

    property int revertState: 0;
    property bool inheritable: true;
    signal clicked;



    ToolButton {
        property string tristateText: i18nc("@info:tooltip", "Revert property. Within the current selection, this property has different values.")
        property string setText: i18nc("@info:tooltip", "Revert property.");
        id: revert;
        icon.width: 22;
        icon.height: 22;
        icon.color: sysPalette.text;
        enabled: revertState !== KoSvgTextPropertiesModel.PropertyUnset && revertState !== KoSvgTextPropertiesModel.PropertyInherited;
        opacity: enabled? 1.0: 0.3;
        display: AbstractButton.IconOnly;
        icon.source: revertState === KoSvgTextPropertiesModel.PropertyTriState? "qrc:///light_edit-undo-tristate.svg": "qrc:///light_edit-undo.svg";
        onClicked: parent.clicked();

        ToolTip.text: revertState === KoSvgTextPropertiesModel.PropertyTriState? tristateText: setText;
        ToolTip.delay: Qt.styleHints.mousePressAndHoldInterval;
        ToolTip.visible: hovered;
    }
}
