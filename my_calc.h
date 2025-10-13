#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    // 创建UI控件
    void createWidgets();
    void createLayout();
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

    // 其他按钮（在UI中存在但代码中未使用的）
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
};

#endif