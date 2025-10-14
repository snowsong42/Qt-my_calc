#include "ScienceLayout.h"
#include <cmath>
#include <QHash>

ScienceLayout::ScienceLayout(QWidget* parent)
    : BaseLayout(parent)
{
    createWidgets();
    setupLayout();
    setupConnections();
    setupScientificButtons();
}

ScienceLayout::~ScienceLayout()
{
    // Qt的对象树会自动管理内存
}

void ScienceLayout::createWidgets()
{
    // 创建基本数字按钮
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
    btnPeriod = new QPushButton(".", this);

    // 创建基本运算按钮
    btnPlus = new QPushButton("+", this);
    btnMinus = new QPushButton("-", this);
    btnMul = new QPushButton("×", this);
    btnDiv = new QPushButton("÷", this);
    btnEquals = new QPushButton("=", this);

    // 创建功能按钮
    btnClear = new QPushButton("C", this);
    btnBackspace = new QPushButton("⌫", this);
    btnPercent = new QPushButton("%", this);

    // 创建科学计算按钮
    btnSecond = new QPushButton("2nd", this);
    btnPi = new QPushButton("π", this);
    btnE = new QPushButton("e", this);
    btnSquare = new QPushButton("x²", this);
    btnPower = new QPushButton("x^y", this);
    btnTenPower = new QPushButton("10^x", this);
    btnLog = new QPushButton("log", this);
    btnLn = new QPushButton("ln", this);
    btnExp = new QPushButton("exp", this);
    btnMod = new QPushButton("mod", this);
    btnLeftParen = new QPushButton("(", this);
    btnRightParen = new QPushButton(")", this);
    btnFactorial = new QPushButton("n!", this);

    // 设置按钮样式
    QList<QPushButton*> allButtons = findChildren<QPushButton*>();
    for (QPushButton* button : allButtons) {
        button->setMinimumHeight(40);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    // 科学计算按钮特殊样式
    btnSecond->setStyleSheet("QPushButton { background-color: #666666; color: white; }");
}

void ScienceLayout::setupLayout()
{
    // 创建主布局 - 7行5列
    gridLayout = new QGridLayout(this);
    gridLayout->setHorizontalSpacing(2);
    gridLayout->setVerticalSpacing(2);
    gridLayout->setContentsMargins(5, 5, 5, 5);

    // 第1行: 2nd, π, e, C, @ (这里用退格代替@)
    gridLayout->addWidget(btnSecond, 0, 0);
    gridLayout->addWidget(btnPi, 0, 1);
    gridLayout->addWidget(btnE, 0, 2);
    gridLayout->addWidget(btnClear, 0, 3);
    gridLayout->addWidget(btnBackspace, 0, 4);

    // 第2行: x², %, HI (这里用mod代替HI), exp, mod
    gridLayout->addWidget(btnSquare, 1, 0);
    gridLayout->addWidget(btnPercent, 1, 1);
    gridLayout->addWidget(btnFactorial, 1, 2); // n! 代替 HI
    gridLayout->addWidget(btnExp, 1, 3);
    gridLayout->addWidget(btnMod, 1, 4);

    // 第3行: %π (这里用左括号代替), (, ), n! (这里用右括号代替), +
    gridLayout->addWidget(btnLeftParen, 2, 0);
    gridLayout->addWidget(btnLeftParen, 2, 1);
    gridLayout->addWidget(btnRightParen, 2, 2);
    gridLayout->addWidget(btnRightParen, 2, 3);
    gridLayout->addWidget(btnPlus, 2, 4);

    // 第4行: x^y, 7, 8, 9, ×
    gridLayout->addWidget(btnPower, 3, 0);
    gridLayout->addWidget(btn7, 3, 1);
    gridLayout->addWidget(btn8, 3, 2);
    gridLayout->addWidget(btn9, 3, 3);
    gridLayout->addWidget(btnMul, 3, 4);

    // 第5行: 10^x, 4, 5, 6, -
    gridLayout->addWidget(btnTenPower, 4, 0);
    gridLayout->addWidget(btn4, 4, 1);
    gridLayout->addWidget(btn5, 4, 2);
    gridLayout->addWidget(btn6, 4, 3);
    gridLayout->addWidget(btnMinus, 4, 4);

    // 第6行: log, 1, 2, 3, +
    gridLayout->addWidget(btnLog, 5, 0);
    gridLayout->addWidget(btn1, 5, 1);
    gridLayout->addWidget(btn2, 5, 2);
    gridLayout->addWidget(btn3, 5, 3);
    gridLayout->addWidget(btnPlus, 5, 4);

    // 第7行: ln, %, 0, ., =
    gridLayout->addWidget(btnLn, 6, 0);
    gridLayout->addWidget(btnPercent, 6, 1);
    gridLayout->addWidget(btn0, 6, 2);
    gridLayout->addWidget(btnPeriod, 6, 3);
    gridLayout->addWidget(btnEquals, 6, 4);
}

void ScienceLayout::setupConnections()
{
    // 连接数字按钮
    connect(btn0, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btn1, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btn2, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btn3, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btn4, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btn5, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btn6, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btn7, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btn8, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btn9, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnPeriod, &QPushButton::clicked, this, &ScienceLayout::appendNumber);

    // 连接基本运算按钮
    connect(btnPlus, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnMinus, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnMul, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnDiv, &QPushButton::clicked, this, &ScienceLayout::appendNumber);

    // 连接功能按钮
    connect(btnBackspace, &QPushButton::clicked, this, &ScienceLayout::onBackspaceClicked);
    connect(btnClear, &QPushButton::clicked, this, &ScienceLayout::onClearClicked);
    connect(btnEquals, &QPushButton::clicked, this, &ScienceLayout::onCommitClicked);

    // 连接括号按钮
    connect(btnLeftParen, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnRightParen, &QPushButton::clicked, this, &ScienceLayout::appendNumber);

    // 连接科学计算按钮
    connect(btnPi, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnE, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnSquare, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnPower, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnTenPower, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnLog, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnLn, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnExp, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnMod, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnFactorial, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnPercent, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
}

void ScienceLayout::setupScientificButtons()
{
    // 设置科学计算函数映射
    scientificFunctions["π"] = "3.141592653589793";
    scientificFunctions["e"] = "2.718281828459045";
    scientificFunctions["x²"] = "²";
    scientificFunctions["x^y"] = "^";
    scientificFunctions["10^x"] = "10^";
    scientificFunctions["log"] = "log(";
    scientificFunctions["ln"] = "ln(";
    scientificFunctions["exp"] = "exp(";
    scientificFunctions["mod"] = "mod";
    scientificFunctions["n!"] = "!";
    scientificFunctions["%"] = "%";
}

void ScienceLayout::handleKeyPress(QKeyEvent* event)
{
    // 处理键盘按键事件
    switch (event->key()) {
    case Qt::Key_0: btn0->click(); break;
    case Qt::Key_1: btn1->click(); break;
    case Qt::Key_2: btn2->click(); break;
    case Qt::Key_3: btn3->click(); break;
    case Qt::Key_4: btn4->click(); break;
    case Qt::Key_5: btn5->click(); break;
    case Qt::Key_6: btn6->click(); break;
    case Qt::Key_7: btn7->click(); break;
    case Qt::Key_8: btn8->click(); break;
    case Qt::Key_9: btn9->click(); break;
    case Qt::Key_Period: btnPeriod->click(); break;
    case Qt::Key_Plus: btnPlus->click(); break;
    case Qt::Key_Minus: btnMinus->click(); break;
    case Qt::Key_Asterisk: btnMul->click(); break;
    case Qt::Key_Slash: btnDiv->click(); break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Equal: btnEquals->click(); break;
    case Qt::Key_Backspace: btnBackspace->click(); break;
    case Qt::Key_Escape: btnClear->click(); break;
    case Qt::Key_ParenLeft: btnLeftParen->click(); break;
    case Qt::Key_ParenRight: btnRightParen->click(); break;
    default: break;
    }
}

void ScienceLayout::appendNumber()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        emit displayUpdateRequested(button->text());
    }
}

void ScienceLayout::onBackspaceClicked()
{
    emit backspaceRequested();
}

void ScienceLayout::onClearClicked()
{
    emit displayClearRequested();
}

void ScienceLayout::onCommitClicked()
{
    QString s = emit getDisplayTextRequested(); // 请求获取表达式

    // 处理计算
    QString result = "正在开发中";
    emit displaySetRequested(s+result);
}