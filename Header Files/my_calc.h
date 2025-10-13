#pragma once
#include "dependences.h"
#include "MainLayout.h"
#include "ScienceLayout.h"
#include "LoanLayout.h"

// 前向声明
class QPushButton;
class QGridLayout;
class QWidget;
class MainLayout;
class ScienceLayout;

class my_calc : public QMainWindow
{
    Q_OBJECT

public:
    explicit my_calc(QWidget* parent = nullptr);
    ~my_calc();

    // 提供对显示框的访问接口
    QLineEdit* getDisplay() const { return displayLineEdit; }
    QWidget* getCentralWidget() const { return centralWidget; }

signals:
    // 布局切换信号
    void layoutSwitchRequested(const QString& layoutName);

public slots:
	void switchToMainLayout(); // 切换到主计算器
	void switchToScienceLayout(); // 切换到科学计算器
    void switchToLoanLayout();  // 切换到贷款计算器

	void showSettings(); // 显示设置对话框
	void updateDisplay(const QString& text); // 更新显示框内容
	void clearDisplay(); // 清空显示框内容
    
protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    void createWidgets();
    void setupConnections();
    void cleanupCurrentLayout();

    // UI控件
    QWidget* centralWidget;

    // 输入输出条，整个项目的核心组件！！！
    QLineEdit* displayLineEdit;

    // 菜单栏子动作
    QAction* mainCalcAction;
    QAction* scienceCalcAction;
    QAction* loanCalcAction;
    QAction* settingsAction;
    QAction* exitAction;
    QAction* aboutAction;

    // 菜单栏
    QMenu* modeMenu;
    QMenu* editMenu;
    QMenu* helpMenu;
    // 工具栏
    QToolBar* mainToolBar;


    // 布局实例
    // HAS-A关系
    MainLayout* mainLayout;
    ScienceLayout* scienceLayout;
    LoanLayout* loanLayout;
    // 当前布局
    QWidget* currentLayout;
};