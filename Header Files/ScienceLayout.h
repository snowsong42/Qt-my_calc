#pragma once
#include "BaseLayout.h"
#include <QHash>
#include <QtQml/QJSEngine>
#include <cmath>

class ScienceLayout : public BaseLayout
{
    Q_OBJECT

public:
    explicit ScienceLayout(QWidget* parent = nullptr);
    ~ScienceLayout() override;

public slots:
	// 直接继承基类的KeyPress处理

private slots:
	void onCommitClicked() override; // override处理等号按钮点击
    void onFunctionClicked(); // 处理函数按钮点击

private:
    // 实现基类的纯虚函数
    void createWidgets() override;
    void setupLayout() override;
    void setupConnections() override;
	void cleanup() override;

	// 自身的工具方法
    QString evaluateExpression(const QString& expression);
    double factorial(double n);
    double degreesToRadians(double degrees);

	// 基本数字按钮继承自BaseLayout
    // 功能按钮继承自BaseLayout
    
    // 基本运算按钮
    QPushButton* btnPlus;
    QPushButton* btnMinus;
    QPushButton* btnMul;
    QPushButton* btnDiv;

    // 科学计算按钮
    QPushButton* btnPi;        // π
    QPushButton* btnE;         // e
    QPushButton* btnSin;       // sin
    QPushButton* btnCos;       // cos
    QPushButton* btnTan;       // tan
    QPushButton* btnSqrt;      // √
    QPushButton* btnReciprocal; // 1/x
    QPushButton* btnPower;     // ^
    QPushButton* btnMod;       // mod
    QPushButton* btnLn;        // ln
    QPushButton* btnLog;       // log
    QPushButton* btnExp;       // exp

    // JavaScript引擎用于计算表达式
    QJSEngine jsEngine;

    // 布局
    QGridLayout* gridLayout;
};