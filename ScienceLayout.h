#pragma once
#include "dependences.h"

// 前向声明
class QPushButton;
class QGridLayout;
class QWidget;

class ScienceLayout : public QWidget
{
    Q_OBJECT

public:
    explicit ScienceLayout(QWidget* parent = nullptr, QLineEdit* display = nullptr);
    ~ScienceLayout();

    // 设置显示框引用
    void setDisplay(QLineEdit* display) { displayLineEdit = display; }

signals:
    // 向主窗口发送的请求信号
    void displayUpdateRequested(const QString& text);
    void displayClearRequested();
    void backspaceRequested();
    void calculateRequested(const QString& expression);

public slots:
    void handleKeyPress(QKeyEvent* event);
    void handleScientificFunction(const QString& function);

private slots:
    void appendNumber();
    void onBackspaceClicked();
    void onClearClicked();
    void onCommitClicked();
    void onScientificButtonClicked();

private:
    void createWidgets();
    void setupLayout();
    void setupConnections();
    void setupScientificButtons();

    // 显示框引用
    QLineEdit* displayLineEdit;

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
    QPushButton* btnFactorial; // n! (图片中的nI可能是阶乘)

    // 布局
    QGridLayout* gridLayout;

    // 科学计算函数映射
    QHash<QString, QString> scientificFunctions;
};