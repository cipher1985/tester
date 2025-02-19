/*
 *  SPDX-FileCopyrightText: 2024 Wolthera van Hövell tot Westerflier <griffinvalley@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */
import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import org.krita.flake.text 1.0

TextPropertyBase {
    propertyName: i18nc("@title:group", "Text Decoration");
    propertyType: TextPropertyBase.Character;
    toolTip: i18nc("@info:tooltip",
                   "Text Decoration allows drawing underlines, overlines and striking through text.");
    searchTerms: i18nc("comma separated search terms for the text-decoration property, matching is case-insensitive",
                       "underline, overline, strikethrough, line-through");

    property alias underline: underlineCbx.checked;
    property alias overline: overlineCbx.checked;
    property alias linethrough: linethroughCbx.checked;
    property int lineStyle;
    property color lineColor;

    onPropertiesUpdated: {
        blockSignals = true;
        underline = properties.textDecorationUnderline;
        overline = properties.textDecorationOverline;
        linethrough = properties.textDecorationLineThrough;
        lineStyle = properties.textDecorationStyle;
        lineColor = properties.textDecorationColor;

        visible = properties.textDecorationLineState !== KoSvgTextPropertiesModel.PropertyUnset
        blockSignals = false;
    }

    onLineStyleChanged: {
        lineStyleCmb.currentIndex = lineStyleCmb.indexOfValue(lineStyle);
        if (!blockSignals) {
            properties.textDecorationStyle = lineStyle;
        }
    }

    onUnderlineChanged: {
        if (!blockSignals) {
            properties.textDecorationUnderline = underline;
        }
    }

    onOverlineChanged: {
        if (!blockSignals) {
            properties.textDecorationOverline = overline;
        }
    }

    onLinethroughChanged: {
        if (!blockSignals) {
            properties.textDecorationLineThrough = linethrough;
        }
    }

    onEnableProperty: {
        properties.textDecorationLineState = KoSvgTextPropertiesModel.PropertySet;
    }

    GridLayout {
        columns: 3;
        columnSpacing: columnSpacing;
        width: parent.width;

        RevertPropertyButton {
            revertState: properties.textDecorationLineState;
            inheritable: false;
            onClicked: properties.textDecorationLineState = KoSvgTextPropertiesModel.PropertyUnset;
        }

        Label {
            text: propertyName;
            Layout.columnSpan: 2;
            elide: Text.ElideRight;
            Layout.fillWidth: true;
            font.italic: properties.textDecorationLineState === KoSvgTextPropertiesModel.PropertyTriState;
        }


        Item {
            width: firstColumnWidth;
            height: 1;
        }
        Label {
            text: i18nc("@title:group", "Line:")
            Layout.columnSpan: 2;
        }

        Item {
            width: firstColumnWidth;
            height: 1;
        }
        CheckBox {
            Layout.columnSpan: 2;
            text: i18nc("@option:check", "Underline")
            id: underlineCbx;
        }
        Item {
            width: firstColumnWidth;
            height: 1;
        }
        CheckBox {
            Layout.columnSpan: 2;
            text: i18nc("@option:check", "Overline")
            id: overlineCbx;
        }
        Item {
            width: firstColumnWidth;
            height: 1;
        }
        CheckBox {
            Layout.columnSpan: 2;
            text: i18nc("@option:check", "Line-through")
            id: linethroughCbx;
        }


        Item {
            width: firstColumnWidth;
            height: 1;
        }

        CheckBox {
            text: i18nc("@label:chooser", "Color")
            id: colorCbx;
            enabled: false;
        }
        Rectangle {
            // replace with color picker?
            color: lineColor;
            Layout.fillWidth: true;
            Layout.fillHeight: true;
        }

        Item {
            width: firstColumnWidth;
            height: 1;
        }
        Label {
            text: i18nc("@label:listbox", "Style:")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter;
            elide: Text.ElideRight;
            Layout.fillWidth: true;
        }

        ComboBox {
            id: lineStyleCmb;
            model: [
                { text: i18nc("@label:inlistbox", "Solid"), value: KoSvgText.Solid},
                { text: i18nc("@label:inlistbox", "Dotted"), value: KoSvgText.Dotted},
                { text: i18nc("@label:inlistbox", "Dashed"), value: KoSvgText.Dashed},
                { text: i18nc("@label:inlistbox", "Double"), value: KoSvgText.Double},
                { text: i18nc("@label:inlistbox", "Wavy"), value: KoSvgText.Wavy},
            ]
            Layout.fillWidth: true;
            textRole: "text";
            valueRole: "value";
            onActivated: lineStyle = currentValue;
            wheelEnabled: true;
        }
    }
}
