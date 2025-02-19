/*
 *  SPDX-FileCopyrightText: 2024 Wolthera van Hövell tot Westerflier <griffinvalley@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */
import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12

TextPropertyBase {
    propertyType: TextPropertyBase.Paragraph;
    GridLayout {
        columns: 2;
        columnSpacing: columnSpacing;
        width: parent.width;

        Item {
            width: firstColumnWidth;
            height: firstColumnWidth;
            ToolButton {
                id: revert;
                icon.width: 22;
                icon.height: 22;
                display: AbstractButton.IconOnly
                icon.source: "qrc:///light_view-refresh.svg"
            }
        }

        Label {
            text:  i18nc("@label:listbox", "Underline Position:")
        }


        Item {
            width: firstColumnWidth;
            height: 1;
        }
        ComboBox {
            model: [
                i18nc("@label:inlistbox", "Vertical Left"),
                i18nc("@label:inlistbox", "Vertical Right")
            ]
            Layout.fillWidth: true;
            id: verticalPositionCmb;
        }

        Item {
            width: firstColumnWidth;
            height: 1;
        }
        CheckBox {
            text:  i18nc("@option:check", "Horizontal Auto");
        }
    }
}
