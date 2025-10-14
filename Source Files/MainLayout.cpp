#include "MainLayout.h"
#include "BaseLayout.h"

MainLayout::MainLayout(QWidget* parent)
    : BaseLayout(parent)
{
    createWidgets();
    setupLayout();
    setupConnections();
}

MainLayout::~MainLayout()
{
    // Qt的对象树会自动管理内存
}

void MainLayout::createWidgets()
{
    // 创建数字按钮
    btn0 = new QPushButton("0", this);
    btn1 = new QPushButton("1", this);
    btn2 = new QPushButton("2", this);
    btn3 = new QPushButton("3", this);
    btn4 = new QPushButton("4", this);
    btn5 = new QPushButton("5", this);
    btn6 = new QPushButton("6", this);
    btn7 = new QPushButton("7", this);
    btn8 = new QPushButton("8", this);
    btn9 = new QPushButton("9", this);
    btnPercent = new QPushButton("%", this);
    btnPeriod = new QPushButton(".", this);

    // 创建功能按钮
    btnBackspace = new QPushButton("⌫", this);
    btnClear = new QPushButton("C", this);
    btnCommit = new QPushButton("=", this);

    // 创建其他按钮
    btnMC = new QPushButton("MC", this);
    btnMplus = new QPushButton("M+", this);
    btnMminus = new QPushButton("M-", this);
    btnMR = new QPushButton("MR", this);
    btnDiv = new QPushButton("÷", this);
    btnMul = new QPushButton("×", this);
    btnMinus = new QPushButton("-", this);
    btnPlus = new QPushButton("+", this);

    // 设置按钮样式 - 更小的按钮
    QList<QPushButton*> allButtons = findChildren<QPushButton*>();
    for (QPushButton* button : allButtons) {
        setupButtonStyle(button);
        button->setMinimumSize(45, 45); // 更小的按钮
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    // 特殊按钮样式
    btnCommit->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; }");
    btnClear->setStyleSheet("QPushButton { background-color: #f44336; color: white; }");
    btnBackspace->setStyleSheet("QPushButton { background-color: #ff9800; color: white; }");
}

void MainLayout::setupLayout()
{
    // 创建主布局
    gridLayout = new QGridLayout(this);
    gridLayout->setHorizontalSpacing(5);  // 减少水平间距
    gridLayout->setVerticalSpacing(5);    // 减少垂直间距
    gridLayout->setContentsMargins(10, 10, 10, 10);

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
    gridLayout->addWidget(btn7, 2, 0);
    gridLayout->addWidget(btn8, 2, 1);
    gridLayout->addWidget(btn9, 2, 2);
    gridLayout->addWidget(btnMinus, 2, 3);

    // 第四行
    gridLayout->addWidget(btn4, 3, 0);
    gridLayout->addWidget(btn5, 3, 1);
    gridLayout->addWidget(btn6, 3, 2);
    gridLayout->addWidget(btnPlus, 3, 3);

    // 第五行
    gridLayout->addWidget(btn1, 4, 0);
    gridLayout->addWidget(btn2, 4, 1);
    gridLayout->addWidget(btn3, 4, 2);
    gridLayout->addWidget(btnCommit, 4, 3, 2, 1); // 跨2行

    // 第六行
    gridLayout->addWidget(btnPercent, 5, 0);
    gridLayout->addWidget(btn0, 5, 1);
    gridLayout->addWidget(btnPeriod, 5, 2);

    // 设置列和行的拉伸因子，使按钮均匀分布
    for (int i = 0; i < 4; ++i) {
        gridLayout->setColumnStretch(i, 1);
    }
    for (int i = 0; i < 6; ++i) {
        gridLayout->setRowStretch(i, 1);
    }
}

void MainLayout::setupConnections()
{
    // 连接功能按钮信号
    connect(btnBackspace, &QPushButton::clicked, this, &MainLayout::onBackspaceClicked);
    connect(btnClear, &QPushButton::clicked, this, &MainLayout::onClearClicked);
    connect(btnCommit, &QPushButton::clicked, this, &MainLayout::onCommitClicked);

    // 连接数字按钮信号
    connect(btn0, &QPushButton::clicked, this, &MainLayout::appendNumber);
    connect(btn1, &QPushButton::clicked, this, &MainLayout::appendNumber);
    connect(btn2, &QPushButton::clicked, this, &MainLayout::appendNumber);
    connect(btn3, &QPushButton::clicked, this, &MainLayout::appendNumber);
    connect(btn4, &QPushButton::clicked, this, &MainLayout::appendNumber);
    connect(btn5, &QPushButton::clicked, this, &MainLayout::appendNumber);
    connect(btn6, &QPushButton::clicked, this, &MainLayout::appendNumber);
    connect(btn7, &QPushButton::clicked, this, &MainLayout::appendNumber);
    connect(btn8, &QPushButton::clicked, this, &MainLayout::appendNumber);
    connect(btn9, &QPushButton::clicked, this, &MainLayout::appendNumber);
    connect(btnPercent, &QPushButton::clicked, this, &MainLayout::appendNumber);
    connect(btnPeriod, &QPushButton::clicked, this, &MainLayout::appendNumber);
}

void MainLayout::handleKeyPress(QKeyEvent* event)
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
    case Qt::Key_Percent:  // %号
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
    case Qt::Key_Enter:
    case Qt::Key_Return:
        btnCommit->click();
        break;
    default:
        break;
    }
}

// 核心代码：通信逻辑的实现
void MainLayout::appendNumber()
{
    // 加一个字符
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString text = emit getDisplayTextRequested(); // 请求获取表达式
    emit displayClearRequested(); // 先清空
	emit displaySetRequested(text + button->text()); // 再设置
}

void MainLayout::onBackspaceClicked()
{
    QString text = emit getDisplayTextRequested(); // 请求获取表达式
    // 删除显示框最后一个字符
    if (!text.isEmpty()) {
        text.chop(1);
    }
	emit displayClearRequested(); // 先清空
	emit displaySetRequested(text); // 再设置
}

void MainLayout::onClearClicked()
{
    emit displayClearRequested(); // 使用基类信号
}

void MainLayout::onCommitClicked()
{
    QString s = emit getDisplayTextRequested(); // 请求获取表达式

    // 处理计算
    QString result = "正在开发中";
    emit displaySetRequested(s + result);
}