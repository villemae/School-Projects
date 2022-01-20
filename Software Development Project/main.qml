import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.13
import QtCharts 2.12


Window {
    id: window
    visible: true
    width: 1096
    height: 720
    title: qsTr("Monitor")


    Column {
        id: column
        x: 0
        width: 300
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        transformOrigin: Item.Center
        Rectangle{
            anchors.fill: column
            color: "darkmagenta"
        }
        SideBar{
            id: sidebar
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Column {
               width: 300
               anchors.horizontalCenter: sidebar.horizontalCenter
               anchors.verticalCenter: sidebar.verticalCenter
               spacing: 50
                Column {
                    //spacing: 5

                    Label {
                        x: 10
                        text: "From"
                        style: Text.Sunken
                        color: "white"
                    }
                    DateSelection{
                        id:fromDate
                        x: 10
                        width: 275
                        visible: true
                    }
                }

                Column {
                    spacing: 5

                    Label {
                        x: 10
                        text: "To"
                        style: Text.Sunken
                        color: "white"
                    }
                    DateSelection{
                        id:toDate
                        x: 10
                        width: 275
                    }
                }
            }
        }
    }

    GraphWindow{
        id: graphWindow
        y: window.height / 6
        width:window.width - column.width - 45
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: column.right
        anchors.leftMargin: 25
        height: window.height / 1.25

        ButtonRow{
            id: buttonRow
            anchors.top: graphWindow.top
            anchors.left: graphWindow.left
            width: graphWindow.width
            anchors.leftMargin: 5
            anchors.topMargin: -43

        }

    }

}






