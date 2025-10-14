#pragma once
#include "BaseLayout.h"

class MainLayout : public BaseLayout
{
    Q_OBJECT

public:
    explicit MainLayout(QWidget* parent = nullptr);
    ~MainLayout() override;

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

    // 其他按钮
    QPushButton* btnMC;
    QPushButton* btnMplus;
    QPushButton* btnMminus;
    QPushButton* btnMR;
    QPushButton* btnDiv;
    QPushButton* btnMul;
    QPushButton* btnMinus;
    QPushButton* btnPlus;

    // 布局
    QGridLayout* gridLayout;
};