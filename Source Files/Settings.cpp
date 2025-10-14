#include "Settings.h"

Settings::Settings()
    : m_style("Default")
    , m_autoSaveWindow(true)
    , m_decimalPlaces(6)
    , m_scientificNotation(false)
{
    load();
}

void Settings::load()
{
    QSettings settings;

    m_style = settings.value("style", "Default").toString();
    m_autoSaveWindow = settings.value("autoSaveWindow", true).toBool();
    m_windowGeometry = settings.value("windowGeometry").toByteArray();
    m_windowState = settings.value("windowState").toByteArray();
    m_decimalPlaces = settings.value("decimalPlaces", 6).toInt();
    m_scientificNotation = settings.value("scientificNotation", false).toBool();
}

void Settings::save()
{
    QSettings settings;

    settings.setValue("style", m_style);
    settings.setValue("autoSaveWindow", m_autoSaveWindow);
    settings.setValue("windowGeometry", m_windowGeometry);
    settings.setValue("windowState", m_windowState);
    settings.setValue("decimalPlaces", m_decimalPlaces);
    settings.setValue("scientificNotation", m_scientificNotation);
}

// 样式相关
QString Settings::getStyle() const { return m_style; }
void Settings::setStyle(const QString& style) { m_style = style; }

// 重要函数：在这里更改样式表
QString Settings::styleCast(const QString& style) const{
    QString styleSheet;
    if (style == "Light") {
        styleSheet =
            "QMainWindow { background-color: #f5f5f5; }"
            "QWidget { background-color: #f5f5f5; color: #333333; }"
            "QLineEdit { background-color: white; color: #333333; border: 2px solid #cccccc; }"
            "QPushButton { "
            "    background-color: white; "
			"    color: #000000; "             // 黑色文字
            "    font-weight: bold; "
            "    border: 1px solid #cccccc; "  // 减少边框宽度
            "    border-radius: 4px; "
            "    padding: 3px 8px; "           // 减少内边距
            "    min-height: 20px; "           // 设置最小高度
			"    min-width: 60px; "            // 设置最小宽度
            "}"
            "QPushButton:hover { "
            "    background-color: #e1f5fe; "
            "    border-color: #4fc3f7; "
            "}"
            "QPushButton:pressed { "
            "    background-color: #e0e0e0; "
            "    border-color: #9e9e9e; "
            "}"
            "QComboBox { "
            "    background-color: #f8f8f8; "
            "    color: #333333; "
            "    min-height: 25px; "
            "}"
            "QComboBox:focus { "
            "    border-color: #3498db; "
            "}"
            "QComboBox::drop-down { "
            "    border: none; "
            "    width: 25px; "
            "}"
            "QComboBox::down-arrow { "
            "    image: none; "
            "    width: 0px; "
            "    height: 0px; "
            "}"
            "QComboBox QAbstractItemView { "
            "    background-color: #f8f8f8; "  // 下拉列表也是浅灰色
            "    selection-background-color: #e1f5fe; "  // 选中项用浅蓝色
            "    outline: none; "
            "    min-height: 30px; "
            "}"

            "QGroupBox { "
			"    background-color: #efefef; "  // 浅灰色背景,三个数字越大越浅
            "    border: 1px solid #cccccc; "
            "    border-radius: 5px; "
            "    margin-top: 10px; "
            "    padding-top: 10px; "
            "}"
            "QGroupBox::title { "
            "    subcontrol-origin: margin; "
            "    subcontrol-position: top center; "
            "    background-color: #f8f8f8; "  // 标题背景也是浅灰色
            "    color: #333333; "
            "    font-weight: bold; "
            "    padding: 0 5px; "
            "}";
    }
    else if (style == "Dark") {
        styleSheet =
            "QMainWindow { background-color: #2b2b2b; }"
            "QWidget { background-color: #2b2b2b; color: #ffffff; }"
            "QLineEdit { background-color: #3c3c3c; color: #ffffff; border: 1px solid #555555; }"
            "QPushButton { "
            "    background-color: #404040; "
            "    color: #ffffff; "
            "    border: 1px solid #555555; "
            "    border-radius: 4px; "
            "    padding: 3px 8px; "
            "    min-height: 20px; "
            "    min-width: 60px; "  // 添加最小宽度
            "}"
            "QPushButton:hover { background-color: #505050; }"
            "QPushButton:pressed { background-color: #606060; }"
            "QComboBox { background-color: #404040; color: #ffffff; border: 1px solid #555555; }"
            "QGroupBox { color: #ffffff; }";
    }
    else if (style == "Blue") {
        styleSheet =
            "QMainWindow { background-color: #e3f2fd; }"
            "QWidget { background-color: #e3f2fd; color: #1565c0; }"
            "QLineEdit { background-color: #bbdefb; color: #0d47a1; border: 1px solid #90caf9; }"
            "QPushButton { "
            "    background-color: #bbdefb; "
			"    color: #00008B; "  // 深蓝色文字
            "    font-weight: bold; "
            "    border: none; "
            "    border-radius: 4px; "
            "    padding: 3px 8px; "
            "    min-height: 20px; "
            "    min-width: 60px; "  // 添加最小宽度
            "}"
            "QPushButton:hover { background-color: #1976d2; }"
            "QPushButton:pressed { background-color: #0d47a1; }";
            "QComboBox { "
            "    background-color: #f3f9ff; "
            "    color: #0d47a1; "
            "    border: 1px solid #90caf9; "
            "    border-radius: 4px; "
            "    padding: 4px 8px; "
            "    min-height: 25px; "
            "}"
            "QComboBox:focus { "
            "    border-color: #1976d2; "
            "    background-color: #ffffff; "
            "}"
            "QComboBox::drop-down { "
            "    border: none; "
            "    width: 25px; "
            "}"
            "QComboBox::down-arrow { "
            "    image: none; "
            "    border-left: 5px solid transparent; "
            "    border-right: 5px solid transparent; "
            "    border-top: 5px solid #0d47a1; "
            "    width: 0px; "
            "    height: 0px; "
            "}"
            "QComboBox QAbstractItemView { "
            "    background-color: #f3f9ff; "
            "    border: 1px solid #90caf9; "
            "    border-radius: 4px; "
            "    selection-background-color: #bbdefb; "
            "    selection-color: #0d47a1; "
            "    outline: none; "
            "    min-height: 30px; "
            "}"
            "QGroupBox { "
            "    background-color: #e1f5fe; "  // 更明显的浅蓝色背景
            "    border: 1px solid #81d4fa; "
            "    border-radius: 5px; "
            "    margin-top: 10px; "
            "    padding-top: 10px; "
            "    color: #0277bd; "
            "}"
            "QGroupBox::title { "
            "    subcontrol-origin: margin; "
            "    subcontrol-position: top center; "
            "    background-color: #e1f5fe; "
            "    color: #01579b; "
            "    font-weight: bold; "
            "    padding: 2px 10px; "
            "    border-radius: 3px; "
            "}"
            // 为单选按钮添加样式
            "QRadioButton { "
            "    color: #0d47a1; "
            "    spacing: 5px; "
            "}"
            "QRadioButton::indicator { "
            "    width: 13px; "
            "    height: 13px; "
            "}"
            "QRadioButton::indicator:unchecked { "
            "    border: 1px solid #90caf9; "
            "    border-radius: 6px; "
            "    background-color: white; "
            "}"
            "QRadioButton::indicator:checked { "
            "    border: 1px solid #1976d2; "
            "    border-radius: 6px; "
            "    background-color: #1976d2; "
            "}";
    }
    else if (style == "Green") {
        styleSheet =
            "QMainWindow { background-color: #e8f5e8; }"
            "QWidget { background-color: #e8f5e8; color: #2e7d32; }"
            "QLineEdit { background-color: #c8e6c9; color: #1b5e20; border: 1px solid #a5d6a7; }"
            "QPushButton { "
            "    background-color: #c8e6c9; "
			"    color: #006400; " // 深绿色文字
            "    font-weight: bold; "
            "    border: none; "
            "    border-radius: 4px; "
            "    padding: 3px 8px; "
            "    min-height: 20px; "
            "    min-width: 60px; "  // 添加最小宽度
            "}"
            "QPushButton:hover { background-color: #388e3c; }"
            "QPushButton:pressed { background-color: #1b5e20; }";
            "QComboBox { "
            "    background-color: #f5fbf5; "
            "    color: #1b5e20; "
            "    border: 1px solid #a5d6a7; "
            "    border-radius: 4px; "
            "    padding: 4px 8px; "
            "    min-height: 25px; "
            "}"
            "QComboBox:focus { "
            "    border-color: #388e3c; "
            "    background-color: #ffffff; "
            "}"
            "QComboBox::drop-down { "
            "    border: none; "
            "    width: 25px; "
            "}"
            "QComboBox::down-arrow { "
            "    image: none; "
            "    border-left: 5px solid transparent; "
            "    border-right: 5px solid transparent; "
            "    border-top: 5px solid #1b5e20; "
            "    width: 0px; "
            "    height: 0px; "
            "}"
            "QComboBox QAbstractItemView { "
            "    background-color: #f5fbf5; "
            "    border: 1px solid #a5d6a7; "
            "    border-radius: 4px; "
            "    selection-background-color: #c8e6c9; "
            "    selection-color: #1b5e20; "
            "    outline: none; "
            "    min-height: 30px; "
            "}"
            "QGroupBox { "
            "    background-color: #e8f5e9; "  // 更明显的浅绿色背景
            "    border: 1px solid #a5d6a7; "
            "    border-radius: 5px; "
            "    margin-top: 10px; "
            "    padding-top: 10px; "
            "    color: #2e7d32; "
            "}"
            "QGroupBox::title { "
            "    subcontrol-origin: margin; "
            "    subcontrol-position: top center; "
            "    background-color: #e8f5e9; "
            "    color: #1b5e20; "
            "    font-weight: bold; "
            "    padding: 2px 10px; "
            "    border-radius: 3px; "
            "}"
            // 为单选按钮添加样式
            "QRadioButton { "
            "    color: #1b5e20; "
            "    spacing: 5px; "
            "}"
            "QRadioButton::indicator { "
            "    width: 13px; "
            "    height: 13px; "
            "}"
            "QRadioButton::indicator:unchecked { "
            "    border: 1px solid #a5d6a7; "
            "    border-radius: 6px; "
            "    background-color: white; "
            "}"
            "QRadioButton::indicator:checked { "
            "    border: 1px solid #388e3c; "
            "    border-radius: 6px; "
            "    background-color: #388e3c; "
            "}";
    }
    else {
        // Default - 使用系统默认样式
        styleSheet = "";
    }
    return styleSheet;
}

// 窗口相关
bool Settings::getAutoSaveWindow() const { return m_autoSaveWindow; }
void Settings::setAutoSaveWindow(bool autoSave) { m_autoSaveWindow = autoSave; }

QByteArray Settings::getWindowGeometry() const { return m_windowGeometry; }
void Settings::setWindowGeometry(const QByteArray& geometry) { m_windowGeometry = geometry; }

QByteArray Settings::getWindowState() const { return m_windowState; }
void Settings::setWindowState(const QByteArray& state) { m_windowState = state; }

// 计算器相关
int Settings::getDecimalPlaces() const { return m_decimalPlaces; }
void Settings::setDecimalPlaces(int places) { m_decimalPlaces = places; }

bool Settings::getScientificNotation() const { return m_scientificNotation; }
void Settings::setScientificNotation(bool enabled) { m_scientificNotation = enabled; }