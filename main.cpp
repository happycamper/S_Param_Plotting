#include "CustomPlotItem.h"
#include <QtWidgets/QApplication>
#include <QtQuick>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

        qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");

        QQuickView view(QStringLiteral("qml/qcustomplot_demo/main.qml"));
        view.setResizeMode(QQuickView::SizeRootObjectToView);
        view.resize(500, 500);
        view.show();

        return a.exec();
}
