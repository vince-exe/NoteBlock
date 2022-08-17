#include "main_dialog.h"

#include <QApplication>

#include "color_picker_dialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainDialog w;
    w.show();

    //ColorPickerDialog colorpicker;
    //colorpicker.show();

    //return colorpicker.exec();
    return w.exec();
}
