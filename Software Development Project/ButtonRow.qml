import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.0

Item {
    id: buttonRow

    Component.onCompleted: {
       startEndTime();
    }

    RowLayout {
        id: rowLayout
        height: 55
        anchors.right: parent.right
        anchors.left: parent.left       
        anchors.top: buttonRow.top
        width: parent.width

    }
        Button {
            id: productForecast
            y: 0
            width: 40
            height: 40
            anchors.left: rowLayout.right
            anchors.leftMargin: -248
            flat: true
            display: AbstractButton.IconOnly
            icon.color: "transparent"
            icon.source: "Icons/battery.png"
            onClicked: {
                if (productForecast.state == "on")
                    productForecast.state = "off";
                else
                    productForecast.state = "on";
                control.fingridButtonClicked("productionForecast")
                startEndTime()
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Power production forecast")
            background: Rectangle{

                color: parent.down ? "#f6f6f6" :
                           (parent.hovered ? "#d6d6d6" : "#1E90FF")
            }
        }
        Button {
            id: windProductionForecast
            y: 0
            width: 40
            height: 40
            anchors.left: rowLayout.right
            anchors.leftMargin: -202
            flat: true
            display: AbstractButton.IconOnly
            icon.color: "transparent"
            icon.source: "Icons/windmill.png"
            onClicked: {
                if (windForecast.state == "on")
                    windForecast.state = "off";
                else
                    windForecast.state = "on";
                control.fingridButtonClicked("windProductionForecast")
                startEndTime()
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Wind production forecast")
            background: Rectangle{

                color: parent.down ? "#f6f6f6" :
                           (parent.hovered ? "#d6d6d6" : "#1E90FF")
            }
        }
        Button {
           id: powerForecast
            y: 0
            width: 40
            height: 40
            anchors.left: rowLayout.right
            anchors.leftMargin: -294
            flat: true
            display: AbstractButton.IconOnly
            icon.color: "transparent"
            icon.source: "Icons/bulb.png"
            onClicked: {
                if (powerForecast.state == "on")
                    powerForecast.state = "off";
                else
                    powerForecast.state = "on";
                control.fingridButtonClicked("powerforecast")
                startEndTime();
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Power consumption forecast")
            background: Rectangle{

                color: parent.down ? "#f6f6f6" :
                           (parent.hovered ? "#d6d6d6" : "#1E90FF")
            }

        }
        Button {
           id: consumption
            x: 238
            y: 0
            width: 40
            height: 40
            anchors.left: rowLayout.right
            anchors.leftMargin: -133
            flat: true
            display: AbstractButton.IconOnly
            icon.source: "Icons/bulb.png"
            onClicked: {
                if (consumption.state == "on")
                    consumption.state = "off";
                else
                    consumption.state = "on";
                control.fingridButtonClicked("consumption")
                startEndTime();
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Total electricity consumption")

        }
        Button {
            id: production
            y: 0
            width: 40
            height: 40
            anchors.left: rowLayout.right
            anchors.leftMargin: -166
            flat: true
            display: AbstractButton.IconOnly
            icon.source: "Icons/battery.png"
            onClicked: {
                if (production.state == "on")
                    production.state = "off";
                else
                    production.state = "on";
                control.fingridButtonClicked("production")
                startEndTime();
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Total electricity production")

        }

        Button {
            id: windProduction
            y: 0
            width: 40
            height: 40
            anchors.left: rowLayout.right
            anchors.leftMargin: -102
            autoRepeat: true
            flat: true
            display: AbstractButton.IconOnly
            icon.source: "Icons/windmill.png"
            onClicked: {
                if (windProduction.state == "on")
                    windProduction.state = "off";
                else
                    windProduction.state = "on";
                control.fingridButtonClicked("windProduction")
                startEndTime();
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Windpower production")

        }

        Button {
            id: nuclearProduction
            y: 0
            width: 40
            height: 40
            anchors.left: rowLayout.right
            anchors.leftMargin: -72
            flat: true
            display: AbstractButton.IconOnly
            icon.color: "transparent"
            icon.source: "Icons/nuclear.png"
            onClicked: {
                if (nuclearProduction.state == "on")
                    nuclearProduction.state = "off";
                else
                    nuclearProduction.state = "on";
                control.fingridButtonClicked("nuclearProduction")
                startEndTime();
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Nuclearpower production")
        }
        Button {
            id: hydroProduction
            y: 0
            width: 40
            height: 40
            anchors.left: rowLayout.right
            anchors.leftMargin: -42
            flat: true
            display: AbstractButton.IconOnly
            icon.source: "Icons/hydropower.png"
            onClicked: {
                if (hydroProduction.state == "on")
                    hydroProduction.state = "off";
                else
                    hydroProduction.state = "on";
                control.fingridButtonClicked("hydroProduction")
                startEndTime();
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Hydropower production")
        }
        Button {
            id: cloudiness
            x: 34
            y: 0
            width: 40
            height: 40
            text: "Cloudiness"
            anchors.right: rowLayout.left
            anchors.rightMargin: -74
            flat: true
            icon.color: "transparent"
            display: AbstractButton.IconOnly
            icon.source: "Icons/weather.png"
            onClicked: {
                if (cloudiness.state == "on") {
                    cloudiness.state = "off";
                    display = AbstractButton.IconOnly
                } else {
                    cloudiness.state = "on";
                    text = "<font color='orange'>" + "C"
                    display = AbstractButton.TextOnly
                }
                checkIfButtonsEnabled()
                control.fmiButtonClicked("cloudiness")
                startEndTime();
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Cloudiness")
        }

        Button {
            id: wind
            y: 0
            width: 40
            height: 40
            anchors.right: rowLayout.left
            anchors.rightMargin: -35
            //anchors.left: rowLayout.right
            //anchors.leftMargin: -361
            flat: true
            display: AbstractButton.IconOnly
            icon.source: "Icons/tornado.png"
            onClicked: {
                if (wind.state == "on") {
                    display = AbstractButton.IconOnly
                    wind.state = "off"
                } else {
                    text = "<font color='darkblue'>" + "W"
                    display = AbstractButton.TextOnly
                    wind.state = "on"
                }
                checkIfButtonsEnabled()
                control.fmiButtonClicked("wind")
                startEndTime();
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Wind")
        }

        Button {
            id: temperature
            x: 67
            y: 0
            width: 40
            height: 40
            anchors.right: rowLayout.left
            anchors.rightMargin: -107
            //anchors.left: rowLayout.right
           // anchors.leftMargin: -311
            flat: true
            display: AbstractButton.IconOnly
            icon.color: "transparent"
            icon.source: "Icons/thermometer.png"
            onClicked: {
                if (temperature.state == "on") {
                    temperature.state = "off"
                    display = AbstractButton.IconOnly
                }
                else {
                    temperature.state = "on"
                    text = "<font color='green'>" + "T"
                    display = AbstractButton.TextOnly
                }
                checkIfButtonsEnabled()
                control.fmiButtonClicked("temperature")
                startEndTime();
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Temperature")

        }
        Button {
            id: windForecast
            x: 113
            y: 0
            width: 40
            height: 40
            anchors.right: rowLayout.left
            anchors.rightMargin: -153
            flat: true
            display: AbstractButton.IconOnly
            icon.color: "transparent"
            icon.source: "Icons/tornado.png"
            onClicked: {
                if (windForecast.state == "on") {
                    windForecast.state = "off"
                    display = AbstractButton.IconOnly
                    wfBack.color = "#FF6347"
                } else {
                    windForecast.state = "on"
                    text = "<font color='white'>" + "24H"
                    font.pointSize = 9
                    display = AbstractButton.TextOnly
                    wfBack.color = 'brown'
                }
                checkIfButtonsEnabled()
                control.fmiButtonClicked("windForecast")
                startEndTime()


            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Wind forecast")
            background: Rectangle{
                id: wfBack
                color: "#FF6347"
            }
        }
        Button {
            id: tempForecast
            x: 159
            y: 0
            width: 40
            height: 40
            anchors.right: rowLayout.left
            anchors.rightMargin: -199
            flat: true
            display: AbstractButton.IconOnly
            icon.color: "transparent"
            icon.source: "Icons/thermometer.png"
            onClicked: {
                if (tempForecast.state == "on") {
                    tempForecast.state = "off"
                    display = AbstractButton.IconOnly
                    tfBack.color = "#FF6347"
                } else {
                    tempForecast.state = "on"
                    text = "<font color='white'>" + "24H"
                    font.pointSize = 9
                    tfBack.color = 'blue'
                    display = AbstractButton.TextOnly
                }
                checkIfButtonsEnabled()
                control.fmiButtonClicked("temperatureForecast")
                startEndTime()
            }
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Temperature forecast")
            background: Rectangle{
                id: tfBack
                color: "#FF6347"
            }
        }

        function startEndTime(){
            control.setStartDate(Qt.formatDate(fromDate.calendar.selectedDate, "yyyy-MM-dd"))
            control.setEndDate(Qt.formatDate(toDate.calendar.selectedDate, "yyyy-MM-dd"))
            console.log(Qt.formatDate(fromDate.calendar.selectedDate, "yyyy-MM-dd"))

        }

        function getFMIState(button) {
            if(button === "tempForecast") {
                return tempForecast.state;
            } else if(button === "windForecast") {
                return windForecast.state;
            } else if(button === "temperature") {
                return temperature.state;
            } else if(button === "wind") {
                return wind.state;
            } else if(button === "cloudiness") {
                return cloudiness.state;
            }
        }

        function getFingridState(button) {
            if(button === "hydroProduction") {
                return hydroProduction.state;
            } else if(button === "nuclearProduction") {
                return nuclearProduction.state;
            } else if(button === "windProduction") {
                return windProduction.state;
            } else if(button === "production") {
                return production.state;
            } else if(button === "consumption") {
                return consumption.state;
            } else if(button === "powerForecast") {
                return powerForecast.state;
            } else if(button === "productForecast") {
                return productForecast.state;
            }
        }

        function checkIfButtonsEnabled() {
            if((temperature.state == "on") || (wind.state == "on") ||
                (cloudiness.state == "on")) {
                tempForecast.enabled = false;
                windForecast.enabled = false;
                wfBack.color = 'grey'
                tfBack.color = 'grey'
            } else if((windForecast.state == "on") ||
                (tempForecast.state == "on")) {
                temperature.enabled = false;
                wind.enabled = false;
                cloudiness.enabled = false;
                temperature.icon.color = 'grey'
            } else {
                tempForecast.enabled = true;
                windForecast.enabled = true;
                wfBack.color = "#FF6347"
                tfBack.color = "#FF6347"

                temperature.enabled = true;
                wind.enabled = true;
                cloudiness.enabled = true;
                temperature.icon.color = 'black'
            }
        }
}




/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_width:339;anchors_x:32;anchors_y:0}
D{i:3;anchors_x:205}D{i:2;anchors_x:238}D{i:5;anchors_x:299}D{i:4;anchors_x:269}D{i:7;anchors_x:32}
D{i:6;anchors_x:329}D{i:8;anchors_x:10}D{i:9;anchors_x:60}
}
##^##*/
