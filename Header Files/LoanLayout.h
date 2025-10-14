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

class LoanLayout : public BaseLayout
{
    Q_OBJECT

public:
    explicit LoanLayout(QWidget* parent = nullptr);
    ~LoanLayout() override;

public slots:
    void handleKeyPress(QKeyEvent* event) override;
    void calculateLoan();
    void resetCalculation();
    void updateOutputType(int index);

private:
    void createWidgets() override;
    void setupLayout() override;
    void setupConnections() override;
    void calculateEqualPrincipalAndInterest(double amount, double rate, int months);
    void calculateEqualPrincipal(double amount, double rate, int months);
    void sendResultsToMainDisplay();

    // 贷款计算特有控件
    QGroupBox* repaymentGroup;
    QRadioButton* equalPrincipalAndInterest;
    QRadioButton* equalPrincipal;
    QComboBox* loanYears;
    QLineEdit* loanAmount;
    QLineEdit* interestRate;
    QComboBox* outputType;
    QPushButton* btnCalculate;
    QPushButton* btnReset;

    // 存储计算结果
    QString monthlyPaymentStr;
    QString totalInterestStr;
    QString totalPaymentStr;

    QGridLayout* gridLayout;
    QVBoxLayout* mainLayout;
    int currentOutputType;
};