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

private:
    Ui::OptionsMenuDialog *ui;
};

#endif // OPTIONS_MENU_DIALOG_H
