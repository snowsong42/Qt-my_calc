#include "LoanLayout.h"
#include <cmath>
#include <limits>

LoanLayout::LoanLayout(QWidget* parent)
    : BaseLayout(parent)
    , currentOutputType(0)
    , useYuanOutput(false) // 默认万元输出
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

    // 创建输出货币单位选择组
    currencyGroup = new QGroupBox("输出单位", this);
    currencyYuan = new QRadioButton("元", currencyGroup);
    currencyWanYuan = new QRadioButton("万元", currencyGroup);
    currencyWanYuan->setChecked(true); // 默认选择万元输出

    // 创建输入控件
    loanYears = new QLineEdit(this);
    loanYears->setPlaceholderText("1-30年");
    loanYears->setValidator(new QIntValidator(1, 30, this));
    loanYears->setText("20"); // 默认20年

    loanAmount = new QLineEdit(this);
    loanAmount->setPlaceholderText("贷款金额");
    loanAmount->setValidator(new QDoubleValidator(0, 10000, 2, this));

    interestRate = new QLineEdit(this);
    interestRate->setPlaceholderText("贷款利率");
    interestRate->setValidator(new QDoubleValidator(0, 100, 2, this));
    interestRate->setText("4.9"); // 默认利率

    // 创建输出类型选择在这里设置尺寸
    outputType = new QComboBox(this);
    outputType->setMinimumHeight(15);
    outputType->addItem("月均还款");
    outputType->addItem("利息总额");
    outputType->addItem("还款总额");
    outputType->addItem("全部显示");

    // 创建按钮
    btnCalculate = new QPushButton("计算", this);
    btnReset = new QPushButton("重置", this);

    // 设置按钮样式
    btnCalculate->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border-radius: 5px;"
        "    padding: 12px 40px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #3d8b40; }"
    );

    btnReset->setStyleSheet(
        "QPushButton {"
        "    background-color: #f44336;"
        "    color: white;"
        "    border-radius: 5px;"
        "    padding: 12px 40px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover { background-color: #da190b; }"
        "QPushButton:pressed { background-color: #b71508; }"
    );

    // 设置输入框样式 - 使用深色文字
    QString inputStyle =
        "QLineEdit {"
        "    padding: 6px 8px;"           // 减小内边距
        "    border: 1px solid #ddd;"     // 减小边框宽度
        "    border-radius: 4px;"         // 减小圆角
        "    font-size: 13px;"            // 减小字体
        "    min-height: 25px;"           // 设置最小高度
        "}"
        "QLineEdit:focus {"
        "    border-color: #3498db;"
        "}";

    loanYears->setStyleSheet(inputStyle);
    loanAmount->setStyleSheet(inputStyle);
    interestRate->setStyleSheet(inputStyle);

    // 设置下拉框样式
    outputType->setStyleSheet(
        "QComboBox {"
        "    padding: 8px 12px;"
        "    border: 2px solid #ddd;"
        "    border-radius: 6px;"
        "    min-height: 15px;"           // 增大最小高度
        "    font-size: 14px;"            // 保持较大字体
        "}"
        "QComboBox:focus {"
        "    border-color: #3498db;"
        "}"
        "QComboBox::drop-down {"
        "    border: none;"
        "    width: 30px;"
        "}"
        "QComboBox::down-arrow {"
        "    image: none;"
        "    border-left: 5px solid transparent;"
        "    border-right: 5px solid transparent;"
        "    border-top: 5px solid #7f8c8d;"
        "    width: 0px;"
        "    height: 0px;"
        "}"
        "QComboBox QAbstractItemView {"
        "    border: 1px solid #ddd;"
        "    border-radius: 4px;"
        "    selection-background-color: #3498db;"
        "    outline: none;"
        "    min-height: 30px;"           // 下拉项最小高度
        "}"
    );

    // 设置单选按钮样式
}

