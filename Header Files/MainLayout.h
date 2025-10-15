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
	void onCommitClicked() override; // override,处理等号按钮点击
    void onMemoryClear();
    void onMemoryAdd();
    void onMemorySubtract();
    void onMemoryRecall();

private:
	// 实现基类的纯虚函数
    void createWidgets() override;
    void setupLayout() override;
    void setupConnections() override;
	void cleanup() override;

	// 自身的工具方法
    QString evaluateExpression(const QString& expression);
    double getCurrentDisplayValue();

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