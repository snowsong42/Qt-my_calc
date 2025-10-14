#include "LoanLayout.h"

LoanLayout::LoanLayout(QWidget* parent)
    : BaseLayout(parent)
    , currentOutputType(0)
{
    createWidgets();
    setupLayout();
    setupConnections();
}

LoanLayout::~LoanLayout()
{
    // Qt的对象树会自动管理内存
}

void LoanLayout::createWidgets()
{
    // 创建还款方式选择组
    repaymentGroup = new QGroupBox("还款方式", this);
    equalPrincipalAndInterest = new QRadioButton("等额本息", repaymentGroup);
    equalPrincipal = new QRadioButton("等额本金", repaymentGroup);
    equalPrincipalAndInterest->setChecked(true); // 默认选择等额本息

    // 创建输入控件 - 设置固定大小防止过度拉伸
    loanYears = new QComboBox(this);
    loanYears->setMaximumWidth(120); // 限制宽度
    for (int i = 1; i <= 30; i++) {
        loanYears->addItem(QString::number(i) + "年");
    }
    loanYears->setCurrentIndex(19); // 默认20年

    loanAmount = new QLineEdit(this);
    loanAmount->setPlaceholderText("输入贷款金额(万元)");
    loanAmount->setMaximumWidth(150);
    loanAmount->setValidator(new QDoubleValidator(0, 10000, 2, this));

    interestRate = new QLineEdit(this);
    interestRate->setPlaceholderText("输入贷款利率(%)");
    interestRate->setMaximumWidth(150);
    interestRate->setValidator(new QDoubleValidator(0, 20, 2, this));
    interestRate->setText("4.9"); // 默认利率

    // 创建输出类型选择 - 设置固定大小
    outputType = new QComboBox(this);
    outputType->setMaximumWidth(120);
    outputType->addItem("月均还款");
    outputType->addItem("利息总额");
    outputType->addItem("还款总额");
    outputType->addItem("全部显示");

    // 创建按钮
    btnCalculate = new QPushButton("计算", this);
    btnReset = new QPushButton("重置", this);

    // 设置按钮固定大小
    btnCalculate->setFixedSize(80, 35);
    btnReset->setFixedSize(80, 35);

    // 设置按钮样式
    btnCalculate->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; border-radius: 5px; }");
    btnReset->setStyleSheet("QPushButton { background-color: #f44336; color: white; border-radius: 5px; }");
}

void LoanLayout::setupLayout()
{
    mainLayout = new QVBoxLayout(this);
    gridLayout = new QGridLayout();

    // 还款方式选择 - 单独一行
    QHBoxLayout* repaymentLayout = new QHBoxLayout(repaymentGroup);
    repaymentLayout->addWidget(equalPrincipalAndInterest);
    repaymentLayout->addWidget(equalPrincipal);
    repaymentLayout->addStretch(); // 添加弹性空间

    // 输入区域 - 重新组织布局
    int row = 0;

    // 第一行：贷款年限和输出类型
    gridLayout->addWidget(new QLabel("贷款年限:", this), row, 0);
    gridLayout->addWidget(loanYears, row, 1);
    gridLayout->addWidget(new QLabel("输出类型:", this), row, 2);
    gridLayout->addWidget(outputType, row, 3);
    row++;

    // 第二行：贷款金额和贷款利率
    gridLayout->addWidget(new QLabel("贷款金额:", this), row, 0);
    gridLayout->addWidget(loanAmount, row, 1);
    gridLayout->addWidget(new QLabel("贷款利率:", this), row, 2);
    gridLayout->addWidget(interestRate, row, 3);
    row++;

    // 第三行：按钮
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(btnCalculate);
    buttonLayout->addWidget(btnReset);
    buttonLayout->addStretch();

    gridLayout->addLayout(buttonLayout, row, 0, 1, 4); // 跨4列
    row++;

    // 添加到主布局
    mainLayout->addWidget(repaymentGroup);
    mainLayout->addLayout(gridLayout);
    mainLayout->addStretch(); // 添加弹性空间使布局更紧凑

    // 设置布局边距和间距
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(15);
    gridLayout->setHorizontalSpacing(15);
    gridLayout->setVerticalSpacing(15);

    // 设置列宽比例，防止控件过度拉伸
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 2);
    gridLayout->setColumnStretch(2, 1);
    gridLayout->setColumnStretch(3, 2);
}

