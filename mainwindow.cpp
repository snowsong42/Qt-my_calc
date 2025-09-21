#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置焦点策略，使窗口可以接收键盘事件
    setFocusPolicy(Qt::StrongFocus);

    // 连接数字按钮信号
    connect(ui->btn0, &QPushButton::clicked, this, &MainWindow::appendNumber);
    connect(ui->btn1, &QPushButton::clicked, this, &MainWindow::appendNumber);
    connect(ui->btn2, &QPushButton::clicked, this, &MainWindow::appendNumber);
    connect(ui->btn3, &QPushButton::clicked, this, &MainWindow::appendNumber);
    connect(ui->btn4, &QPushButton::clicked, this, &MainWindow::appendNumber);
    connect(ui->btn5, &QPushButton::clicked, this, &MainWindow::appendNumber);
    connect(ui->btn6, &QPushButton::clicked, this, &MainWindow::appendNumber);
    connect(ui->btn7, &QPushButton::clicked, this, &MainWindow::appendNumber);
    connect(ui->btn8, &QPushButton::clicked, this, &MainWindow::appendNumber);
    connect(ui->btn9, &QPushButton::clicked, this, &MainWindow::appendNumber);
    connect(ui->btnAsterisk, &QPushButton::clicked, this, &MainWindow::appendNumber);
    connect(ui->btnHash, &QPushButton::clicked, this, &MainWindow::appendNumber);

    // 连接功能按钮信号
    connect(ui->btnBackspace, &QPushButton::clicked, this, &MainWindow::onBackspaceClicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->btnCall, &QPushButton::clicked, this, &MainWindow::onCallClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 处理键盘按键事件
    switch(event->key()) {
    case Qt::Key_0:
        ui->btn0->click();
        break;
    case Qt::Key_1:
        ui->btn1->click();
        break;
    case Qt::Key_2:
        ui->btn2->click();
        break;
    case Qt::Key_3:
        ui->btn3->click();
        break;
    case Qt::Key_4:
        ui->btn4->click();
        break;
    case Qt::Key_5:
        ui->btn5->click();
        break;
    case Qt::Key_6:
        ui->btn6->click();
        break;
    case Qt::Key_7:
        ui->btn7->click();
        break;
    case Qt::Key_8:
        ui->btn8->click();
        break;
    case Qt::Key_9:
        ui->btn9->click();
        break;
    case Qt::Key_Asterisk:
        ui->btnAsterisk->click();
        break;
    case Qt::Key_NumberSign: // 这是正确的井号键常量
        ui->btnHash->click();
        break;
    case Qt::Key_Backspace:
        onBackspaceClicked();
        break;
    case Qt::Key_Delete:
        onClearClicked();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        onCallClicked();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::appendNumber()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString currentText = ui->displayLineEdit->text();
        QString newText = currentText + button->text();
        ui->displayLineEdit->setText(newText);
    }
}

void MainWindow::onBackspaceClicked()
{
    QString currentText = ui->displayLineEdit->text();
    if (!currentText.isEmpty()) {
        currentText.chop(1); // 移除最后一个字符
        ui->displayLineEdit->setText(currentText);
    }
}

void MainWindow::onClearClicked()
{
    ui->displayLineEdit->clear();
}

void MainWindow::onCallClicked()
{
    QString number = ui->displayLineEdit->text();
    if (!number.isEmpty()) {
        // 这里可以实现实际的拨号逻辑
        if(number == "7355608"){
            QMessageBox::information(this, "拨号中...", "密码正确:7355608\n炸弹已经安放!", "T阵营胜利");
            this->close();
        } else {
            QMessageBox::information(this, "拨号失败", QString("密码错误: %1\n炸弹安放失败!").arg(number), "重新安放");
        }
        // 在实际应用中，这里可能会调用系统API或发送网络请求
    }
}
