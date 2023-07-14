#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // init color box
    color = {"red", "blue", "yellow", "black"};
    for (int i=0;i<4;i++){
        ui->colorBox->addItem(color[i]);
    }
    ui->colorBox->setCurrentIndex(3);

    // set default font
    font.setFamily("Arial");
    font.setPointSize(10);
    ui->textEdit->document()->setDefaultFont(font);
    cursor = ui->textEdit->textCursor();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->sizeBox->setValue(font.pointSize());

    // check if text is change
    isTextChanged = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString getFileName(QString &filePath){
    QFileInfo fileInfo(filePath);
    return fileInfo.fileName();
}

void MainWindow::on_actionNew_triggered()
{
    if(!currentFile.isEmpty()){
        //neu file da ton tai thi hien diaglog hoi viec save
    } else {
        currentFile.clear();
        ui->textEdit->setText(QString());
        this->setWindowTitle("MyNote");
    }
}

void MainWindow::on_actionOpen_triggered()
{

    if(isTextChanged){
        // neu file hien tai chua luu thi phai hien len dialog hoi co muon luu hay khong
    }

    QString initDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filePath = QFileDialog::getOpenFileName(this, "Open file", initDir, "Text Documents (*.txt);;All Files (*.*)");
    QFile file(filePath);

    if(!filePath.isEmpty()){
        if(file.open(QFile::ReadOnly|QFile::Text)){
            QTextStream in(&file);
            in.setCodec("UTF-8");
            QString fileContent = in.readAll();
            QString fileName = getFileName(filePath);
            ui->textEdit->setText(fileContent);
            currentFile = filePath;
            this->setWindowTitle(fileName);
            file.close();
            isTextChanged = false;
        } else {
            QMessageBox::warning(this, "Warning", "Cannot open file\n" + file.errorString());
            return;
        }
    } else {
        return;
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString initDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filePath = QFileDialog::getSaveFileName(this, "Save As", initDir, "Text Documents (*.txt);;All Files (*.*)");
    QFile file(filePath);
    if(!filePath.isEmpty()){
        if(file.open(QFile::WriteOnly|QFile::Text)){
            QTextStream out(&file);
            QString fileName = getFileName(filePath);
            out << ui->textEdit->toPlainText();
            currentFile = filePath;
            this->setWindowTitle(fileName);
            file.close();
            isTextChanged = false;
            setWindowTitle(windowTitle().remove('*'));
        } else {
            QMessageBox::warning(this, "Warning", "Cannot save file\n" + file.errorString());
            return;
        }
    } else {
        return;
    }
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(currentFile);
    if(!file.exists()){
        on_actionSave_As_triggered();
    } else {
        if(file.open(QFile::WriteOnly|QFile::Text)){
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            file.close();
            isTextChanged = false;
            setWindowTitle(windowTitle().remove('*'));
        } else {
            QMessageBox::warning(this, "Warning", "Cannot save file\n" + file.errorString());
            return;
        }
    }
}

void MainWindow::on_textEdit_textChanged()
{
    if(!isTextChanged){
        isTextChanged = true;
        this->setWindowTitle(windowTitle()+'*');
    }
}

void MainWindow::on_actionClose_triggered()
{
    MainWindow::close();
}

void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->textEdit->setFont(f);
}

// change size of font
void MainWindow::on_sizeBox_valueChanged(int arg1)
{
    // get info of current font
//    charFormat = cursor.charFormat();
//    font = charFormat.font();

    // update font
//    font.setPointSize(arg1);
//    charFormat.setFont(font);
//    cursor.setCharFormat(charFormat);
//    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->setFontPointSize(arg1);
}

// display size of current font
void MainWindow::on_textEdit_cursorPositionChanged()
{
    cursor = ui->textEdit->textCursor();
    charFormat = cursor.charFormat();
    font = charFormat.font();
    ui->sizeBox->setValue(font.pointSize());
}

void MainWindow::on_colorBox_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "red"){
        setColor.setRgb(255,0,0);
    } else if (arg1 == "blue") {
        setColor.setRgb(0,0,255);
    } else if (arg1 == "yellow") {
        setColor.setRgb(255,255,0);
    } else {
        setColor.setRgb(0,0,0);
    }
    ui->textEdit->setTextColor(setColor);
}
