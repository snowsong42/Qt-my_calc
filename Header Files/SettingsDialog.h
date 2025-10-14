#pragma once

#include <QDialog>
#include "Settings.h"

class QComboBox;
class QCheckBox;
class QSpinBox;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(Settings* settings, QWidget* parent = nullptr);

signals:
    void styleChanged(const QString& style);

private slots:
    void applySettings();
    void resetToDefaults();
    void onStyleChanged(int index);

private:
    void createWidgets();
    void setupLayout();
    void loadSettings();

    Settings* m_settings;

    // 样式设置
    QComboBox* styleComboBox;

    // 窗口设置
    QCheckBox* autoSaveCheckBox;

    // 计算器设置
    QSpinBox* decimalPlacesSpinBox;
    QCheckBox* scientificNotationCheckBox;

    // 按钮
    QPushButton* applyButton;
    QPushButton* resetButton;
    QPushButton* cancelButton;
    QPushButton* okButton;
};