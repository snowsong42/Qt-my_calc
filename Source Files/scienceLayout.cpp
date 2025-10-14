#include "ScienceLayout.h"

ScienceLayout::ScienceLayout(QWidget* parent)
    : BaseLayout(parent)
{
    createWidgets();
    setupLayout();
    setupConnections();
}

ScienceLayout::~ScienceLayout()
{
	cleanup();
}

void ScienceLayout::cleanup()
{
    // 删除所有按钮
    QList<QPushButton*> allButtons = findChildren<QPushButton*>();
    for (QPushButton* button : allButtons) {
        delete button;
    }
    allButtons.clear();
    // 删除布局
    if (gridLayout) {
        delete gridLayout;
        gridLayout = nullptr;
    }
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

    // 创建科学计算按钮
    btnPi = new QPushButton("π", this);
    btnE = new QPushButton("e", this);
    btnSin = new QPushButton("sin", this);
    btnCos = new QPushButton("cos", this);
    btnTan = new QPushButton("tan", this);
    btnSqrt = new QPushButton("√", this);
    btnReciprocal = new QPushButton("1/x", this);
    btnPower = new QPushButton("^", this);
    btnMod = new QPushButton("mod", this);
    btnLn = new QPushButton("ln", this);
    btnLog = new QPushButton("log", this);
    btnExp = new QPushButton("exp", this);

    // 设置按钮样式 - 更小的按钮
    QList<QPushButton*> allButtons = findChildren<QPushButton*>();
    for (QPushButton* button : allButtons) {
        setupButtonStyle(button);
        button->setMinimumSize(45, 45);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    // 特殊按钮样式
    btnEquals->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; }");
    btnClear->setStyleSheet("QPushButton { background-color: #f44336; color: white; }");
    btnBackspace->setStyleSheet("QPushButton { background-color: #ff9800; color: white; }");

    // 科学函数按钮样式
    QString scientificStyle = "QPushButton { background-color: #2196F3; color: white; }";
    btnSin->setStyleSheet(scientificStyle);
    btnCos->setStyleSheet(scientificStyle);
    btnTan->setStyleSheet(scientificStyle);
    btnSqrt->setStyleSheet(scientificStyle);
    btnReciprocal->setStyleSheet(scientificStyle);
    btnLn->setStyleSheet(scientificStyle);
    btnLog->setStyleSheet(scientificStyle);
    btnExp->setStyleSheet(scientificStyle);
    btnPi->setStyleSheet(scientificStyle);
    btnE->setStyleSheet(scientificStyle);
    btnPower->setStyleSheet(scientificStyle);
    btnMod->setStyleSheet(scientificStyle);
}

void ScienceLayout::setupLayout()
{
    // 创建主布局 - 6行5列
    gridLayout = new QGridLayout(this);
    gridLayout->setHorizontalSpacing(5);
    gridLayout->setVerticalSpacing(5);
    gridLayout->setContentsMargins(10, 10, 10, 10);

    // 第0行: e, π, sin, C, ⌫
    gridLayout->addWidget(btnE, 0, 0);
    gridLayout->addWidget(btnPi, 0, 1);
    gridLayout->addWidget(btnSin, 0, 2);
    gridLayout->addWidget(btnClear, 0, 3);
    gridLayout->addWidget(btnBackspace, 0, 4);

    // 第1行: cos, tan, √, 1/x, ^
    gridLayout->addWidget(btnCos, 1, 0);
    gridLayout->addWidget(btnTan, 1, 1);
    gridLayout->addWidget(btnSqrt, 1, 2);
    gridLayout->addWidget(btnReciprocal, 1, 3);
    gridLayout->addWidget(btnPower, 1, 4);

    // 第2行: 7, 8, 9, +, mod
    gridLayout->addWidget(btn7, 2, 0);
    gridLayout->addWidget(btn8, 2, 1);
    gridLayout->addWidget(btn9, 2, 2);
    gridLayout->addWidget(btnPlus, 2, 3);
    gridLayout->addWidget(btnMod, 2, 4);

    // 第3行: 4, 5, 6, -, ln
    gridLayout->addWidget(btn4, 3, 0);
    gridLayout->addWidget(btn5, 3, 1);
    gridLayout->addWidget(btn6, 3, 2);
    gridLayout->addWidget(btnMinus, 3, 3);
    gridLayout->addWidget(btnLn, 3, 4);

    // 第4行: 1, 2, 3, ×, log
    gridLayout->addWidget(btn1, 4, 0);
    gridLayout->addWidget(btn2, 4, 1);
    gridLayout->addWidget(btn3, 4, 2);
    gridLayout->addWidget(btnMul, 4, 3);
    gridLayout->addWidget(btnLog, 4, 4);

    // 第5行: ., 0, =, ÷, exp
    gridLayout->addWidget(btnPeriod, 5, 0);
    gridLayout->addWidget(btn0, 5, 1);
    gridLayout->addWidget(btnEquals, 5, 2);
    gridLayout->addWidget(btnDiv, 5, 3);
    gridLayout->addWidget(btnExp, 5, 4);

    // 设置列和行的拉伸因子，使按钮均匀分布
    for (int i = 0; i < 5; ++i) {
        gridLayout->setColumnStretch(i, 1);
    }
    for (int i = 0; i < 6; ++i) {
        gridLayout->setRowStretch(i, 1);
    }
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
    connect(btnPower, &QPushButton::clicked, this, &ScienceLayout::appendNumber);
    connect(btnMod, &QPushButton::clicked, this, &ScienceLayout::appendNumber);

    // 连接功能按钮
    connect(btnBackspace, &QPushButton::clicked, this, &ScienceLayout::onBackspaceClicked);
    connect(btnClear, &QPushButton::clicked, this, &ScienceLayout::onClearClicked);
    connect(btnEquals, &QPushButton::clicked, this, &ScienceLayout::onCommitClicked);

    // 连接科学计算按钮
    connect(btnPi, &QPushButton::clicked, this, &ScienceLayout::onFunctionClicked);
    connect(btnE, &QPushButton::clicked, this, &ScienceLayout::onFunctionClicked);
    connect(btnSin, &QPushButton::clicked, this, &ScienceLayout::onFunctionClicked);
    connect(btnCos, &QPushButton::clicked, this, &ScienceLayout::onFunctionClicked);
    connect(btnTan, &QPushButton::clicked, this, &ScienceLayout::onFunctionClicked);
    connect(btnSqrt, &QPushButton::clicked, this, &ScienceLayout::onFunctionClicked);
    connect(btnReciprocal, &QPushButton::clicked, this, &ScienceLayout::onFunctionClicked);
    connect(btnLn, &QPushButton::clicked, this, &ScienceLayout::onFunctionClicked);
    connect(btnLog, &QPushButton::clicked, this, &ScienceLayout::onFunctionClicked);
    connect(btnExp, &QPushButton::clicked, this, &ScienceLayout::onFunctionClicked);
}

