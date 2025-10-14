#pragma once

#include <QString>
#include <QSettings>

class Settings
{
public:
    Settings();
    void load();
    void save();

    // 样式相关
    QString getStyle() const;
    void setStyle(const QString& style);
    QString styleCast(const QString& style) const;

    // 窗口相关
    bool getAutoSaveWindow() const;
    void setAutoSaveWindow(bool autoSave);

    QByteArray getWindowGeometry() const;
    void setWindowGeometry(const QByteArray& geometry);

    QByteArray getWindowState() const;
    void setWindowState(const QByteArray& state);

    // 计算器相关
    int getDecimalPlaces() const;
    void setDecimalPlaces(int places);

    bool getScientificNotation() const;
    void setScientificNotation(bool enabled);

private:
    QString m_style;
    bool m_autoSaveWindow;
    QByteArray m_windowGeometry;
    QByteArray m_windowState;
    int m_decimalPlaces;
    bool m_scientificNotation;
};