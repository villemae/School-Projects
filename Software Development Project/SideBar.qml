import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.13
import QtQuick.Controls.Styles 1.1

import QtCharts 2.12

Item {
    id: getAName
    width: 300
    anchors.top: parent.top


    ComboBox {
        id: placesComboBox
        x: 10
        y: 59
        width: 148
        height: 32
        displayText: currentText


        model: ListModel {
            id: model
            ListElement { text: "Helsinki" }
            ListElement { text: "Pirkkala" }
            ListElement { text: "Turku" }
            ListElement { text: "Lahti" }
            ListElement { text: "Jyväskylä" }
            ListElement { text: "Oulu" }
            ListElement { text: "Kemi" }
            ListElement { text: "Rovaniemi" }
            ListElement { text: "Kittilä" }
        }

        onActivated:  {
           /* onActivated: console.log("I clicked item with index "
                                     + index + " which has label "
                                     + model.get(currentIndex).text)*/


            // direct the chosen city to control
            control.setCity(model.get(currentIndex).text);
        }
    }

    MenuBar {
        Menu {
               title: qsTr("&File")
               Action { text: qsTr("&New...") }
               Action { text: qsTr("&Open...") }
               Action { text: qsTr("&Save")
                   shortcut: StandardKey.Save

                    }
               Action { text: qsTr("Save &As...")
                    shortcut: StandardKey.SaveAs

               }
               MenuSeparator { }
               Action { text: qsTr("&Quit")
               shortcut: StandardKey.Quit
               onTriggered: Qt.quit()
               }
           }

           Menu {
               title: qsTr("&Help")
               Action { text: qsTr("&About") }
           }
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
