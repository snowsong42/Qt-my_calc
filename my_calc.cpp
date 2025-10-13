#include "my_calc.h"

my_calc::my_calc(QWidget* parent)
    : QMainWindow(parent)
{
    // 设置窗口属性
    setWindowTitle("计算器");
    setFixedSize(476, 570);

    // 创建控件和布局
    createWidgets();
    createMainLayout();
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

    // 创建文件菜单动作
    myAc1 = new QAction("新建", this);
    myAc1->setStatusTip("创建新的计算");
    myAc1->setShortcut(QKeySequence::New);

    myAc2 = new QAction("打开", this);
    myAc2->setStatusTip("打开保存的计算");
    myAc2->setShortcut(QKeySequence::Open);

    exitAction = new QAction("退出", this);
    exitAction->setStatusTip("退出应用程序");
    exitAction->setShortcut(QKeySequence::Quit);

    // 创建编辑菜单动作
    myAc3 = new QAction("设置", this);
    myAc3->setStatusTip("应用程序设置");
    myAc3->setShortcut(QKeySequence("Ctrl+P"));

    // 创建帮助菜单动作
    aboutAction = new QAction("关于", this);
    aboutAction->setStatusTip("关于此应用程序");

    // 创建文件菜单
    fileMenu = menuBar()->addMenu("文件");
    fileMenu->addAction(myAc1);
    fileMenu->addAction(myAc2);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // 创建编辑菜单
    editMenu = menuBar()->addMenu("编辑");
    editMenu->addAction(myAc3);

    // 创建帮助菜单
    helpMenu = menuBar()->addMenu("帮助");
    helpMenu->addAction(aboutAction);

    // 创建工具栏
    mainToolBar = addToolBar("主工具栏");
    mainToolBar->addAction(myAc1);
    mainToolBar->addAction(myAc2);
    mainToolBar->addSeparator();
    mainToolBar->addAction(myAc3);

    // 连接信号和槽
    connect(myAc1, &QAction::triggered, this, &my_calc::pop1);
    connect(myAc2, &QAction::triggered, this, &my_calc::pop2);
    connect(myAc3, &QAction::triggered, this, &my_calc::pop3);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "关于计算器",
            "这是一个基于Qt的计算器应用程序\n"
            "版本 1.0\n"
            "使用纯代码实现");
        });
}

void my_calc::createMainLayout()
{
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

void my_calc::pop1()
{
    QMessageBox::information(this, "新建", "创建新的计算会话", QMessageBox::Ok);
}

void my_calc::pop2()
{
    QMessageBox::information(this, "打开", "打开保存的计算文件", QMessageBox::Ok);
}

void my_calc::pop3()
{
    QMessageBox::information(this, "设置", "打开应用程序设置", QMessageBox::Ok);
}