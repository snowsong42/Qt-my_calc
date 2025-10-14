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
    // 统一的通信接口 - 所有布局都通过这些信号与主界面通信
    void displayUpdateRequested(const QString& text);   // 追加文本
    void displaySetRequested(const QString& text);      // 设置文本
    void displayClearRequested();                       // 清空显示
    void backspaceRequested();                          // 删除字符
    QString getDisplayTextRequested();                  // 请求获取显示文本
    void calculateRequested(const QString& expression); // 计算请求

public slots:
    // 统一的键盘事件处理接口
    virtual void handleKeyPress(QKeyEvent* event) = 0;

    // 接收显示文本的槽函数
    virtual void onDisplayTextReceived(const QString& text) { Q_UNUSED(text); }

protected:
    // 公共的工具方法
    void setupButtonStyle(QPushButton* button, const QString& style = "");
    void setupCommonConnections();

    // 公共的成员变量
    QLineEdit* displayLineEdit = nullptr;

private:
    // 纯虚函数 - 子类必须实现
    virtual void createWidgets() = 0;
    virtual void setupLayout() = 0;
    virtual void setupConnections() = 0;
};