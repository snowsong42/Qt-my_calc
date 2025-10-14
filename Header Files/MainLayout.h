#pragma once
#include "BaseLayout.h"
#include <QJSEngine>
#include <stack>
#include <map>

class MainLayout : public BaseLayout
{
    Q_OBJECT

public:
    explicit MainLayout(QWidget* parent = nullptr);
    ~MainLayout() override;

public slots:

private slots:
    void appendNumber();
    void onBackspaceClicked();
    void onClearClicked();
    void onCommitClicked() override;
    void onMemoryClear();
    void onMemoryAdd();
    void onMemorySubtract();
    void onMemoryRecall();

private:
    void createWidgets() override;
    void setupLayout() override;
    void setupConnections() override;
    QString evaluateExpression(const QString& expression);
    double getCurrentDisplayValue();
    bool isOperator(QChar c);

    // 数字按钮
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
    QPushButton* btnPercent;
    QPushButton* btnPeriod;

    // 功能按钮
    QPushButton* btnBackspace;
    QPushButton* btnClear;
    QPushButton* btnCommit;

    // 内存按钮
    QPushButton* btnMC;
    QPushButton* btnMplus;
    QPushButton* btnMminus;
    QPushButton* btnMR;

    // 运算按钮
    QPushButton* btnDiv;
    QPushButton* btnMul;
    QPushButton* btnMinus;
    QPushButton* btnPlus;

    // 计算引擎
    QJSEngine jsEngine;

    // 内存值
    double memoryValue;

    // 布局
    QGridLayout* gridLayout;
};