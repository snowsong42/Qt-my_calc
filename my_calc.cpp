#include "my_calc.h"
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

my_calc::my_calc(QWidget* parent)
    : QMainWindow(parent)
{
    // 设置窗口属性
    setWindowTitle("计算器");
    setFixedSize(476, 570);

    // 创建控件和布局
    createWidgets();
    createLayout();
    createConnections();

    // 设置焦点策略
    setFocusPolicy(Qt::StrongFocus);
}

my_calc::~my_calc()
{
    // Qt的对象树会自动管理内存，不需要手动删除
}

void my_calc::createWidgets()
{
    // 创建中央部件
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建显示框
    displayLineEdit = new QLineEdit(centralWidget);
    displayLineEdit->setMinimumHeight(40);
    displayLineEdit->setFont(QFont("Century Gothic", 24));
    displayLineEdit->setStyleSheet("font: 24pt \"Century Gothic\";");
    displayLineEdit->setText("");
    displayLineEdit->setAlignment(Qt::AlignRight);
    displayLineEdit->setReadOnly(true);
    displayLineEdit->setPlaceholderText("请输入号码...");

    // 创建数字按钮
    btn0 = new QPushButton("0", centralWidget);
    btn1 = new QPushButton("1", centralWidget);
    btn2 = new QPushButton("2", centralWidget);
    btn3 = new QPushButton("3", centralWidget);
    btn4 = new QPushButton("4", centralWidget);
    btn5 = new QPushButton("5", centralWidget);
    btn6 = new QPushButton("6", centralWidget);
    btn7 = new QPushButton("7", centralWidget);
    btn8 = new QPushButton("8", centralWidget);
    btn9 = new QPushButton("9", centralWidget);
    btnPercent = new QPushButton("%", centralWidget);
    btnPeriod = new QPushButton(".", centralWidget);

    // 创建功能按钮
    btnBackspace = new QPushButton("删除", centralWidget);
    btnClear = new QPushButton("C", centralWidget);
    btnCommit = new QPushButton("=", centralWidget);

    // 创建其他按钮
    btnMC = new QPushButton("MC", centralWidget);
    btnMplus = new QPushButton("M+", centralWidget);
    btnMminus = new QPushButton("M-", centralWidget);
    btnMR = new QPushButton("MR", centralWidget);
    btnDiv = new QPushButton("÷", centralWidget);
    btnMul = new QPushButton("×", centralWidget);
    btnMinus = new QPushButton("-", centralWidget);
    btnPlus = new QPushButton("+", centralWidget);

    // 设置按钮最小高度
    QList<QPushButton*> allButtons = centralWidget->findChildren<QPushButton*>();
    for (QPushButton* button : allButtons) {
        button->setMinimumHeight(50);
    }
    btnBackspace->setMinimumHeight(40);
    btnCommit->setMinimumHeight(100);
}

void my_calc::createLayout()
{
    // 创建主布局
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setHorizontalSpacing(15);

    // 设置显示框位置
    displayLineEdit->setGeometry(30, 30, 411, 71);

    // 布局按钮
    // 第一行
    gridLayout->addWidget(btnMC, 0, 0);
    gridLayout->addWidget(btnMplus, 0, 1);
    gridLayout->addWidget(btnMminus, 0, 2);
    gridLayout->addWidget(btnMR, 0, 3);

    // 第二行
    gridLayout->addWidget(btnClear, 1, 0);
    gridLayout->addWidget(btnDiv, 1, 1);
    gridLayout->addWidget(btnMul, 1, 2);
    gridLayout->addWidget(btnBackspace, 1, 3);

    // 第三行
    gridLayout->addWidget(btn1, 2, 0);
    gridLayout->addWidget(btn2, 2, 1);
    gridLayout->addWidget(btn3, 2, 2);
    gridLayout->addWidget(btnMinus, 2, 3);

    // 第四行
    gridLayout->addWidget(btn4, 3, 0);
    gridLayout->addWidget(btn5, 3, 1);
    gridLayout->addWidget(btn6, 3, 2);
    gridLayout->addWidget(btnPlus, 3, 3);

    // 第五行
    gridLayout->addWidget(btn7, 4, 0);
    gridLayout->addWidget(btn8, 4, 1);
    gridLayout->addWidget(btn9, 4, 2);
    gridLayout->addWidget(btnCommit, 4, 3, 2, 1); // 跨2行

    // 第六行
    gridLayout->addWidget(btnPercent, 5, 0);
    gridLayout->addWidget(btn0, 5, 1);
    gridLayout->addWidget(btnPeriod, 5, 2);

    // 设置布局边距
    gridLayout->setContentsMargins(50, 110, 50, 30);
}

