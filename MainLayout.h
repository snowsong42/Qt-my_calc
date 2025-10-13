#pragma once
#include "dependences.h"

// 前向声明
class QPushButton;
class QGridLayout;
class QWidget;

class MainLayout : public QWidget
{
    Q_OBJECT

public:
    explicit MainLayout(QWidget* parent = nullptr, QLineEdit* display = nullptr);
    ~MainLayout();

    // 设置显示框引用
    void setDisplay(QLineEdit* display) { displayLineEdit = display; }

signals:
    // 向主窗口发送的请求信号
    void displayUpdateRequested(const QString& text);
    void displayClearRequested();
    void backspaceRequested();

public slots:
    void handleKeyPress(QKeyEvent* event);

private slots:
    void appendNumber();
    void onBackspaceClicked();
    void onClearClicked();
    void onCommitClicked();

private:
    void createWidgets();
    void setupLayout();
    void setupConnections();

    // 显示框引用
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
};