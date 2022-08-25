#ifndef DECRYPT_DIALOG_H
#define DECRYPT_DIALOG_H

#include <QDialog>

namespace Ui {
class DecryptDialog;
}

class DecryptDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DecryptDialog(QWidget *parent = nullptr);
    ~DecryptDialog();

private slots:
    void on_decKeyBox_textChanged(const QString &arg1);

    void on_browseBtn_clicked();

    void on_doneBtn_clicked();

private:
    Ui::DecryptDialog *ui;
};

#endif // DECRYPT_DIALOG_H
