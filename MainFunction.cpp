#include "my_calc.h"

void my_calc::keyPressEvent(QKeyEvent* event)
{
    // 处理键盘按键事件
    switch (event->key()) {
    case Qt::Key_0:
        btn0->click();
        break;
    case Qt::Key_1:
        btn1->click();
        break;
    case Qt::Key_2:
        btn2->click();
        break;
    case Qt::Key_3:
        btn3->click();
        break;
    case Qt::Key_4:
        btn4->click();
        break;
    case Qt::Key_5:
        btn5->click();
        break;
    case Qt::Key_6:
        btn6->click();
        break;
    case Qt::Key_7:
        btn7->click();
        break;
    case Qt::Key_8:
        btn8->click();
        break;
    case Qt::Key_9:
        btn9->click();
        break;
    case Qt::Key_Percent:  //%号
        btnPercent->click();
        break;
    case Qt::Key_Period: // .号
        btnPeriod->click();
        break;
    case Qt::Key_Backspace:
        btnBackspace->click();
        break;
    case Qt::Key_Delete:
        btnClear->click();
        break;
    case Qt::Key_ParenLeft: //(
        break;
    case Qt::Key_ParenRight:    //)
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        btnCommit->click();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void my_calc::appendNumber()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString currentText = displayLineEdit->text();
        QString newText = currentText + button->text();
        displayLineEdit->setText(newText);
    }
}

void my_calc::onBackspaceClicked()
{
    QString currentText = displayLineEdit->text();
    if (!currentText.isEmpty()) {
        currentText.chop(1); // 移除最后一个字符
        displayLineEdit->setText(currentText);
    }
}

void my_calc::onClearClicked()
{
    displayLineEdit->clear();
}

void my_calc::onCommitClicked()
{
    QString number = displayLineEdit->text();
    if (!number.isEmpty()) {
        // 这里可以实现实际的拨号逻辑
        if (number == "7355608") {
            QMessageBox::information(this, "拨号中...",
                "密码正确:7355608\n炸弹已经安放!",
                QMessageBox::Ok);
            this->close();
        }
        else {
            QMessageBox::information(this, "拨号失败",
                QString("密码错误: %1\n炸弹安放失败!").arg(number),
                QMessageBox::Ok);
        }
        // 在实际应用中，这里可能会调用系统API或发送网络请求
    }
}