#ifndef MAIN_DIALOG_H
#define MAIN_DIALOG_H

#include <QDialog>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

private slots:

private:
    Ui::MainDialog *ui;

    void resizeEvent(QResizeEvent* event);
};

#endif // MAIN_DIALOG_H