void LoanLayout::setupLayout()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(12);
    mainLayout->setContentsMargins(18, 18, 18, 18);

    // 还款方式选择
    QHBoxLayout* repaymentLayout = new QHBoxLayout(repaymentGroup);
    repaymentLayout->addWidget(equalPrincipalAndInterest);
    repaymentLayout->addWidget(equalPrincipal);
    repaymentLayout->addStretch();

    // 输出货币单位选择
    QHBoxLayout* currencyLayout = new QHBoxLayout(currencyGroup);
    currencyLayout->addWidget(currencyYuan);
    currencyLayout->addWidget(currencyWanYuan); // 修正变量名
    currencyLayout->addStretch();

    // 创建输入区域网格布局
    gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(15);
    gridLayout->setVerticalSpacing(15);

    int row = 0;

    // 第一行：贷款年限
    QLabel* yearsLabel = new QLabel("贷款年限 (年)", this);
    yearsLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    gridLayout->addWidget(yearsLabel, row, 0);
    gridLayout->addWidget(loanYears, row, 1);
    row++;

    // 第二行：贷款金额
    QLabel* amountLabel = new QLabel("贷款金额 (万元)", this);
    amountLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    gridLayout->addWidget(amountLabel, row, 0);
    gridLayout->addWidget(loanAmount, row, 1);
    row++;

    // 第三行：贷款利率
    QLabel* rateLabel = new QLabel("贷款利率 (%)", this);
    rateLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    gridLayout->addWidget(rateLabel, row, 0);
    gridLayout->addWidget(interestRate, row, 1);
    row++;

    // 第四行：输出类型
    QLabel* outputLabel = new QLabel("输出类型", this);
    outputLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    gridLayout->addWidget(outputLabel, row, 0);
    gridLayout->addWidget(outputType, row, 1);
    row++;

    /// 第五行：按钮
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(btnCalculate);
    buttonLayout->addSpacing(80);  // 添加80像素的间距
    buttonLayout->addWidget(btnReset);
    buttonLayout->addStretch();

    gridLayout->addLayout(buttonLayout, row, 0, 1, 2);
    row++;

    // 设置列比例
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 2);

    // 添加到主布局
    mainLayout->addWidget(repaymentGroup);
    mainLayout->addWidget(currencyGroup);
    mainLayout->addLayout(gridLayout);
    mainLayout->addStretch();
}

void LoanLayout::setupConnections()
{
    // 连接计算按钮
    connect(btnCalculate, &QPushButton::clicked, this, &LoanLayout::onCommitClicked);
    connect(btnReset, &QPushButton::clicked, this, &LoanLayout::resetCalculation);

    // 连接输出类型选择
    connect(outputType, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &LoanLayout::updateOutputType);

    // 连接货币单位选择
    connect(currencyYuan, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) {
            updateCurrencyType(0);
        }
        });
    connect(currencyWanYuan, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) {
            updateCurrencyType(1);
        }
        });

    // 新增：连接还款方式选择
    connect(equalPrincipalAndInterest, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked && !monthlyPaymentStr.isEmpty()) {
            // 如果有计算结果，立即重新计算并更新显示
            onCommitClicked();
        }
        });
    connect(equalPrincipal, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked && !monthlyPaymentStr.isEmpty()) {
            // 如果有计算结果，立即重新计算并更新显示
            onCommitClicked();
        }
        });
}
bool LoanLayout::validateInputs()
{
    // 检查贷款年限
    if (loanYears->text().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入贷款年限");
        loanYears->setFocus();
        return false;
    }

    int years = loanYears->text().toInt();
    if (years < 1 || years > 30) {
        QMessageBox::warning(this, "输入错误", "贷款年限必须在1-30年之间");
        loanYears->setFocus();
        return false;
    }

    // 检查贷款金额
    if (loanAmount->text().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入贷款金额");
        loanAmount->setFocus();
        return false;
    }

    double amount = loanAmount->text().toDouble();
    if (amount <= 0) {
        QMessageBox::warning(this, "输入错误", "贷款金额必须大于0");
        loanAmount->setFocus();
        return false;
    }

    // 检查贷款利率
    if (interestRate->text().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入贷款利率");
        interestRate->setFocus();
        return false;
    }

    double rate = interestRate->text().toDouble();
    if (rate <= 0 || rate > 100) {
        QMessageBox::warning(this, "输入错误", "贷款利率必须在0-100%之间");
        interestRate->setFocus();
        return false;
    }

    return true;
}

void LoanLayout::onCommitClicked()
{
    if (!validateInputs()) {
        return;
    }

    // 获取输入值 - 输入统一为万元
    double amount = loanAmount->text().toDouble() * 10000; // 输入万元转换为元

    double rate = interestRate->text().toDouble() / 100 / 12; // 年利率转为月利率
    int months = loanYears->text().toInt() * 12; // 年转为月

    // 检查数据溢出
    if (amount > std::numeric_limits<double>::max() / 1000) {
        QMessageBox::warning(this, "计算错误", "贷款金额过大，无法计算");
        return;
    }

    if (rate > 1.0) {
        QMessageBox::warning(this, "计算错误", "利率过高，无法计算");
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
    try {
        // 等额本息计算公式
        if (rate == 0) {
            // 零利率情况
            double monthlyPayment = amount / months;
            double totalPayment = amount;
            double totalInterest = 0;

            monthlyPaymentStr = formatCurrency(monthlyPayment);
            totalInterestStr = formatCurrency(totalInterest);
            totalPaymentStr = formatCurrency(totalPayment);
            return;
        }

        double temp = pow(1 + rate, months);
        if (std::isinf(temp) || std::isnan(temp)) {
            throw std::overflow_error("计算溢出");
        }

        double monthlyPayment = amount * rate * temp / (temp - 1);
        double totalPayment = monthlyPayment * months;
        double totalInterest = totalPayment - amount;

        // 检查结果是否有效
        if (std::isinf(monthlyPayment) || std::isnan(monthlyPayment) ||
            std::isinf(totalPayment) || std::isnan(totalPayment)) {
            throw std::overflow_error("计算结果溢出");
        }

        // 存储计算结果
        monthlyPaymentStr = formatCurrency(monthlyPayment);
        totalInterestStr = formatCurrency(totalInterest);
        totalPaymentStr = formatCurrency(totalPayment);
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "计算错误", QString("计算过程中发生错误: %1").arg(e.what()));
        monthlyPaymentStr = "计算错误";
        totalInterestStr = "计算错误";
        totalPaymentStr = "计算错误";
    }
}

