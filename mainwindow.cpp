#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QDebug>

#define CRLF "\n"
#define TAB_INTERVAL "    "

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGenerate_clicked()
{
    QString strContent = ui->txtProperties->toPlainText();
    strContent.replace("\r\n", "\n");

    QStringList lines = strContent.split("\n");

    QList<QMap<QString, QString>> lstVars;

    QList<QString>::iterator it = lines.begin();
    while (it != lines.end()) {
        qDebug() << *it;
        QString type, name, comment;
        if (processLine(*it, type, name, comment))
        {
            QMap<QString, QString> mapOneVar;
            mapOneVar["name"]   = name;
            mapOneVar["type"]   = type;
            mapOneVar["comment"] = comment;
            lstVars.append(mapOneVar);
        }
        it++;
    }

    ui->txtProperties->append(QString("/*********************** declare ***********************/%1").arg(CRLF));

    display(lstVars);
}

bool MainWindow::processLine(QString line, QString &type, QString &name, QString &comment)
{
    int iSemicolon = line.indexOf(';');
    if (iSemicolon != -1)
    {
        comment = line.right(line.length() - (iSemicolon + 1)).trimmed();   //获取注释
        line = line.left(iSemicolon);
        line.replace(QRegularExpression("\\s+"), " ");  // 去掉重复的空格
        line = line.trimmed();
        QStringList vars = line.split(' ');
        name = vars.takeLast(); // 获取变量名
        type = vars.join(' ');  // 变量类型
        qDebug() << u8"变量类型:" << type << u8" 变量名：" << name << u8" 注释：" << comment;
        return true;
    }

    return false;
}

void MainWindow::display(QList<QMap<QString, QString> > listVars)
{
    displayDeclare(listVars, ui->edtClassName->text().trimmed(), ui->cbxBaseClassName->currentText());
    ui->txtProperties->append(QString("/*********************** implement ***********************/%1").arg(CRLF));
    displayImplement(listVars, ui->edtClassName->text().trimmed(), ui->cbxBaseClassName->currentText());
}

void MainWindow::displayDeclare(QList<QMap<QString, QString> > listVars, QString className, QString baseClassName)
{
    QString s = QString("class %1 : public %2").arg(className).arg(baseClassName);
    ui->txtProperties->append(s);
    ui->txtProperties->append(QString("{"));

    ui->txtProperties->append(QString("%1Q_OBJECT").arg(TAB_INTERVAL));
    QMap<QString, QString> var;
    foreach(var, listVars)
    {
        s = QString("%1Q_PROPERTY(%2 %3 MEMBER %3)").arg(TAB_INTERVAL).arg(var["type"]).arg(var["name"]);
        ui->txtProperties->append(s);
    }
    ui->txtProperties->append(QString("%1public:").arg(CRLF));

    // 构造函数
    s = QString("%3Q_INVOKABLE %1(%2 *parent = nullptr);").arg(className).arg(baseClassName).arg(TAB_INTERVAL);
    ui->txtProperties->append(s);

    // 拷贝构造函数
    s = QString("%2%1(const %1 &obj);").arg(className).arg(TAB_INTERVAL);
    ui->txtProperties->append(s);

    // 赋值函数
    s = QString("%2%1 & operator = (const %1 &obj);").arg(className).arg(TAB_INTERVAL);
    ui->txtProperties->append(s);

    // 变量声明
    foreach(var, listVars)
    {
        s = QString("%1%2 %3; \t%4").arg(TAB_INTERVAL).arg(var["type"]).arg(var["name"]).arg(var["comment"]);
        ui->txtProperties->append(s);
    }

    ui->txtProperties->append(QString("%1private:").arg(CRLF));

    // copyValue 函数
    s = QString("%2void copyValue(const %1 &obj);").arg(className).arg(TAB_INTERVAL);
    ui->txtProperties->append(s);

    ui->txtProperties->append(QString("};%1").arg(CRLF));
}

void MainWindow::displayImplement(QList<QMap<QString, QString> > listVars, QString className, QString baseClassName)
{
    // 构造函数
    QString s = QString("%1::%1(%2 *parent) : %2(parent)").arg(className).arg(baseClassName);
    ui->txtProperties->append(s);
    ui->txtProperties->append(QString("{%1").arg(CRLF));
    ui->txtProperties->append(QString("}%1").arg(CRLF));

    // 拷贝构造函数
    s = QString("%1::%1(const %1 &obj)").arg(className);
    ui->txtProperties->append(s);
    ui->txtProperties->append(QString("{"));
    s = QString("%1copyValue(obj);").arg(TAB_INTERVAL);
    ui->txtProperties->append(s);
    ui->txtProperties->append(QString("}%1").arg(CRLF));

    // 赋值函数
    s = QString("%1 &%1::operator = (const %1 &obj)").arg(className);
    ui->txtProperties->append(s);
    ui->txtProperties->append(QString("{"));
    s = QString("%1copyValue(obj);").arg(TAB_INTERVAL);
    ui->txtProperties->append(s);
    s = QString("%1return *this;").arg(TAB_INTERVAL);
    ui->txtProperties->append(s);
    ui->txtProperties->append(QString("}%1").arg(CRLF));

    // copyValue 函数
    s = QString("void %1::copyValue(const %1 &obj)").arg(className);
    ui->txtProperties->append(s);
    ui->txtProperties->append(QString("{"));
    QMap<QString, QString> var;
    foreach(var, listVars)
    {
        s = QString("%1%2 = obj.%3;").arg(TAB_INTERVAL).arg(var["name"],-24, ' ').arg(var["name"]);
        ui->txtProperties->append(s);
    }
    ui->txtProperties->append(QString("}%1").arg(CRLF));
}
