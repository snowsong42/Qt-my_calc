#include "my_calc.h"

my_calc::my_calc(QWidget* parent)
    : QMainWindow(parent)
    , mainLayout(nullptr)
    , scienceLayout(nullptr)
    , loanLayout(nullptr)
    , currentLayout(nullptr)
    , appSettings(new Settings())
    , settingsDialog(nullptr)
{
    this->setWindowIcon(QIcon(":/image/ice.ico"));
    setWindowTitle("计算器");
    setMinimumSize(400, 500);
    resize(500, 600);

    createWidgets();
    setupConnections();

    setFocusPolicy(Qt::StrongFocus);

    // 应用保存的窗口状态
    if (appSettings->getAutoSaveWindow()) {
        restoreGeometry(appSettings->getWindowGeometry());
        restoreState(appSettings->getWindowState());
    }


    // 将样式名称转换为样式表
    QString styleSheet = appSettings->styleCast(appSettings->getStyle()); 
    // 应用样式表
    applyStyle(styleSheet);

    // 默认显示主布局
    switchToMainLayout();
}

void my_calc::applyStyle(const QString& styleSheet) {
    qApp->setStyleSheet(styleSheet);
}

my_calc::~my_calc()
{
    // 保存窗口状态
    if (appSettings->getAutoSaveWindow()) {
        appSettings->setWindowGeometry(saveGeometry());
        appSettings->setWindowState(saveState());
        appSettings->save();
    }

    cleanupCurrentLayout();
    delete appSettings;
    if (settingsDialog) {
        delete settingsDialog;
    }
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
    settingsAction->setShortcut(QKeySequence("F4"));

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
	// 布局切换
    connect(mainCalcAction, &QAction::triggered, this, &my_calc::switchToMainLayout);
    connect(scienceCalcAction, &QAction::triggered, this, &my_calc::switchToScienceLayout);
    connect(loanCalcAction, &QAction::triggered, this, &my_calc::switchToLoanLayout);

	// 关闭、设置、关于
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    connect(settingsAction, &QAction::triggered, this, &my_calc::showSettings);
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "关于计算器",
            "这是一个基于Qt的计算器小程序，纯代码实现\n"
			"作者：SnowSong\n"
            "越崎理工实验24-01班 学号：06245011\n"
			"版本：v2.3 加图标\n"
            "Github开源地址：https://github.com/snowsong42/Qt-my_calc");
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
		delete currentLayout;
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

void my_calc::showSettings()
{
    if (!settingsDialog) {
        settingsDialog = new SettingsDialog(appSettings, this);
		// 连接样式更改信号到样式应用槽
        connect(settingsDialog, &SettingsDialog::styleChanged,
            this, [this](const QString& style) {
                applyStyle(appSettings->styleCast(style));
			});
    }
    settingsDialog->exec();
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