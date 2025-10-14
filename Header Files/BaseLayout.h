#pragma once
#include "dependences.h"

// 前向声明
class QPushButton;
class QGridLayout;
class QWidget;

class BaseLayout : public QWidget
{
    Q_OBJECT

public:
    explicit BaseLayout(QWidget* parent = nullptr);
    virtual ~BaseLayout() = default;

signals:
    // 统一的通信接口，所有布局都通过这些信号与主界面通信
    QString getDisplayTextRequested();                  // 请求获取显示文本
    void displaySetRequested(const QString& text);      // 设置文本
    void displayClearRequested();                       // 清空显示

public slots:
    // 统一的键盘事件处理接口
    void handleKeyPress(QKeyEvent* event);
	// 统一的提交按钮点击处理接口，其实只是便于在基类里编写键盘事件处理
    virtual void onCommitClicked() = 0;

protected:
    // 公共的工具方法
    void setupButtonStyle(QPushButton* button, const QString& style = "");
    void setupCommonConnections();

private:
    // 纯虚函数，只能由子类实现
    virtual void createWidgets() = 0;
    virtual void setupLayout() = 0;
    virtual void setupConnections() = 0;
};