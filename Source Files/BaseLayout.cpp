#include "BaseLayout.h"

// 构造函数
BaseLayout::BaseLayout(QWidget * parent)
    : QWidget(parent)
{
}

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