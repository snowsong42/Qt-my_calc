#include "my_calc.h"

my_calc::my_calc(QWidget* parent)
    : QMainWindow(parent)
    , mainLayout(nullptr)
    , scienceLayout(nullptr)
    , loanLayout(nullptr)
    , currentLayout(nullptr)
{
    this->setWindowIcon(QIcon(":/image/ice.ico"));
    // 设置窗口属性
    setWindowTitle("计算器");
    setMinimumSize(400, 500); // 设置最小大小，允许缩放
    resize(500, 600); // 初始大小

    // 创建控件
    createWidgets();
    setupConnections();

    // 设置焦点策略
    setFocusPolicy(Qt::StrongFocus);

    // 默认显示主布局
    switchToMainLayout();
}

my_calc::~my_calc()
{
    cleanupCurrentLayout();
}

void my_calc::createWidgets()
{
    // 创建中央部件
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建主布局
    QVBoxLayout* mainVLayout = new QVBoxLayout(centralWidget);
    mainVLayout->setSpacing(10);
    mainVLayout->setContentsMargins(15, 15, 15, 15);

    // 创建显示框
    displayLineEdit = new QLineEdit();
    displayLineEdit->setMinimumHeight(70);
    displayLineEdit->setFont(QFont("Century Gothic", 17));
    displayLineEdit->setText("");
    displayLineEdit->setAlignment(Qt::AlignRight);
    displayLineEdit->setReadOnly(false);
    displayLineEdit->setPlaceholderText("请输入表达式...");
    /*
    displayLineEdit->setStyleSheet(
        "QLineEdit {"
        "    border: 2px solid #ccc;"
        "    border-radius: 5px;"
        "    padding: 5px 10px;"
        "    background-color: #f9f9f9;"
        "    font: 16pt 'Century Gothic';"
        "}"
    );
    */
    displayLineEdit->setStyleSheet(
        "QLineEdit {"
        "    border: 2px solid #A0A0A0;" /* 边框宽度为2px，颜色为#A0A0A0 */
        "    border - radius: 4px;" /* 边框圆角 */
        "    padding - left: 5px;" /* 文本距离左边界有5px */
        "    background - color: #F2F2F2;" /* 背景颜色 *//* 文本颜色不设置 */
        "    selection - background - color: #A0A0A0;" /* 选中文本的背景颜色 */
        "    selection - color: #F2F2F2;" /* 选中文本的颜色 */
        "}"
        "QLineEdit:focus {"
        "    border-color: #3498db;"
        "}"
    );

    mainVLayout->addWidget(displayLineEdit);

    // 创建菜单子动作
    mainCalcAction = new QAction("主计算器", this);
    mainCalcAction->setStatusTip("切换到主计算器模式");
    mainCalcAction->setShortcut(QKeySequence("F1"));

    scienceCalcAction = new QAction("科学计算器", this);
    scienceCalcAction->setStatusTip("切换到科学计算器模式");
    scienceCalcAction->setShortcut(QKeySequence("F2"));

    loanCalcAction = new QAction("贷款计算器", this);
    loanCalcAction->setStatusTip("切换到贷款计算器模式");
    loanCalcAction->setShortcut(QKeySequence("F3"));

    settingsAction = new QAction("设置", this);
    settingsAction->setStatusTip("应用程序设置");
    settingsAction->setShortcut(QKeySequence("Ctrl+S"));

    exitAction = new QAction("退出", this);
    exitAction->setStatusTip("退出应用程序");
    exitAction->setShortcut(QKeySequence::Quit);

    aboutAction = new QAction("关于", this);
    aboutAction->setStatusTip("关于此应用程序");

    // 创建菜单
    // 模式
    modeMenu = menuBar()->addMenu("模式");
    modeMenu->addAction(mainCalcAction);
    modeMenu->addAction(scienceCalcAction);
    modeMenu->addAction(loanCalcAction);
    modeMenu->addSeparator();
    modeMenu->addAction(exitAction);

    // 编辑
    editMenu = menuBar()->addMenu("编辑");
    editMenu->addAction(settingsAction);

    // 帮助
    helpMenu = menuBar()->addMenu("帮助");
    helpMenu->addAction(aboutAction);

    // 创建工具栏
    mainToolBar = addToolBar("主工具栏");
    mainToolBar->addAction(mainCalcAction);
    mainToolBar->addAction(scienceCalcAction);
    mainToolBar->addAction(loanCalcAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(settingsAction);
}

void my_calc::setupConnections()
{
    // 连接菜单动作
    connect(mainCalcAction, &QAction::triggered, this, &my_calc::switchToMainLayout);
    connect(scienceCalcAction, &QAction::triggered, this, &my_calc::switchToScienceLayout);
    connect(settingsAction, &QAction::triggered, this, &my_calc::showSettings);
    connect(loanCalcAction, &QAction::triggered, this, &my_calc::switchToLoanLayout);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "关于计算器",
            "这是一个基于Qt的计算器应用程序\n"
            "版本 1.0\n"
            "使用纯代码实现");
        });
}

