#include "LoanLayout.h"
#include <cmath>
#include <QButtonGroup>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QGroupBox>
#include <QRadioButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

LoanLayout::LoanLayout(QWidget* parent, QLineEdit* display)
    : QWidget(parent)
    , displayLineEdit(display)
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

    // 创建输入控件
    loanYears = new QComboBox(this);
    for (int i = 1; i <= 30; i++) {
        loanYears->addItem(QString::number(i) + "年");
    }
    loanYears->setCurrentIndex(19); // 默认20年

    loanAmount = new QLineEdit(this);
    loanAmount->setPlaceholderText("输入贷款金额");
    loanAmount->setValidator(new QDoubleValidator(0, 10000, 2, this));

    interestRate = new QLineEdit(this);
    interestRate->setPlaceholderText("输入贷款利率");
    interestRate->setValidator(new QDoubleValidator(0, 20, 2, this));
    interestRate->setText("4.9"); // 默认利率

    // 创建输出类型选择
    outputType = new QComboBox(this);
    outputType->addItem("月均还款");
    outputType->addItem("利息总额");
    outputType->addItem("还款总额");
    outputType->addItem("全部显示");

    // 创建按钮
    btnCalculate = new QPushButton("计算", this);
    btnReset = new QPushButton("重新计算", this);

    // 创建数字按钮（用于快速输入）
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
    btnBackspace = new QPushButton("⌫", this);
    btnClear = new QPushButton("C", this);

    // 创建输出标签和结果显示
    monthlyPaymentLabel = new QLabel("月均还款(元):", this);
    totalInterestLabel = new QLabel("利息总额(元):", this);
    totalPaymentLabel = new QLabel("还款总额(元):", this);

    monthlyPaymentResult = new QLineEdit(this);
    monthlyPaymentResult->setReadOnly(true);
    totalInterestResult = new QLineEdit(this);
    totalInterestResult->setReadOnly(true);
    totalPaymentResult = new QLineEdit(this);
    totalPaymentResult->setReadOnly(true);

    // 设置按钮样式
    QList<QPushButton*> allButtons = findChildren<QPushButton*>();
    for (QPushButton* button : allButtons) {
        button->setMinimumHeight(35);
    }

    btnCalculate->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; }");
    btnReset->setStyleSheet("QPushButton { background-color: #f44336; color: white; }");
}

void LoanLayout::setupLayout()
{
    mainLayout = new QVBoxLayout(this);
    gridLayout = new QGridLayout();

    // 还款方式选择
    QHBoxLayout* repaymentLayout = new QHBoxLayout(repaymentGroup);
    repaymentLayout->addWidget(equalPrincipalAndInterest);
    repaymentLayout->addWidget(equalPrincipal);

    // 输入区域
    int row = 0;
    gridLayout->addWidget(new QLabel("贷款年限(年):", this), row, 0);
    gridLayout->addWidget(loanYears, row, 1);
    gridLayout->addWidget(new QLabel("输出类型:", this), row, 2);
    gridLayout->addWidget(outputType, row, 3);
    row++;

    gridLayout->addWidget(new QLabel("贷款金额(万元):", this), row, 0);
    gridLayout->addWidget(loanAmount, row, 1);
    gridLayout->addWidget(btnCalculate, row, 2);
    gridLayout->addWidget(btnReset, row, 3);
    row++;

    gridLayout->addWidget(new QLabel("贷款利率(%):", this), row, 0);
    gridLayout->addWidget(interestRate, row, 1);
    gridLayout->addWidget(monthlyPaymentLabel, row, 2);
    gridLayout->addWidget(monthlyPaymentResult, row, 3);
    row++;

    // 数字键盘区域
    gridLayout->addWidget(btn1, row, 0);
    gridLayout->addWidget(btn2, row, 1);
    gridLayout->addWidget(btn3, row, 2);
    gridLayout->addWidget(totalInterestLabel, row, 3);
    gridLayout->addWidget(totalInterestResult, row, 4);
    row++;

    gridLayout->addWidget(btn4, row, 0);
    gridLayout->addWidget(btn5, row, 1);
    gridLayout->addWidget(btn6, row, 2);
    gridLayout->addWidget(totalPaymentLabel, row, 3);
    gridLayout->addWidget(totalPaymentResult, row, 4);
    row++;

    gridLayout->addWidget(btn7, row, 0);
    gridLayout->addWidget(btn8, row, 1);
    gridLayout->addWidget(btn9, row, 2);
    gridLayout->addWidget(btnBackspace, row, 3);
    gridLayout->addWidget(btnClear, row, 4);
    row++;

    gridLayout->addWidget(btn0, row, 0, 1, 2); // 跨两列
    gridLayout->addWidget(btnPeriod, row, 2);
    row++;

    // 添加到主布局
    mainLayout->addWidget(repaymentGroup);
    mainLayout->addLayout(gridLayout);

    // 设置布局边距
    mainLayout->setContentsMargins(10, 10, 10, 10);
    gridLayout->setHorizontalSpacing(10);
    gridLayout->setVerticalSpacing(10);
}

