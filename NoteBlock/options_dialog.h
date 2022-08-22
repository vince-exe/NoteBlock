#ifndef OPTIONS_DIALOG_H
#define OPTIONS_DIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    /* used to check if the users wants to change the text color or background color */
    static bool changeTextColor;

    /* used to check if the user has successfully created the file */
    static bool fileCreated;

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();

private slots:
    void on_resetBtn_clicked();

    void on_doneBtn_clicked();

    void on_currentTextColorLabel_clicked();

    void on_currentBackColorLabel_clicked();

private:
    Ui::OptionsDialog *ui;
};

#endif // OPTIONS_DIALOG_H
