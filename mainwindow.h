#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override; // 添加键盘事件处理

private slots:
    void appendNumber();
    void onBackspaceClicked();
    void onClearClicked();
    void onCallClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
