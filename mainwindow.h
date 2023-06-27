#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFileInfo>
#include <QStandardPaths>
#include <QTextCursor>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

    void on_textEdit_textChanged();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_sizeBox_valueChanged(int arg1);

    void on_textEdit_cursorPositionChanged();

    void on_colorBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    bool isTextChanged;
    QTextCursor cursor;
    QTextCharFormat charFormat;
    QFont font;
};

#endif // MAINWINDOW_H