void LoanLayout::setupConnections()
{
    // 连接计算按钮
    connect(btnCalculate, &QPushButton::clicked, this, &LoanLayout::calculateLoan);
    connect(btnReset, &QPushButton::clicked, this, &LoanLayout::resetCalculation);

    // 连接输出类型选择
    connect(outputType, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &LoanLayout::updateOutputType);

    // 连接数字按钮
    connect(btn0, &QPushButton::clicked, this, &LoanLayout::appendNumber);
    connect(btn1, &QPushButton::clicked, this, &LoanLayout::appendNumber);
    connect(btn2, &QPushButton::clicked, this, &LoanLayout::appendNumber);
    connect(btn3, &QPushButton::clicked, this, &LoanLayout::appendNumber);
    connect(btn4, &QPushButton::clicked, this, &LoanLayout::appendNumber);
    connect(btn5, &QPushButton::clicked, this, &LoanLayout::appendNumber);
    connect(btn6, &QPushButton::clicked, this, &LoanLayout::appendNumber);
    connect(btn7, &QPushButton::clicked, this, &LoanLayout::appendNumber);
    connect(btn8, &QPushButton::clicked, this, &LoanLayout::appendNumber);
    connect(btn9, &QPushButton::clicked, this, &LoanLayout::appendNumber);
    connect(btnPeriod, &QPushButton::clicked, this, &LoanLayout::appendNumber);
    connect(btnBackspace, &QPushButton::clicked, this, &LoanLayout::onBackspaceClicked);
    connect(btnClear, &QPushButton::clicked, this, &LoanLayout::onClearClicked);
}

void LoanLayout::handleKeyPress(QKeyEvent* event)
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
    case Qt::Key_Backspace: btnBackspace->click(); break;
    case Qt::Key_Delete:
    case Qt::Key_Escape: btnClear->click(); break;
    case Qt::Key_Enter:
    case Qt::Key_Return: btnCalculate->click(); break;
    default: break;
    }
}

void LoanLayout::appendNumber()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        // 判断当前焦点在哪个输入框
        if (loanAmount->hasFocus()) {
            loanAmount->setText(loanAmount->text() + button->text());
        }
        else if (interestRate->hasFocus()) {
            interestRate->setText(interestRate->text() + button->text());
        }
        else {
            emit displayUpdateRequested(button->text());
        }
    }
}

void LoanLayout::onBackspaceClicked()
{
    // 判断当前焦点在哪个输入框
    if (loanAmount->hasFocus()) {
        QString text = loanAmount->text();
        if (!text.isEmpty()) {
            text.chop(1);
            loanAmount->setText(text);
        }
    }
    else if (interestRate->hasFocus()) {
        QString text = interestRate->text();
        if (!text.isEmpty()) {
            text.chop(1);
            interestRate->setText(text);
        }
    }
    else {
        emit displayClearRequested();
    }
}

void LoanLayout::onClearClicked()
{
    // 判断当前焦点在哪个输入框
    if (loanAmount->hasFocus()) {
        loanAmount->clear();
    }
    else if (interestRate->hasFocus()) {
        interestRate->clear();
    }
    else {
        emit displayClearRequested();
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
}

void LoanLayout::calculateEqualPrincipalAndInterest(double amount, double rate, int months)
{
    // 等额本息计算公式
    double monthlyPayment = amount * rate * pow(1 + rate, months) / (pow(1 + rate, months) - 1);
    double totalPayment = monthlyPayment * months;
    double totalInterest = totalPayment - amount;

    // 更新结果显示
    monthlyPaymentResult->setText(QString::number(monthlyPayment, 'f', 2));
    totalInterestResult->setText(QString::number(totalInterest, 'f', 2));
    totalPaymentResult->setText(QString::number(totalPayment, 'f', 2));
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

    // 更新结果显示
    monthlyPaymentResult->setText(QString::number(firstMonthPayment, 'f', 2) + " (首月)");
    totalInterestResult->setText(QString::number(totalInterest, 'f', 2));
    totalPaymentResult->setText(QString::number(totalPayment, 'f', 2));
}

void LoanLayout::resetCalculation()
{
    loanAmount->clear();
    interestRate->setText("4.9");
    loanYears->setCurrentIndex(19); // 重置为20年
    monthlyPaymentResult->clear();
    totalInterestResult->clear();
    totalPaymentResult->clear();
}

void LoanLayout::updateOutputType(int index)
{
    currentOutputType = index;

    // 根据选择的输出类型显示/隐藏相应的输出
    bool showAll = (index == 3); // "全部显示"

    monthlyPaymentLabel->setVisible(showAll || index == 0);
    monthlyPaymentResult->setVisible(showAll || index == 0);

    totalInterestLabel->setVisible(showAll || index == 1);
    totalInterestResult->setVisible(showAll || index == 1);

    totalPaymentLabel->setVisible(showAll || index == 2);
    totalPaymentResult->setVisible(showAll || index == 2);
}