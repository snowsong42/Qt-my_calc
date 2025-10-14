#include "my_calc.h"

my_calc::my_calc(QWidget* parent)
    : QMainWindow(parent)
    , mainLayout(nullptr)
    , scienceLayout(nullptr)
    , loanLayout(nullptr)
    , currentLayout(nullptr)
{
    // 设置窗口属性
    setWindowTitle("计算器");
    setFixedSize(600, 600);

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

    // 创建显示框
    displayLineEdit = new QLineEdit(centralWidget);
    displayLineEdit->setMinimumHeight(40);
    displayLineEdit->setFont(QFont("Century Gothic", 24));
    displayLineEdit->setStyleSheet("font: 24pt \"Century Gothic\";");
    displayLineEdit->setText("");
    displayLineEdit->setAlignment(Qt::AlignRight);
    displayLineEdit->setReadOnly(true);
    displayLineEdit->setPlaceholderText("请输入表达式...");
    displayLineEdit->setGeometry(30, 30, 411, 71);

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
    settingsAction->setShortcut(QKeySequence("Ctrl+P"));

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
        currentLayout->setParent(nullptr);
        currentLayout->deleteLater();
        currentLayout = nullptr;
    }
}

// 统一的布局连接函数
void my_calc::connectLayoutSignals(BaseLayout* layout)
{
    if (!layout) return;

	// 统一接入所有布局的共同信号，借助BaseLayout
    connect(layout, &BaseLayout::displayUpdateRequested, this, &my_calc::updateDisplay);
    connect(layout, &BaseLayout::displaySetRequested, this, &my_calc::setDisplay);
    connect(layout, &BaseLayout::displayClearRequested, this, &my_calc::clearDisplay);
    connect(layout, &BaseLayout::backspaceRequested, this, &my_calc::backspaceDisplay);
    connect(layout, &BaseLayout::getDisplayTextRequested, this, &my_calc::getDisplayText);
}

// 切换到主计算器布局
void my_calc::switchToMainLayout()
{
    cleanupCurrentLayout();
    mainLayout = new MainLayout(centralWidget);
    currentLayout = mainLayout;
    connectLayoutSignals(mainLayout);
    mainLayout->setGeometry(0, 110, width(), height() - 110);
    mainLayout->show();
}

// 切换到科学计算器布局
void my_calc::switchToScienceLayout()
{
    cleanupCurrentLayout();
    scienceLayout = new ScienceLayout(centralWidget);
    currentLayout = scienceLayout;
    connectLayoutSignals(scienceLayout);
    scienceLayout->setGeometry(0, 110, width(), height() - 110);
    scienceLayout->show();
}

// 切换到贷款计算器布局
void my_calc::switchToLoanLayout()
{
    cleanupCurrentLayout();
    loanLayout = new LoanLayout(centralWidget);
    currentLayout = loanLayout;
    connectLayoutSignals(loanLayout);
    loanLayout->setGeometry(0, 110, width(), height() - 110);
    loanLayout->show();
}

// 显示设置对话框（占位）
void my_calc::showSettings()
{
    QMessageBox::information(this, "设置", "设置功能正在开发中...");
}

// 操作显示框的核心代码，是收发周转的枢纽
void my_calc::updateDisplay(const QString& text)
{
	// 在显示框末尾追加文本
    QString currentText = displayLineEdit->text();
    displayLineEdit->setText(currentText + text);
}

void my_calc::setDisplay(const QString& text)
{
	// 直接设置显示框内容
    displayLineEdit->setText(text);
}

void my_calc::backspaceDisplay()
{
	// 删除显示框最后一个字符
    QString text = displayLineEdit->text();
    if (!text.isEmpty()) {
        text.chop(1);
        displayLineEdit->setText(text);
	}
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

