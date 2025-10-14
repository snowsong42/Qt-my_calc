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
    explicit BaseLayout(QWidget* parent = nullptr) {};
	~BaseLayout() {}  // 析构函数不能继承,所以空着

signals:
    // 统一的通信信号
    // 所有布局都通过这些信号与主界面通信
    QString getDisplayTextRequested();                  // 请求获取显示文本
    void displaySetRequested(const QString& text);      // 设置文本
    void displayClearRequested();                       // 清空显示

public slots:
    // 统一的键盘事件处理槽
    void handleKeyPress(QKeyEvent* event);

	// 统一的提交按钮点击处理方法，其实只是便于在基类里编写键盘事件处理
	// 但这引出了一个设计问题：每个窗口都必须有一个提交按钮，映射到enter键。
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
	virtual void cleanup() = 0;
};