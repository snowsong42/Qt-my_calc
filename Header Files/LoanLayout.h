#pragma once
#include "BaseLayout.h"
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
#include <limits>

class LoanLayout : public BaseLayout
{
    Q_OBJECT

public:
    explicit LoanLayout(QWidget* parent = nullptr);
    ~LoanLayout() override;

public slots:
    void onCommitClicked() override;
    void resetCalculation();
    void updateOutputType(int index);
    void updateCurrencyType(int index);

private:
	// 重写基类的纯虚函数
    void createWidgets() override;
    void setupLayout() override;
    void setupConnections() override;
	void cleanup() override;

    // 自身的工具函数
    void calculateEqualPrincipalAndInterest(double amount, double rate, int months);
    void calculateEqualPrincipal(double amount, double rate, int months);
    void sendResultsToMainDisplay();
    bool validateInputs();
    QString formatCurrency(double value) const;

    // 贷款计算特有控件
    QGroupBox* repaymentGroup;
    QRadioButton* equalPrincipalAndInterest;
    QRadioButton* equalPrincipal;

    QGroupBox* currencyGroup;
    QRadioButton* currencyYuan;
    QRadioButton* currencyWanYuan; // 修正变量名

    QLineEdit* loanYears;
    QLineEdit* loanAmount;
    QLineEdit* interestRate;
    QComboBox* outputType;
    QPushButton* btnReset;
	// btn Commit继承自BaseLayout

    // 存储计算结果
    QString monthlyPaymentStr;
    QString totalInterestStr;
    QString totalPaymentStr;

    QGridLayout* gridLayout;
    QVBoxLayout* mainLayout;
    int currentOutputType;
    bool useYuanOutput; // true=元输出, false=万元输出
};