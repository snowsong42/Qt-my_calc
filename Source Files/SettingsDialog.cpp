#include "SettingsDialog.h"
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>

SettingsDialog::SettingsDialog(Settings* settings, QWidget* parent)
    : QDialog(parent)
    , m_settings(settings)
{
    setWindowTitle("设置");
    setMinimumSize(400, 350);
    setModal(true);

    createWidgets();
    setupLayout();
    loadSettings();

    // 连接信号
    connect(applyButton, &QPushButton::clicked, this, &SettingsDialog::applySettings);
    connect(resetButton, &QPushButton::clicked, this, &SettingsDialog::resetToDefaults);
    connect(cancelButton, &QPushButton::clicked, this, &SettingsDialog::reject);
    connect(okButton, &QPushButton::clicked, this, &SettingsDialog::accept);
    connect(styleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &SettingsDialog::onStyleChanged);
}

void SettingsDialog::createWidgets()
{
    // 样式设置
    styleComboBox = new QComboBox(this);
    styleComboBox->addItem("默认主题", "Default");
    styleComboBox->addItem("浅色主题", "Light");
    styleComboBox->addItem("深色主题", "Dark");
    styleComboBox->addItem("蓝色主题", "Blue");
    styleComboBox->addItem("绿色主题", "Green");

    // 窗口设置
    autoSaveCheckBox = new QCheckBox("自动保存窗口位置和大小", this);

    // 计算器设置
    decimalPlacesSpinBox = new QSpinBox(this);
    decimalPlacesSpinBox->setRange(0, 15);
    decimalPlacesSpinBox->setSuffix(" 位小数");

    scientificNotationCheckBox = new QCheckBox("对大数字使用科学计数法", this);

    // 按钮
    applyButton = new QPushButton("应用", this);
    resetButton = new QPushButton("恢复默认", this);
    cancelButton = new QPushButton("取消", this);
    okButton = new QPushButton("确定", this);
}

void SettingsDialog::setupLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // 样式设置组
    QGroupBox* styleGroup = new QGroupBox("界面样式", this);
    QVBoxLayout* styleLayout = new QVBoxLayout(styleGroup);
    styleLayout->addWidget(new QLabel("选择主题:", this));
    styleLayout->addWidget(styleComboBox);
    styleLayout->addStretch();

    // 窗口设置组
    QGroupBox* windowGroup = new QGroupBox("窗口设置", this);
    QVBoxLayout* windowLayout = new QVBoxLayout(windowGroup);
    windowLayout->addWidget(autoSaveCheckBox);
    windowLayout->addStretch();

    // 计算器设置组
    QGroupBox* calcGroup = new QGroupBox("计算器设置", this);
    QGridLayout* calcLayout = new QGridLayout(calcGroup);
    calcLayout->addWidget(new QLabel("小数位数:", this), 0, 0);
    calcLayout->addWidget(decimalPlacesSpinBox, 0, 1);
    calcLayout->addWidget(scientificNotationCheckBox, 1, 0, 1, 2);

    // 按钮布局
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(applyButton);
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);

    // 添加到主布局
    mainLayout->addWidget(styleGroup);
    mainLayout->addWidget(windowGroup);
    mainLayout->addWidget(calcGroup);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}

void SettingsDialog::loadSettings()
{
    // 加载当前设置
    int styleIndex = styleComboBox->findData(m_settings->getStyle());
    if (styleIndex >= 0) {
        styleComboBox->setCurrentIndex(styleIndex);
    }

    autoSaveCheckBox->setChecked(m_settings->getAutoSaveWindow());
    decimalPlacesSpinBox->setValue(m_settings->getDecimalPlaces());
    scientificNotationCheckBox->setChecked(m_settings->getScientificNotation());
}

// 应用设置
void SettingsDialog::applySettings()
{
    m_settings->setStyle(styleComboBox->currentData().toString());
    m_settings->setAutoSaveWindow(autoSaveCheckBox->isChecked());
    m_settings->setDecimalPlaces(decimalPlacesSpinBox->value());
    m_settings->setScientificNotation(scientificNotationCheckBox->isChecked());

    m_settings->save();

    // 发出样式改变信号
    emit styleChanged(m_settings->getStyle());

    QMessageBox::information(this, "设置", "设置已应用成功！");
}

void SettingsDialog::resetToDefaults()
{
    int result = QMessageBox::question(this, "恢复默认设置",
        "确定要恢复所有设置为默认值吗？",
        QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::Yes) {
        // 重置为默认值
        styleComboBox->setCurrentIndex(0); // 默认主题
        autoSaveCheckBox->setChecked(true);
        decimalPlacesSpinBox->setValue(6);
        scientificNotationCheckBox->setChecked(false);

        applySettings();
    }
}

void SettingsDialog::onStyleChanged(int index)
{
    // 这里可以添加样式预览功能
    // 暂时留空，后续可以扩展
}