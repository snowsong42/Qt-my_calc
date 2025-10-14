#pragma once
#include "BaseLayout.h"
#include <QHash>

class ScienceLayout : public BaseLayout
{
    Q_OBJECT

public:
    explicit ScienceLayout(QWidget* parent = nullptr);
    ~ScienceLayout() override;

public slots:
    void handleKeyPress(QKeyEvent* event) override;

private slots:
    void appendNumber();
    void onBackspaceClicked();
    void onClearClicked();
    void onCommitClicked();

private:
    void createWidgets() override;
    void setupLayout() override;
    void setupConnections() override;
    void setupScientificButtons();


    // 基本数字按钮
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

    // 基本运算按钮
    QPushButton* btnPlus;
    QPushButton* btnMinus;
    QPushButton* btnMul;
    QPushButton* btnDiv;
    QPushButton* btnEquals;

    // 功能按钮
    QPushButton* btnClear;
    QPushButton* btnBackspace;
    QPushButton* btnPercent;

    // 科学计算按钮
    QPushButton* btnSecond;    // 2nd
    QPushButton* btnPi;        // π
    QPushButton* btnE;         // e
    QPushButton* btnSquare;    // x²
    QPushButton* btnPower;     // x^y
    QPushButton* btnTenPower;  // 10^x
    QPushButton* btnLog;       // log
    QPushButton* btnLn;        // ln
    QPushButton* btnExp;       // exp
    QPushButton* btnMod;       // mod
    QPushButton* btnLeftParen; // (
    QPushButton* btnRightParen; // )
    QPushButton* btnFactorial; // n!

    // 科学计算函数映射
    QHash<QString, QString> scientificFunctions;
    // 布局
    QGridLayout* gridLayout;
};