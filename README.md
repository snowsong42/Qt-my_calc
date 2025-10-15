# 设计思想

- 解耦，解耦，再解耦。
- 最好能在一个模块完全不知道另一个模块具体实现的情况下，完成自己的任务，尤其重要的是完成与那个他自己都不认识的模块合作的任务。
- 举例而言：即使我主界面不用LineEdit了，我的子模块照样可以工作！
- 接口设计统一在抽象类BaseLayout里面，然后具体的Layout都继承自这个抽象类，实现对Layout共有功能的改动“一次更改，全面生效”。
- 具体实现方法，我们既然用了Qt，就不要自己写回调函数了，直接定义signal和slot，在用的时候emit发射信号即可。
- 这样，我的发送义务就只有发射统一格式的信号，你那边怎么接收，我这个模块不关心。
- 这样，我的接收义务就只有用槽接收统一格式的信号，信号什么时候来，谁发过来，我都不关心。
# 模块综述

- 主界面，下辖着主界面的LineEdit，这是整个软件的核心。
- MainLayout，继承BaseLayout，自基本计算器布局
- ScienceLayout，继承BaseLayout，科学计算器布局
- LoanLayout，继承BaseLayout，利息计算器布局

# 技术细节

## BaseLayout
- 在这里实现了通用且统一的Layout权利法案
- 除此之外，有一个onCommitClicked()的纯虚函数，也就是说，默认每个Layout都必然有递交功能。
- 这样写为下面统一按键输入方式奠定基础。因为按下Enter毕竟是需要触发onCommitClicked()的。
- 统一的按键输入方式。特殊按键特殊处理。
- 一些固定的连接，但我还没有看到有哪些连接是固定的，所以就暂定留在这里了。
- 统一一个默认的按钮样式。

## 主界面权利法案
主界面有以下几个组件间权利：
- 接收这三种信号：
	- 请求直接重设对话框内容
	- 请求清空对话框内容
	- 申请获得对话框内容
- 发射这一种信号：
	- 转发键盘信号

## Layout权利法案
每个Layout都有以下几个组件间权利：
- 在被创建时接收主界面的指针
- 通过public接口函数直接查询主界面的指针（一般不要用！）
```C++
 QWidget* getCentralWidget() const { return centralWidget; }
```
- 发射这三种信号：
	- 请求直接重设对话框内容
	- 请求清空对话框内容
	- 申请获得对话框内容
- 接收这一种信号：
	- 主界面转发的键盘信号

## 合作流程
于是他们的工作流程是这样的：
【主界面】创建菜单和对话框，以主计算器初始化
【主计算器】接到通知，被创建
【主界面】选择科学计算器
【主界面】删除主计算器，初始化科学计算器
【科学计算器】接到通知，被创建
以此类推...

# 【新】设置系统

### 设计思想

一、 分层架构：
- 数据层 (Settings) - 纯数据管理
- 视图层 (SettingsDialog) - 纯界面交互
- 控制层 (my_calc) - 协调和数据流转
二、解耦：使用Qt的信号槽实现松耦合通信，设置更改能实时反映到界面。
三、样式表系统
四、 数据持久化
## 整体架构

设置功能主要由三个核心类组成：
- **Settings** - 数据模型层，负责设置数据的存储和转换
- **SettingsDialog** - 视图层，提供用户界面
- **my_calc** - 主窗口，集成和应用设置

工作流程：
1. **用户点击设置菜单** -> `showSettings()`
2. **打开设置对话框** -> 加载当前设置到界面
3. **用户修改设置** -> 通过各种控件交互
4. **点击应用/确定** -> `applySettings()`
5. **保存并应用** -> 更新数据 + 持久化 + 发出信号
6. **主窗口响应** -> 立即更新界面样式

## 1. Settings 类详解

### 数据成员
```cpp
QString m_style;                    // 当前主题样式
bool m_autoSaveWindow;              // 是否自动保存窗口状态
int m_decimalPlaces;                // 小数位数精度
bool m_scientificNotation;          // 是否使用科学计数法
QByteArray m_windowGeometry;        // 窗口几何信息
QByteArray m_windowState;           // 窗口状态信息
```

### 核心功能

- 数据持久化：从系统注册表/配置文件中加载设置 | 将设置保存到系统注册表/配置文件
- 样式转换系统 - `styleCast()` 方法:这是最重要的功能，将样式名称转换为对应的QSS样式表。

可选样式：
- Light主题
- Dark主题
- Blue主题
- Green主题
- Default主题
## 2. SettingsDialog 类详解

### 数据成员
```cpp
QComboBox* styleComboBox;           // 主题选择下拉框
QCheckBox* autoSaveCheckBox;        // 自动保存窗口状态
QSpinBox* decimalPlacesSpinBox;     // 小数位数设置
QCheckBox* scientificNotationCheckBox; // 科学计数法开关

// 操作按钮
QPushButton* applyButton;           // 应用按钮
QPushButton* resetButton;           // 恢复默认
QPushButton* cancelButton;          // 取消
QPushButton* okButton;              // 确定
```

###  设置流程

1. **加载当前设置** - `loadSettings()`
2. **用户修改界面** - 通过各种控件
3. **应用设置** - `applySettings()`
   - 从界面读取值
   - 更新Settings对象
   - 保存到持久化存储
   - 发出`styleChanged`信号

### 信号机制
```cpp
styleChanged(const QString& style)  // 样式改变信号
```
当用户更改主题时，立即通知主窗口更新界面样式。

## 3. 主界面

### 初始化阶段

- 在构造函数中 创建设置对象
- 应用保存的样式
### 自动保存

- 程序启动时恢复窗口状态
- 程序退出时保存窗口状态