void my_calc::createConnections()
{
    // 连接功能按钮信号
    connect(btnBackspace, &QPushButton::clicked, this, &my_calc::onBackspaceClicked);
    connect(btnClear, &QPushButton::clicked, this, &my_calc::onClearClicked);
    connect(btnCommit, &QPushButton::clicked, this, &my_calc::onCommitClicked);

    // 连接数字按钮信号
    connect(btn0, &QPushButton::clicked, this, &my_calc::appendNumber);
    connect(btn1, &QPushButton::clicked, this, &my_calc::appendNumber);
    connect(btn2, &QPushButton::clicked, this, &my_calc::appendNumber);
    connect(btn3, &QPushButton::clicked, this, &my_calc::appendNumber);
    connect(btn4, &QPushButton::clicked, this, &my_calc::appendNumber);
    connect(btn5, &QPushButton::clicked, this, &my_calc::appendNumber);
    connect(btn6, &QPushButton::clicked, this, &my_calc::appendNumber);
    connect(btn7, &QPushButton::clicked, this, &my_calc::appendNumber);
    connect(btn8, &QPushButton::clicked, this, &my_calc::appendNumber);
    connect(btn9, &QPushButton::clicked, this, &my_calc::appendNumber);
    connect(btnPercent, &QPushButton::clicked, this, &my_calc::appendNumber);
    connect(btnPeriod, &QPushButton::clicked, this, &my_calc::appendNumber);
}

void my_calc::keyPressEvent(QKeyEvent* event)
{
    // 处理键盘按键事件
    switch (event->key()) {
    case Qt::Key_0:
        btn0->click();
        break;
    case Qt::Key_1:
        btn1->click();
        break;
    case Qt::Key_2:
        btn2->click();
        break;
    case Qt::Key_3:
        btn3->click();
        break;
    case Qt::Key_4:
        btn4->click();
        break;
    case Qt::Key_5:
        btn5->click();
        break;
    case Qt::Key_6:
        btn6->click();
        break;
    case Qt::Key_7:
        btn7->click();
        break;
    case Qt::Key_8:
        btn8->click();
        break;
    case Qt::Key_9:
        btn9->click();
        break;
    case Qt::Key_Percent:  //%号
        btnPercent->click();
        break;
    case Qt::Key_Period: // .号
        btnPeriod->click();
        break;
    case Qt::Key_Backspace:
        btnBackspace->click();
        break;
    case Qt::Key_Delete:
        btnClear->click();
        break;
    case Qt::Key_ParenLeft: //(
        break;
    case Qt::Key_ParenRight:    //)
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        btnCommit->click();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void my_calc::appendNumber()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString currentText = displayLineEdit->text();
        QString newText = currentText + button->text();
        displayLineEdit->setText(newText);
    }
}

void my_calc::onBackspaceClicked()
{
    QString currentText = displayLineEdit->text();
    if (!currentText.isEmpty()) {
        currentText.chop(1); // 移除最后一个字符
        displayLineEdit->setText(currentText);
    }
}

void my_calc::onClearClicked()
{
    displayLineEdit->clear();
}

void my_calc::onCommitClicked()
{
    QString number = displayLineEdit->text();
    if (!number.isEmpty()) {
        // 这里可以实现实际的拨号逻辑
        if (number == "7355608") {
            QMessageBox::information(this, "拨号中...",
                "密码正确:7355608\n炸弹已经安放!",
                QMessageBox::Ok);
            this->close();
        }
        else {
            QMessageBox::information(this, "拨号失败",
                QString("密码错误: %1\n炸弹安放失败!").arg(number),
                QMessageBox::Ok);
        }
        // 在实际应用中，这里可能会调用系统API或发送网络请求
    }
}