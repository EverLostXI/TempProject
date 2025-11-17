#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccess(const QString &username);

private slots:
    void onLoginButtonClicked();

private:
    Ui::LoginWindow *ui;
    
    // Validate username and password
    bool validateLogin(const QString &username, const QString &password);
};

#endif // LOGINWINDOW_H
