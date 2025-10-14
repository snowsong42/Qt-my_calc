#include "BaseLayout.h"

void BaseLayout::setupButtonStyle(QPushButton* button, const QString& style)
{
    button->setMinimumHeight(40);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    if (!style.isEmpty()) {
        button->setStyleSheet(style);
    }
}

void BaseLayout::setupCommonConnections()
{
    // 这里可以放置一些通用的连接逻辑
    // 具体连接在子类中实现
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