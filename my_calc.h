#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

// 前向声明
class QLineEdit;
class QPushButton;
class QGridLayout;
class QWidget;

class my_calc : public QMainWindow
{
    Q_OBJECT

public:
    explicit my_calc(QWidget* parent = nullptr);
    ~my_calc();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void appendNumber();
    void onBackspaceClicked();
    void onClearClicked();
    void onCommitClicked();
    void pop1();
    void pop2();
    void pop3();

private:
    // 创建UI控件
    void createWidgets();
    void createMainLayout();
    void createConnections();

    // 显示控件
    QLineEdit* displayLineEdit;

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
    QWidget* centralWidget;

    // 菜单栏和工具栏
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* helpMenu;
    QToolBar* mainToolBar;

    QAction* myAc1;
    QAction* myAc2;
    QAction* myAc3;
    QAction* exitAction;
    QAction* aboutAction;
};