#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QDateTime>
#include <QMap>

#include "contactlistmodel.h"
#include "user.h"
#include "message.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
    
    void setCurrentUser(const QString &username);

private slots:
    void onContactSelected(const QModelIndex &index);
    void onSendButtonClicked();
    void onMessageReturnPressed();
    
private:
    Ui::ChatWindow *ui;
    
    QString m_currentUser;
    QString m_selectedContactId;
    ContactListModel *m_contactModel;
    QMap<QString, QList<Message>> m_chatHistory;
    
    // Initialize contacts (simulated data)
    void initContacts();
    
    // Initialize chat history (simulated data)
    void initChatHistory();
    
    // Add message to chat display
    void addMessageToDisplay(const Message &message, const User &sender);
    
    // Format message for display
    QString formatMessage(const Message &message, const User &sender);
    
    // Update contact status display
    void updateContactStatus(const User &contact);
};

#endif // CHATWINDOW_H
