#include <QApplication>
#include <QMainWindow>
#include <QDebug>

#include "include/loginwindow.h"
#include "include/chatwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application style
    app.setStyle("Fusion");
    
    // Create login window
    LoginWindow loginWindow;
    
    // Create chat window (initially hidden)
    ChatWindow chatWindow;
    
    // Connect login success signal to chat window
    QObject::connect(&loginWindow, &LoginWindow::loginSuccess, [&](const QString &username) {
        loginWindow.hide();
        chatWindow.setCurrentUser(username);
        chatWindow.show();
    });
    
    // Show login window
    loginWindow.show();
    
    return app.exec();
}
