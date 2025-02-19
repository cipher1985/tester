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
    propertyName: i18nc("@label:listbox", "Alignment Baseline");
    propertyType: TextPropertyBase.Character;
    toolTip: i18nc("@info:tooltip",
                   "Alignment Baseline allows controling how this range of text is aligned to the parent text.");
    searchTerms: i18nc("comma separated search terms for the alignment-baseline property, matching is case-insensitive",
                       "alignment-baseline, mojisoroe");
    property int baselineSelection;

    onPropertiesUpdated: {
        blockSignals = true;
        baselineSelection = properties.alignmentBaseline;
        visible = properties.alignmentBaselineState !== KoSvgTextPropertiesModel.PropertyUnset
        blockSignals = false;
    }

    onBaselineSelectionChanged: {
        baselineCmb.currentIndex = baselineCmb.indexOfValue(baselineSelection);
        if (!blockSignals) {
            properties.alignmentBaseline = baselineSelection;
        }
    }

    onEnableProperty: properties.alignmentBaselineState = KoSvgTextPropertiesModel.PropertySet;

    GridLayout {
        columns: 2;
        columnSpacing: columnSpacing;
        width: parent.width;

        RevertPropertyButton {
            revertState: properties.alignmentBaselineState;
            onClicked: properties.alignmentBaselineState = KoSvgTextPropertiesModel.PropertyUnset;
        }

        Label {
            text: propertyName;
            elide: Text.ElideRight;
            Layout.fillWidth: true;
            font.italic: properties.alignmentBaselineState === KoSvgTextPropertiesModel.PropertyTriState;
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
