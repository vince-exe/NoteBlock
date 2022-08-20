#ifndef ADD_FOLDER_DIALOG_H
#define ADD_FOLDER_DIALOG_H

#include <QDialog>

namespace Ui {
class AddFolderDialog;
}

class AddFolderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFolderDialog(QWidget *parent = nullptr);
    ~AddFolderDialog();

private:
    Ui::AddFolderDialog *ui;
};

#endif // ADD_FOLDER_DIALOG_H
