#ifndef FOLDER_UTILITIES_H
#define FOLDER_UTILITIES_H

#include <QDialog>

namespace Ui {
class FolderUtilities;
}

class FolderUtilities : public QDialog
{
    Q_OBJECT

public:
    explicit FolderUtilities(QWidget *parent = nullptr);
    ~FolderUtilities();

private:
    Ui::FolderUtilities *ui;
};

#endif // FOLDER_UTILITIES_H
