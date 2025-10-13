#pragma once
#include "dependences.h"

// 前向声明
class QPushButton;
class QGridLayout;
class QLineEdit;
class QRadioButton;
class QComboBox;
class QGroupBox;
class QLabel;

class LoanLayout : public QWidget
{
    Q_OBJECT

public:
    explicit LoanLayout(QWidget* parent = nullptr, QLineEdit* display = nullptr);
    ~LoanLayout();

    // 设置显示框引用
    void setDisplay(QLineEdit* display) { displayLineEdit = display; }

signals:
    // 向主窗口发送的请求信号
    void displayUpdateRequested(const QString& text);
    void displayClearRequested();

public slots:
    void handleKeyPress(QKeyEvent* event);
    void calculateLoan();
    void resetCalculation();
    void updateOutputType(int index);

private slots:
    void appendNumber();
    void onBackspaceClicked();
    void onClearClicked();

private:
    void createWidgets();
    void setupLayout();
    void setupConnections();
    void calculateEqualPrincipalAndInterest(double amount, double rate, int months);  // 等额本息计算
    void calculateEqualPrincipal(double amount, double rate, int months);             // 等额本金计算

    // 显示框引用
    QLineEdit* displayLineEdit;

    // 还款方式选择
    QGroupBox* repaymentGroup;
    QRadioButton* equalPrincipalAndInterest;  // 等额本息
    QRadioButton* equalPrincipal;             // 等额本金

    // 输入控件
    QComboBox* loanYears;        // 贷款年限
    QLineEdit* loanAmount;       // 贷款金额
    QLineEdit* interestRate;     // 贷款利率
    QComboBox* outputType;       // 输出类型选择

    // 按钮
    QPushButton* btnCalculate;
    QPushButton* btnReset;

    // 数字按钮（用于快速输入）
    QPushButton* btn0;
    QPushButton* btn1;
    QPushButton* btn2;
    QPushButton* btn3;
    QPushButton* btn4;
    QPushButton* btn5;
    QPushButton* btn6;
    QPushButton* btn7;
    QPushButton* btn8;
    QPushButton* btn9;
    QPushButton* btnPeriod;
    QPushButton* btnBackspace;
    QPushButton* btnClear;

    // 输出标签
    QLabel* monthlyPaymentLabel;    // 月均还款
    QLabel* totalInterestLabel;     // 利息总额
    QLabel* totalPaymentLabel;      // 还款总额

    QLineEdit* monthlyPaymentResult;
    QLineEdit* totalInterestResult;
    QLineEdit* totalPaymentResult;

    // 布局
    QGridLayout* gridLayout;
    QVBoxLayout* mainLayout;

    // 当前输出类型
    int currentOutputType;
};