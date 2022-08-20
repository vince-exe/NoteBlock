#ifndef SAVE_AS_DIALOG_H
#define SAVE_AS_DIALOG_H

#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class SaveAsDialog;
}

class SaveAsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveAsDialog(QWidget *parent = nullptr);
    ~SaveAsDialog();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void keyPressEvent(QKeyEvent* event);

    void on_pushButton_clicked();

    void on_fileNameBox_textChanged(const QString &arg1);

    void on_goBtn_clicked();

    void on_doneBtn_clicked();

    void on_doOptionBtn_clicked();

private:
    Ui::SaveAsDialog *ui;
    QFileSystemModel* dirmodel = new QFileSystemModel(this);;
};

#endif // SAVE_AS_DIALOG_H
