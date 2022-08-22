#ifndef OPEN_FILE_DIALOG_H
#define OPEN_FILE_DIALOG_H

#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class OpenFileDialog;
}

class OpenFileDialog : public QDialog
{
    Q_OBJECT

public:
    static bool fileOpened;

public:
    explicit OpenFileDialog(QWidget *parent = nullptr);
    ~OpenFileDialog();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_resetPathBtn_clicked();

    void on_browseBtn_clicked();

    void on_doOptionBtn_clicked();

    void on_openBtn_clicked();

private:
    Ui::OpenFileDialog *ui;
    QFileSystemModel* dirFilemodel = new QFileSystemModel(this);;
};

#endif // OPEN_FILE_DIALOG_H