// 将键盘事件转发给当前布局
void my_calc::keyPressEvent(QKeyEvent* event)
{
    if (currentLayout) {
        if (MainLayout* main = qobject_cast<MainLayout*>(currentLayout)) {
            main->handleKeyPress(event);
            return;
        }
        if (ScienceLayout* science = qobject_cast<ScienceLayout*>(currentLayout)) {
            science->handleKeyPress(event);
            return;
        }
        if (LoanLayout* loan = qobject_cast<LoanLayout*>(currentLayout)) {
            loan->handleKeyPress(event);
            return;
        }
    }
    QMainWindow::keyPressEvent(event);
}

// 清理当前布局
void my_calc::cleanupCurrentLayout()
{
    if (currentLayout) {
        QLayout* layout = centralWidget->layout();
        if (layout) {
            // 从布局中移除当前布局部件
            QLayoutItem* item;
            while ((item = layout->takeAt(1)) != nullptr) { // 从索引1开始（索引0是displayLineEdit）
                delete item->widget();
                delete item;
            }
        }
        currentLayout = nullptr;
    }
}

// 统一的布局连接函数
void my_calc::connectLayoutSignals(BaseLayout* layout)
{
    if (!layout) return;

    // 统一接入所有布局的共同信号，借助BaseLayout
    connect(layout, &BaseLayout::getDisplayTextRequested, this, &my_calc::getDisplayText);
    connect(layout, &BaseLayout::displaySetRequested, this, &my_calc::setDisplay);
    connect(layout, &BaseLayout::displayClearRequested, this, &my_calc::clearDisplay);
}

// 切换到主计算器布局
void my_calc::switchToMainLayout()
{
    cleanupCurrentLayout();
    mainLayout = new MainLayout();
    currentLayout = mainLayout;
    connectLayoutSignals(mainLayout);

    QVBoxLayout* mainVLayout = qobject_cast<QVBoxLayout*>(centralWidget->layout());
    if (mainVLayout) {
        mainVLayout->addWidget(mainLayout);
    }
}

// 切换到科学计算器布局
void my_calc::switchToScienceLayout()
{
    cleanupCurrentLayout();
    scienceLayout = new ScienceLayout();
    currentLayout = scienceLayout;
    connectLayoutSignals(scienceLayout);

    QVBoxLayout* mainVLayout = qobject_cast<QVBoxLayout*>(centralWidget->layout());
    if (mainVLayout) {
        mainVLayout->addWidget(scienceLayout);
    }
}

// 切换到贷款计算器布局
void my_calc::switchToLoanLayout()
{
    cleanupCurrentLayout();
    loanLayout = new LoanLayout();
    currentLayout = loanLayout;
    connectLayoutSignals(loanLayout);

    QVBoxLayout* mainVLayout = qobject_cast<QVBoxLayout*>(centralWidget->layout());
    if (mainVLayout) {
        mainVLayout->addWidget(loanLayout);
    }
}

// 显示设置对话框
void my_calc::showSettings()
{
    QMessageBox::information(this, "设置", "设置功能正在开发中...");
}

// 核心代码:收发周转的枢纽
// 三个槽函数的执行代码，用于操作显示框
void my_calc::setDisplay(const QString& text)
{
    // 直接设置显示框内容
    displayLineEdit->setText(text);
}

void my_calc::clearDisplay()
{
    // 清空显示框
    displayLineEdit->clear();
}

QString my_calc::getDisplayText() const {
    // 获取显示框内容
    return displayLineEdit->text();
}