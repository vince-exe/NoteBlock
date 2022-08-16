#ifndef OPTIONS_MENU_DIALOG_H
#define OPTIONS_MENU_DIALOG_H

#include <QDialog>

namespace Ui {
class OptionsMenuDialog;
}

class OptionsMenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsMenuDialog(QWidget *parent = nullptr);
    ~OptionsMenuDialog();

private slots:
    void on_saveAsBtn_clicked();

    void on_saveBtn_clicked();

    void on_openBtn_clicked();

    void on_newBtn_clicked();

    void on_optionsBtn_clicked();

private:
    Ui::OptionsMenuDialog *ui;
};

#endif // OPTIONS_MENU_DIALOG_H