void LoanLayout::calculateEqualPrincipal(double amount, double rate, int months)
{
    try {
        // 等额本金计算公式
        double principalPerMonth = amount / months;
        double totalInterest = 0;

        for (int i = 0; i < months; i++) {
            double monthlyInterest = (amount - i * principalPerMonth) * rate;
            if (std::isinf(totalInterest + monthlyInterest) || std::isnan(totalInterest + monthlyInterest)) {
                throw std::overflow_error("利息计算溢出");
            }
            totalInterest += monthlyInterest;
        }

        double firstMonthPayment = principalPerMonth + amount * rate;
        double totalPayment = amount + totalInterest;

        // 检查结果是否有效
        if (std::isinf(firstMonthPayment) || std::isnan(firstMonthPayment) ||
            std::isinf(totalPayment) || std::isnan(totalPayment)) {
            throw std::overflow_error("计算结果溢出");
        }

        // 存储计算结果
        monthlyPaymentStr = formatCurrency(firstMonthPayment) + " (首月)";
        totalInterestStr = formatCurrency(totalInterest);
        totalPaymentStr = formatCurrency(totalPayment);
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "计算错误", QString("计算过程中发生错误: %1").arg(e.what()));
        monthlyPaymentStr = "计算错误";
        totalInterestStr = "计算错误";
        totalPaymentStr = "计算错误";
    }
}

QString LoanLayout::formatCurrency(double value) const
{
    if (std::isinf(value) || std::isnan(value)) {
        return "无效数值";
    }

    if (useYuanOutput) {
        // 显示为元，添加千位分隔符
        QString yuanStr = QString::number(value, 'f', 2);

        // 添加千位分隔符
        int dotIndex = yuanStr.indexOf('.');
        QString integerPart = dotIndex >= 0 ? yuanStr.left(dotIndex) : yuanStr;
        QString decimalPart = dotIndex >= 0 ? yuanStr.mid(dotIndex) : "";

        for (int i = integerPart.length() - 3; i > 0; i -= 3) {
            integerPart.insert(i, ',');
        }

        return integerPart + decimalPart + "元";
    }
    else {
        // 显示为万元
        double wanValue = value / 10000;
        if (wanValue >= 10000) {
            return QString::number(wanValue / 10000, 'f', 2) + "亿元";
        }
        else {
            return QString::number(wanValue, 'f', 2) + "万元";
        }
    }
}

void LoanLayout::sendResultsToMainDisplay()
{
    QString resultText;

    switch (currentOutputType) {
    case 0: // 月均还款
        resultText = "月均还款: " + monthlyPaymentStr;
        break;
    case 1: // 利息总额
        resultText = "利息总额: " + totalInterestStr;
        break;
    case 2: // 还款总额
        resultText = "还款总额: " + totalPaymentStr;
        break;
    case 3: // 全部显示
        resultText = "月均还款: " + monthlyPaymentStr + "\n" +
            "利息总额: " + totalInterestStr + "\n" +
            "还款总额: " + totalPaymentStr;
        break;
    default:
        resultText = "计算结果:\n月均还款: " + monthlyPaymentStr + "\n" +
            "利息总额: " + totalInterestStr + "\n" +
            "还款总额: " + totalPaymentStr;
        break;
    }

    // 通过信号发送结果到主界面
    emit displaySetRequested(resultText);
}

void LoanLayout::resetCalculation()
{
    loanYears->setText("20");
    loanAmount->clear();
    interestRate->setText("4.9");

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

    // 如果有计算结果，立即更新显示（不重新计算）
    if (!monthlyPaymentStr.isEmpty()) {
        sendResultsToMainDisplay();
    }
}

void LoanLayout::updateCurrencyType(int index)
{
    useYuanOutput = (index == 0); // 0=元输出, 1=万元输出

    // 如果有计算结果，立即重新计算并更新显示
    if (!monthlyPaymentStr.isEmpty()) {
        onCommitClicked();  // 重新计算并更新显示
    }
}