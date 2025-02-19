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
    propertyName: i18nc("@label:listbox", "Dominant Baseline")
    propertyType: TextPropertyBase.Paragraph;
    toolTip: i18nc("@info:tooltip",
                   "Dominant Baseline specifies how stretches of text of different sizes are aligned, it is also the default for Alignment Baseline.");
    searchTerms: i18nc("comma separated search terms for the dominant-baseline property, matching is case-insensitive",
                       "dominant-baseline, mojisoroe");
    property int baselineSelection

    onPropertiesUpdated: {
        blockSignals = true;
        baselineSelection = properties.dominantBaseline;
        visible = properties.dominantBaselineState !== KoSvgTextPropertiesModel.PropertyUnset;
        blockSignals = false;
    }

    onBaselineSelectionChanged: {
        baselineCmb.currentIndex = baselineCmb.indexOfValue(baselineSelection);
        if (!blockSignals) {
            properties.dominantBaseline = baselineSelection;
        }
    }

    onEnableProperty: properties.dominantBaselineState = KoSvgTextPropertiesModel.PropertySet;

    GridLayout {
        columns: 2;
        columnSpacing: columnSpacing;
        width: parent.width;

        RevertPropertyButton {
            revertState: properties.dominantBaselineState;
            onClicked: properties.dominantBaselineState = KoSvgTextPropertiesModel.PropertyUnset;
        }

        Label {
            text: propertyName;
            elide: Text.ElideRight;
            Layout.fillWidth: true;
            font.italic: properties.dominantBaselineState === KoSvgTextPropertiesModel.PropertyTriState;
        }


        Item {
            width: firstColumnWidth;
            height: 1;
        }
        ComboBox {
            model: [
                {text: i18nc("@label:inlistbox", "Baseline"), value: KoSvgText.BaselineAuto},
                {text: i18nc("@label:inlistbox", "Alphabetic"), value: KoSvgText.BaselineAlphabetic},
                {text: i18nc("@label:inlistbox", "Ideographic"), value: KoSvgText.BaselineIdeographic},
                {text: i18nc("@label:inlistbox", "Central"), value: KoSvgText.BaselineCentral},
                {text: i18nc("@label:inlistbox", "Hanging"), value: KoSvgText.BaselineHanging},
                {text: i18nc("@label:inlistbox", "Middle"), value: KoSvgText.BaselineMiddle},
                {text: i18nc("@label:inlistbox", "Mathematical"), value: KoSvgText.BaselineMathematical},
                {text: i18nc("@label:inlistbox", "Text-Top"), value: KoSvgText.BaselineTextTop},
                {text: i18nc("@label:inlistbox", "Text-Bottom"), value: KoSvgText.BaselineTextBottom}
            ]
            Layout.fillWidth: true;
            id: baselineCmb;
            textRole: "text";
            valueRole: "value";
            onActivated: baselineSelection = currentValue;
            wheelEnabled: true;
        }
    }
}
