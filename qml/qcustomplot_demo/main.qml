import QtQuick 2.0
import CustomPlot 1.0

Rectangle {
    width: 360
    height: 360


    CustomPlotItem {

               id: customPlot
               anchors.fill: parent

               Component.onCompleted: initCustomPlot()

           }
}
