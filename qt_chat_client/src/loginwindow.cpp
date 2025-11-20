#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    
    // Set window icon
    setWindowIcon(QIcon(":/icons/login.png"));
    
    // Set focus to username field
    ui->usernameLineEdit->setFocus();
    
    // Connect enter key to login button
    connect(ui->usernameLineEdit, &QLineEdit::returnPressed, this, &LoginWindow::onLoginButtonClicked);
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &LoginWindow::onLoginButtonClicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onLoginButtonClicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both username and password.");
        return;
    }
    
    if (validateLogin(username, password)) {
        emit loginSuccess(username);
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
        ui->passwordLineEdit->clear();
        ui->passwordLineEdit->setFocus();
    }
}

bool LoginWindow::validateLogin(const QString &username, const QString &password)
{
    // In a real application, this would connect to a server for authentication
    // For demo purposes, we'll use hardcoded credentials
    
    // Valid credentials (demo only)
    QHash<QString, QString> validUsers = {
        {"user1", "password1"},
        {"user2", "password2"},
        {"admin", "admin123"}
    };
    
    return validUsers.contains(username) && validUsers[username] == password;
}