void LoanLayout::setupConnections()
{
    // 连接计算按钮
    connect(btnCalculate, &QPushButton::clicked, this, &LoanLayout::calculateLoan);
    connect(btnReset, &QPushButton::clicked, this, &LoanLayout::resetCalculation);

    // 连接输出类型选择
    connect(outputType, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &LoanLayout::updateOutputType);
}

void LoanLayout::handleKeyPress(QKeyEvent* event)
{
    // 只处理回车键进行计算
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        btnCalculate->click();
        break;
    default:
        break;
    }
}

void LoanLayout::calculateLoan()
{
    // 获取输入值
    double amount = loanAmount->text().toDouble() * 10000; // 转换为元
    double rate = interestRate->text().toDouble() / 100 / 12; // 年利率转为月利率
    int months = (loanYears->currentIndex() + 1) * 12; // 年转为月

    if (amount <= 0 || rate <= 0 || months <= 0) {
        QMessageBox::warning(this, "输入错误", "请输入有效的贷款参数");
        return;
    }

    // 根据还款方式计算
    if (equalPrincipalAndInterest->isChecked()) {
        calculateEqualPrincipalAndInterest(amount, rate, months);
    }
    else {
        calculateEqualPrincipal(amount, rate, months);
    }

    // 发送结果到主界面显示
    sendResultsToMainDisplay();
}

void LoanLayout::calculateEqualPrincipalAndInterest(double amount, double rate, int months)
{
    // 等额本息计算公式
    double monthlyPayment = amount * rate * pow(1 + rate, months) / (pow(1 + rate, months) - 1);
    double totalPayment = monthlyPayment * months;
    double totalInterest = totalPayment - amount;

    // 存储计算结果
    monthlyPaymentStr = QString::number(monthlyPayment, 'f', 2);
    totalInterestStr = QString::number(totalInterest, 'f', 2);
    totalPaymentStr = QString::number(totalPayment, 'f', 2);
}

void LoanLayout::calculateEqualPrincipal(double amount, double rate, int months)
{
    // 等额本金计算公式
    double principalPerMonth = amount / months; // 每月本金
    double totalInterest = 0;

    for (int i = 0; i < months; i++) {
        double monthlyInterest = (amount - i * principalPerMonth) * rate;
        totalInterest += monthlyInterest;
    }

    double firstMonthPayment = principalPerMonth + amount * rate;
    double totalPayment = amount + totalInterest;

    // 存储计算结果
    monthlyPaymentStr = QString::number(firstMonthPayment, 'f', 2) + " (首月)";
    totalInterestStr = QString::number(totalInterest, 'f', 2);
    totalPaymentStr = QString::number(totalPayment, 'f', 2);
}

// 根据当前选择的输出类型发送结果到主界面
void LoanLayout::sendResultsToMainDisplay()
{
    QString resultText;

    switch (currentOutputType) {
    case 0: // 月均还款
        resultText = "月均还款: " + monthlyPaymentStr + " 元";
        break;
    case 1: // 利息总额
        resultText = "利息总额: " + totalInterestStr + " 元";
        break;
    case 2: // 还款总额
        resultText = "还款总额: " + totalPaymentStr + " 元";
        break;
    case 3: // 全部显示
        resultText = "月均还款: " + monthlyPaymentStr + " 元\n" +
            "利息总额: " + totalInterestStr + " 元\n" +
            "还款总额: " + totalPaymentStr + " 元";
        break;
    default:
        resultText = "月均还款: " + monthlyPaymentStr + " 元\n" +
            "利息总额: " + totalInterestStr + " 元\n" +
            "还款总额: " + totalPaymentStr + " 元";
        break;
    }

    // 通过信号发送结果到主界面
    emit displaySetRequested(resultText);
}

void LoanLayout::resetCalculation()
{
    loanAmount->clear();
    interestRate->setText("4.9");
    loanYears->setCurrentIndex(19); // 重置为20年

    // 清空存储的结果
    monthlyPaymentStr.clear();
    totalInterestStr.clear();
    totalPaymentStr.clear();

    // 发送清空信号到主界面
    emit displayClearRequested();
}

void LoanLayout::updateOutputType(int index)
{
    currentOutputType = index;

    // 如果有计算结果，立即更新显示
    if (!monthlyPaymentStr.isEmpty()) {
        sendResultsToMainDisplay();
    }
}