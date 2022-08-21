#ifndef SAVE_AS_UTILITIES_H
#define SAVE_AS_UTILITIES_H

#include <QDialog>

namespace Ui {
class SaveAsUtilities;
}

class SaveAsUtilities : public QDialog
{
    Q_OBJECT

public:
    explicit SaveAsUtilities(QWidget *parent = nullptr);
    ~SaveAsUtilities();

private slots:
    void on_folderNameBox_textChanged(const QString &arg1);

    void on_cancelBtn_clicked();

    void on_doneBtn_clicked();

private:
    Ui::SaveAsUtilities *ui;

    void keyPressEvent(QKeyEvent* event);
};

#endif // SAVE_AS_UTILITIES_H