void ScienceLayout::appendNumber()
{
    // 加一个字符
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString text = emit getDisplayTextRequested(); // 请求获取表达式
    emit displaySetRequested(text + button->text());
}

void ScienceLayout::onFunctionClicked()
{
    // 处理函数按钮点击
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString text = emit getDisplayTextRequested(); // 请求获取表达式

    QString functionText;
    QString buttonText = button->text();

    // 处理特殊函数格式
    if (buttonText == "π") {
        functionText = "3.141592653589793";
    }
    else if (buttonText == "e") {
        functionText = "2.718281828459045";
    }
    else if (buttonText == "√") {
        functionText = "sqrt(";
    }
    else if (buttonText == "1/x") {
        // 先计算当前值，然后取倒数
        QString currentText = emit getDisplayTextRequested();
        if (!currentText.isEmpty()) {
            try {
                double value = currentText.toDouble();
                if (value != 0) {
                    double result = 1.0 / value;
                    emit displaySetRequested(QString::number(result, 'g', 10));
                }
                else {
                    emit displaySetRequested("错误: 除零");
                }
                return;
            }
            catch (...) {
                emit displaySetRequested("错误: 无效输入");
                return;
            }
        }
        functionText = "1/";
    }
    else if (buttonText == "sin" || buttonText == "cos" || buttonText == "tan") {
        functionText = buttonText + "(";
    }
    else if (buttonText == "ln") {
        functionText = "log("; // 自然对数
    }
    else if (buttonText == "log") {
        functionText = "log10("; // 常用对数
    }
    else if (buttonText == "exp") {
        functionText = "exp(";
    }
    else {
        functionText = buttonText;
    }

    emit displaySetRequested(text + functionText);
}

void ScienceLayout::onBackspaceClicked()
{
    QString text = emit getDisplayTextRequested(); // 请求获取表达式
    // 删除显示框最后一个字符
    if (!text.isEmpty()) {
        text.chop(1);
    }
    emit displaySetRequested(text);
}

void ScienceLayout::onClearClicked()
{
    emit displayClearRequested();
}

void ScienceLayout::onCommitClicked()
{
    QString expression = emit getDisplayTextRequested(); // 请求获取表达式

    if (expression.isEmpty()) {
        return;
    }

    QString result = evaluateExpression(expression);
    emit displaySetRequested(result);
}

QString ScienceLayout::evaluateExpression(const QString& expression)
{
    try {
        // 预处理表达式，替换特殊符号
        QString processedExpr = expression;

        // 替换数学符号
        processedExpr.replace("×", "*");
        processedExpr.replace("÷", "/");
        processedExpr.replace("π", "3.141592653589793");
        processedExpr.replace("e", "2.718281828459045");

        // 处理科学函数
        processedExpr.replace("sin(", "Math.sin(");
        processedExpr.replace("cos(", "Math.cos(");
        processedExpr.replace("tan(", "Math.tan(");
        processedExpr.replace("sqrt(", "Math.sqrt(");
        processedExpr.replace("log(", "Math.log(");  // 自然对数
        processedExpr.replace("log10(", "Math.log10("); // 常用对数
        processedExpr.replace("exp(", "Math.exp(");

        // 处理mod运算
        int modIndex;
        while ((modIndex = processedExpr.indexOf("mod")) != -1) {
            // 简单的mod处理，找到前后的数字
            // 这只是一个简单实现，完整的表达式解析需要更复杂的逻辑
            processedExpr.replace(modIndex, 3, "%");
        }

        // 使用QJSEngine计算表达式
        QJSValue result = jsEngine.evaluate(processedExpr);

        if (result.isError()) {
            return "错误: " + result.toString();
        }

        double value = result.toNumber();

        // 处理特殊值
        if (std::isinf(value)) {
            return "错误: 无穷大";
        }
        if (std::isnan(value)) {
            return "错误: 非数字";
        }

        // 格式化输出
        if (qAbs(value) < 1e-10) value = 0; // 处理浮点误差

        return QString::number(value, 'g', 10);

    }
    catch (const std::exception& e) {
        return QString("错误: %1").arg(e.what());
    }
    catch (...) {
        return "错误: 计算失败";
    }
}

double ScienceLayout::factorial(double n)
{
    if (n < 0 || std::floor(n) != n) {
        return std::numeric_limits<double>::quiet_NaN(); // 非整数或负数阶乘未定义
    }

    double result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double ScienceLayout::degreesToRadians(double degrees)
{
    return degrees * M_PI / 180.0;
}