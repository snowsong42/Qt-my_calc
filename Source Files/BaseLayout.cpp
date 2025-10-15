#include "BaseLayout.h"

// 基类构造函数
BaseLayout::BaseLayout(QWidget* parent)
    : QWidget(parent)
{
	// 初始化常用按钮
	btn0 = nullptr;
	btn1 = nullptr;
	btn2 = nullptr;
	btn3 = nullptr;
	btn4 = nullptr;
	btn5 = nullptr;
	btn6 = nullptr;
	btn7 = nullptr;
	btn8 = nullptr;
	btn9 = nullptr;
	btnPercent = nullptr;
	btnPeriod = nullptr;
	btnBackspace = nullptr;
	btnClear = nullptr;
	btnCommit = nullptr;
}

void BaseLayout::setupButtonStyle(QPushButton* button, const QString& style)
{
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    if (!style.isEmpty()) {
        button->setStyleSheet(style);
    }
}

// 通用的连接逻辑
void BaseLayout::setupCommonConnections()
{
    // 连接功能按钮信号
    connect(btnBackspace, &QPushButton::clicked, this, &BaseLayout::onBackspaceClicked);
    connect(btnClear, &QPushButton::clicked, this, &BaseLayout::onClearClicked);
    connect(btnCommit, &QPushButton::clicked, this, &BaseLayout::onCommitClicked);

    // 连接数字按钮信号
    connect(btn0, &QPushButton::clicked, this, &BaseLayout::appendNumber);
    connect(btn1, &QPushButton::clicked, this, &BaseLayout::appendNumber);
    connect(btn2, &QPushButton::clicked, this, &BaseLayout::appendNumber);
    connect(btn3, &QPushButton::clicked, this, &BaseLayout::appendNumber);
    connect(btn4, &QPushButton::clicked, this, &BaseLayout::appendNumber);
    connect(btn5, &QPushButton::clicked, this, &BaseLayout::appendNumber);
    connect(btn6, &QPushButton::clicked, this, &BaseLayout::appendNumber);
    connect(btn7, &QPushButton::clicked, this, &BaseLayout::appendNumber);
    connect(btn8, &QPushButton::clicked, this, &BaseLayout::appendNumber);
    connect(btn9, &QPushButton::clicked, this, &BaseLayout::appendNumber);
    connect(btnPercent, &QPushButton::clicked, this, &BaseLayout::appendNumber);
    connect(btnPeriod, &QPushButton::clicked, this, &BaseLayout::appendNumber);
}

// 核心代码：通信逻辑的实现
// 这里实现一些常见的通信逻辑
void BaseLayout::appendNumber()
{
    // 加一个字符
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString text = emit getDisplayTextRequested(); // 请求获取表达式
    emit displaySetRequested(text + button->text());
}

void BaseLayout::onBackspaceClicked()
{
    QString text = emit getDisplayTextRequested(); // 请求获取表达式
    // 删除显示框最后一个字符
    if (!text.isEmpty()) {
        text.chop(1);
    }
    emit displaySetRequested(text);
}

void BaseLayout::onClearClicked()
{
    emit displayClearRequested();
}



void BaseLayout::handleKeyPress(QKeyEvent* event)
{
    // 允许所有键盘输入 - 直接将字符添加到显示框
    QString text = emit getDisplayTextRequested();

    // 处理特殊按键
    if (event->key() == Qt::Key_Backspace) {
        if (!text.isEmpty()) {
            text.chop(1);
            emit displaySetRequested(text);
        }
    }
    else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        onCommitClicked();
    }
    else if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_Delete) {
        emit displayClearRequested();
    }
    else {
        // 获取按键的文本，直接添加到显示框
        QString keyText = event->text();
        if (!keyText.isEmpty() && keyText != "\r" && keyText != "\n") {
            emit displaySetRequested(text + keyText);
        }
    }
}