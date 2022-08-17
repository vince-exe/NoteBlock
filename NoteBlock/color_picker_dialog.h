#ifndef COLOR_PICKER_DIALOG_H
#define COLOR_PICKER_DIALOG_H

#include <QDialog>

/* return a QString rappresenting the rgb value */
QString getRGB(int r, int g, int b);

namespace Ui {
class ColorPickerDialog;
}

class ColorPickerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorPickerDialog(QWidget *parent = nullptr);
    ~ColorPickerDialog();

private slots:
    void on_reedSlider_valueChanged(int value);

    void on_greenSlider_valueChanged(int value);

    void on_blueSlider_valueChanged(int value);

    void on_redSpinBox_valueChanged(int arg1);

    void on_greenSpinBox_valueChanged(int arg1);

    void on_blueSpinBox_valueChanged(int arg1);

private:
    Ui::ColorPickerDialog *ui;
};

#endif // COLOR_PICKER_DIALOG_H
