import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2


Item {

    property alias calendar: calendar
    implicitWidth: column.width
    implicitHeight: row.height

    RowLayout {
        id: row
        width: parent.width

        TextField {
            width: 300
            text: Qt.formatDate(calendar.selectedDate, "dd-MM-yyyy")
            enabled: true
            inputMask: "99-99-9999"
            Layout.fillWidth: true

            anchors.verticalCenter: parent.verticalCenter
            onEditingFinished: {

                var newDate = new Date();
                calendar.selectedDate = newDate;
                /*newDate.setFullYear(text.substr(6, 4));
                newDate.setDate(text.substr(0, 2));
                newDate.setMonth(text.substr(3, 2) - 1);
               */


                //formatDate(calendar.selectedDate,"YYYY-MM-DDThh:mm:ss.zzzZ")



            }

        }

        Image {
            id: button
            source: "Icons/icon-calendar.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -1

            MouseArea {
                anchors.fill: parent
                onClicked: calendar.visible = true
            }
        }
    }

    Calendar {
        id: calendar
        //parent: parent.contentItem
        visible: false

        width: parent.width * 0.8
        height: width
        anchors.centerIn: parent

        focus: visible
        onClicked: {visible = false
        console.log(selectedDate)
        }
        Keys.onBackPressed: {
            event.accepted = true;
            visible = false;
            console.log(selectedDate)
        }
    }

}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
