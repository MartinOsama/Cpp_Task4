#include <QApplication>
#include "StudentQueryWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    StudentQueryWidget widget;
    widget.show();
    return app.exec();
}
