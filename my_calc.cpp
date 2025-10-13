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
    setFixedSize(600, 800);

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

void my_calc::cleanupCurrentLayout()
{
    if (currentLayout) {
        currentLayout->setParent(nullptr);
        currentLayout->deleteLater();
        currentLayout = nullptr;
    }
}

// 切换到主计算器
void my_calc::switchToMainLayout()
{
    cleanupCurrentLayout();

    mainLayout = new MainLayout(centralWidget, displayLineEdit);
    currentLayout = mainLayout;

    // 连接MainLayout的信号到my_calc的槽
    connect(mainLayout, &MainLayout::displayUpdateRequested, this, &my_calc::updateDisplay);
    connect(mainLayout, &MainLayout::displayClearRequested, this, &my_calc::clearDisplay);
    connect(mainLayout, &MainLayout::backspaceRequested, this, [this]() {
        QString text = displayLineEdit->text();
        if (!text.isEmpty()) {
            text.chop(1);
            displayLineEdit->setText(text);
        }
        });

    // 调整布局位置
    mainLayout->setGeometry(0, 110, width(), height() - 110);
    mainLayout->show();
}

// 切换到科学计算器
void my_calc::switchToScienceLayout()
{
    cleanupCurrentLayout();

    scienceLayout = new ScienceLayout(centralWidget, displayLineEdit);
    currentLayout = scienceLayout;

    // 连接ScienceLayout的信号到my_calc的槽
    connect(scienceLayout, &ScienceLayout::displayUpdateRequested, this, &my_calc::updateDisplay);
    connect(scienceLayout, &ScienceLayout::displayClearRequested, this, &my_calc::clearDisplay);
    connect(scienceLayout, &ScienceLayout::backspaceRequested, this, [this]() {
        QString text = displayLineEdit->text();
        if (!text.isEmpty()) {
            text.chop(1);
            displayLineEdit->setText(text);
        }
        });
    connect(scienceLayout, &ScienceLayout::calculateRequested, this, [this](const QString& expression) {
        // 这里可以实现科学计算表达式的求值
        // 暂时简单显示
        QMessageBox::information(this, "科学计算",
            QString("计算表达式: %1\n科学计算功能正在开发中...").arg(expression),
            QMessageBox::Ok);
        });

    // 调整布局位置
    scienceLayout->setGeometry(0, 110, width(), height() - 110);
    scienceLayout->show();
}

// 切换到贷款计算器
void my_calc::switchToLoanLayout()
{
    cleanupCurrentLayout();

    loanLayout = new LoanLayout(centralWidget, displayLineEdit);
    currentLayout = loanLayout;

    // 连接LoanLayout的信号到my_calc的槽
    connect(loanLayout, &LoanLayout::displayUpdateRequested, this, &my_calc::updateDisplay);
    connect(loanLayout, &LoanLayout::displayClearRequested, this, &my_calc::clearDisplay);

    // 调整布局位置
    loanLayout->setGeometry(0, 110, width(), height() - 110);
    loanLayout->show();
}

void my_calc::showSettings()
{
    QMessageBox::information(this, "设置", "应用程序设置对话框", QMessageBox::Ok);
}

void my_calc::updateDisplay(const QString& text)
{
    QString currentText = displayLineEdit->text();
    displayLineEdit->setText(currentText + text);
}

void my_calc::clearDisplay()
{
    displayLineEdit->clear();
}

void my_calc::keyPressEvent(QKeyEvent* event)
{
    // 将键盘事件转发给当前布局
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