import QtQuick 2.0
import QtCharts 2.3
import QtCharts 2.12

Item {    
    id: element
    visible: true


    Connections {
        target: view

        onProductionDataChanged: { // Sähköntuotanto pylväsdiagrammina
            var state = buttonRow.getFingridState("production")
            if(state === "on") {
                productionAxisY.visible = true
                var split = control.splitProductionLength()
                var a=0;
                var length = control.productionLength();
                while(a < length) {
                    productionSet.append(control.getFingridData(a));
                    if(length < 100) {
                        a++;
                    } else {
                        a+=split;
                    }
                }
                barAxisX.min = 0
                barAxisX.max = productionSet.count-1
                productionAxisY.max = productionSet.at(productionSet.count-1)+5000
            } else {
                productionSet.values = []
                productionAxisY.visible = false
            }

            /*for(var a = 0; a < control.productionLength(); a+=split){
                productionSet.append(control.getFingridData(a));
            }*/

        }
        // Sähkönkulutus pylväsdiagrammina
        onConsumptionDataChanged: {
            var state = buttonRow.getFingridState("consumption")
            if(state === "on") {
                consumptionAxisY.visible = true
                var split = control.splitProductionLength()
                var a=0;
                var length = control.productionLength();
                while(a < length) {
                    consumptionSet.append(control.getFingridData(a));
                    if(length < 100) {
                        a++;
                    } else {
                        a+=split;
                    }
                }
                barAxisX.min = 0
                barAxisX.max = consumptionSet.count-1
            } else {
                consumptionSet.values = []
                consumptionAxisY.visible = false
            }
        }
        onWindProductionDataChanged: {
            var state = buttonRow.getFingridState("windProduction")
            if(state === "on") {
                windProductionAxisY.visible = true
                var split = control.splitProductionLength()
                var a=0;
                var length = control.productionLength();
                while(a < length) {
                    windSet.append(control.getFingridData(a));
                if(length < 100) {
                    a++;
                } else {
                    a+=split;
                }
                }
                barAxisX.min = 0
                barAxisX.max = windSet.count-1
            } else {
                windSet.values = []
                windProductionAxisY.visible = false
            }
        }
        onNuclearDataChanged: {
            var state = buttonRow.getFingridState("nuclearProduction")
            if(state === "on") {
                nuclearAxisY.visible = true
                var split = control.splitProductionLength()
                var a=0;
                var length = control.productionLength();
                while(a < length) {
                    nuclearSet.append(control.getFingridData(a));
                if(length < 100) {
                    a++;
                } else {
                    a+=split;
                }
                }
                barAxisX.min = 0
                barAxisX.max = nuclearSet.count-1
            } else {
                nuclearSet.values = []
                nuclearAxisY.visible = false
            }
        }
        onWaterDataChanged: {
            var state = buttonRow.getFingridState("hydroProduction")
            if(state === "on") {
                waterAxisY.visible = true
                var split = control.splitProductionLength()
                var a=0;
                var length = control.productionLength();
                while(a < length) {
                    waterSet.append(control.getFingridData(a));
                if(length < 100) {
                    a++;
                } else {
                    a+=split;
                }
                }
                barAxisX.min = 0
                barAxisX.max = waterSet.count-1
            } else {
                waterSet.values = []
                waterAxisY.visible = false
            }
        }

        onProductionForecastDataChanged: {
            var state = buttonRow.getFingridState("productForecast")
            if(state === "on") {
                productionAxisY.visible = true
                var split = control.splitProductionLength()
                var a=0;
                var length = control.productionLength();
                while(a < length) {
                    productionForecastSet.append(control.getFingridData(a));
                    if(length < 100) {
                        a++;
                    } else {
                        a+=split;
                    }
                }
                barAxisX.min = 0
                barAxisX.max = productionForecastSet.count-1
                productionAxisY.max = productionForecastSet.at(productionForecastSet.count-1)+5000
            } else {
                productionForecastSet.values = []
                productionAxisY.visible = false
            }
        }

        onPowerForecastDataChanged: {
            var state = buttonRow.getFingridState("powerForecast")
            if(state === "on") {
                consumptionAxisY.visible = true
                var split = control.splitProductionLength()
                var a=0;
                var length = control.productionLength();
                while(a < length) {
                    powerForecastSet.append(control.getFingridData(a));
                    if(length < 100) {
                        a++;
                    } else {
                        a+=split;
                    }
                }
                barAxisX.min = 0
                barAxisX.max = powerForecastSet.count-1
            } else {
                powerForecastSet.values = []
                consumptionAxisY.visible = false
            }
        }

        onTemperatureDataChanged: {
            var state = buttonRow.getFMIState("temperature")
            if(state === "on") {
                lineAxisY.visible = true
                for(var i=0; i<control.length(); i++) {
                    temperatureGraph.append(i, control.getData(i));
                }
                lineAxisY.min = control.getMinTemperature()-2
                lineAxisY.max = control.getMaxTemperature()+2
                lineAxisX.min = temperatureGraph.at(0).x
                lineAxisX.max = temperatureGraph.at(temperatureGraph.count-1).x
            } else {
                lineAxisY.visible = false
                temperatureGraph.clear();
            }
        }
        onCloudinessDataChanged: {
            var state = buttonRow.getFMIState("cloudiness")
            if(state === "on") {
                cloudinessAxisY.visible = true
                for(var i=0; i<control.length(); i++) {
                    cloudinessGraph.append(i, control.getData(i));
                }
                lineAxisX.min = cloudinessGraph.at(0).x
                lineAxisX.max = cloudinessGraph.at(cloudinessGraph.count-1).x
            } else {
                cloudinessAxisY.visible = false
                cloudinessGraph.clear();
            }
        }
        onWindDataChanged: {
            var state = buttonRow.getFMIState("wind")
            if(state === "on") {
                windAxisY.visible = true
                for(var i=0; i<control.length(); i++) {
                    windGraph.append(i, control.getData(i));
                }
                lineAxisX.min = windGraph.at(0).x
                lineAxisX.max = windGraph.at(windGraph.count-1).x
            } else {
                windAxisY.visible = false
                windGraph.clear();
            }
        }
        onWindForecastDataChanged: {
            var state = buttonRow.getFMIState("windForecast")
            if(state === "on") {
                windAxisY.visible = true
                for(var i=0; i<control.length(); i++) {
                    windForecastGraph.append(i, control.getData(i));
                }
                lineAxisX.min = windForecastGraph.at(0).x
                lineAxisX.max = windForecastGraph.at(windForecastGraph.count-1).x
            } else {
                windAxisY.visible = false
                windForecastGraph.clear();
            }
        }
        onTemperatureForecastDataChanged: {
            var state = buttonRow.getFMIState("tempForecast")
            if(state === "on") {
                lineAxisY.visible = true
                for(var i=0; i<control.length(); i++) {
                    temperatureForecastGraph.append(i, control.getData(i));
                }
                lineAxisX.min = temperatureForecastGraph.at(0).x
                lineAxisX.max = temperatureForecastGraph.at(temperatureForecastGraph.count-1).x
                lineAxisY.min = -30
                lineAxisY.max = 30
            } else {
                lineAxisY.visible = false
                temperatureForecastGraph.clear();
            }
        }
    }

    Rectangle {
        id: chartBorder
        height: graphWindow.height
        width: graphWindow.width
        anchors.fill: parent
        border.color: "black"
        border.width: 5
    }

    ChartView {
        id: bar
        visible: true
        legend.visible: true
        width: chartBorder.width * 0.98
        height: chartBorder.height *0.98
        antialiasing: true


        ValueAxis {
            id: lineAxisX
            min: 0
            max:20
            visible: false
        }

        ValueAxis {
            id: lineAxisY
            titleText: "Celsius"
            min: -10
            max: 30
            visible: false
        }

        ValueAxis {
            id: cloudinessAxisY
            titleText: "Cloudiness"
            min: 0
            max: 8
            visible: false
        }

        ValueAxis {
            id: windAxisY
            titleText: "Wind"
            min: 0
            max: 30
            visible: false
        }

        ValueAxis {
            id: barAxisX
            min: 0
            max: 50
            visible: false
        }

        ValueAxis {
            id: barAxisY
            min: 0
        }

        ValueAxis {
            id: productionAxisY
            titleText: "Production"
            min: 0
            max: 10000
            visible: false
        }

        ValueAxis {
            id: consumptionAxisY
            titleText: "Consumption"
            min: 0
            max: 15000
            visible: false
        }

        ValueAxis {
            id: windProductionAxisY
            titleText: "Wind Production"
            min: 0
            max: 2200
            visible: false
        }

        ValueAxis {
            id: nuclearAxisY
            titleText: "Nuclear power"
            min: 0
            max: 3000
            visible: false
        }

        ValueAxis {
            id: waterAxisY
            titleText: "Hydropower"
            min: 0
            max: 3000
            visible: false
        }

        DateTimeAxis {
            id: xTime
            format: "yyyy MMM dd"
            tickCount: 4
            min: fromDate.calendar.selectedDate
            max: toDate.calendar.selectedDate
            visible: true


        }/*        function timeInterval() {
            if (fromDate.calendar.getFullYear !== toDate.calendar.getFullYear){
                return "yyyy MMM" }
            else if (fromDate.calendar.getMonth !== toDate.calendar.getMonth){
                return "MMM dd" }
            else if (fromDate.calendar.getday !== toDate.calendar.getDay){
                return "dd hh" }
            else {
                return "yyyy MMM"  }
        }*/

       BarSeries {
            name: "ElectricityView"
            id: productionSeries
            axisX: barAxisX
            axisY: productionAxisY
            barWidth: 2

            BarSet {
                id: productionSet
                label: "Electricity Production"
                values: []
                color: "blue"
                borderColor: "black"
            }
       }
       BarSeries {
            name: "ElectricityView"
            id: consumptionSeries
            axisX: barAxisX
            axisY: consumptionAxisY
            barWidth: 2

            BarSet {
                id: consumptionSet
                label: "Electricity Consumption"
                values: []
                color: "red"
            }
        }
       BarSeries {
            name: "ElectricityView"
            id: windSeries
            axisX: barAxisX
            axisY: windProductionAxisY
            barWidth: 2

            BarSet {
                id: windSet
                label: "Wind production"
                values: []
                color: "green"
            }
        }
       BarSeries {
            name: "ElectricityView"
            id: nuclearSeries
            axisX: barAxisX
            axisY: nuclearAxisY
            barWidth: 2

            BarSet {
                id: nuclearSet
                label: "Nuclear production"
                values: []
                color: "orange"
            }
        }
       BarSeries {
            name: "ElectricityView"
            id: waterSeries
            axisX: barAxisX
            axisY: waterAxisY
            barWidth: 2

            BarSet {
                id: waterSet
                label: "Water production"
                values: []
                color: "lightblue"
            }
        }

       BarSeries {
            name: "ElectricityView"
            id: productionForecastSeries
            axisX: barAxisX
            axisY: productionAxisY
            barWidth: 2

            BarSet {
                id: productionForecastSet
                label: "Production forecast"
                values: []
                color: "orange"
            }
        }

       BarSeries {
            name: "ElectricityView"
            id: powerForecastSeries
            axisX: barAxisX
            axisY: consumptionAxisY
            barWidth: 2

            BarSet {
                id: powerForecastSet
                label: "Power forecast"
                values: []
                color: "darkgreen"
            }
        }

        LineSeries {
                name: "Temperature"
                id: temperatureGraph
                axisX: lineAxisX
                axisYRight: lineAxisY
                color: "green"
                width: 2
        }
        LineSeries {

                name: "Power"
                id: lineSeries2
                axisX: lineAxisX
                axisYRight: lineAxisY
         }
        LineSeries {

                name: "Cloudiness"
                id: cloudinessGraph
                axisX: lineAxisX
                axisYRight: cloudinessAxisY
        }
        LineSeries {
                name: "Wind"
                id: windGraph
                axisX: lineAxisX
                axisYRight: windAxisY
        }
        LineSeries {
                name: "Wind Forecast"
                id: windForecastGraph
                axisX: lineAxisX
                axisYRight: lineAxisY
        }
        LineSeries {
                name: "Temperature Forecast"
                id: temperatureForecastGraph
                axisX: lineAxisX
                axisYRight: lineAxisY
        }
        LineSeries {
                name: "Production Forecast"
                id: productionForecastGraph
                axisX: lineAxisX
                axisYRight: lineAxisY
        }

        LineSeries {
                name: "Date"
                axisX: xTime
        }

    }

}




/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_width:0}
}
##^##*/
