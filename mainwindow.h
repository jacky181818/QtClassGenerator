#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QList>

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
    void on_btnGenerate_clicked();
    bool processLine(QString line, QString &type, QString &name, QString &comment);    //��ÿ�зֽ�ɱ������͡���������ע��
    void display(QList<QMap<QString, QString>> listVars);
    void displayDeclare(QList<QMap<QString, QString>> listVars, QString className, QString baseClassName);
    void displayImplement(QList<QMap<QString, QString>> listVars, QString className, QString baseClassName);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
