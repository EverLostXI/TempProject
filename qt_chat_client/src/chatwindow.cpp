#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include <QScrollBar>
#include <QFile>
#include <QTextStream>

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow),
    m_contactModel(new ContactListModel(this))
{
    ui->setupUi(this);
    
    // Set window icon
    setWindowIcon(QIcon(":/icons/login.png"));
    
    // Set up contacts list view
    ui->contactsListView->setModel(m_contactModel);
    
    // Create and set delegate for contacts list
    QFile delegateFile(":/qml/ContactItemDelegate.qml");
    if (delegateFile.open(QIODevice::ReadOnly)) {
        QByteArray delegateData = delegateFile.readAll();
        delegateFile.close();
        
        // Note: In a real project, you would use QQmlApplicationEngine or QQuickWidget
        // to load QML delegates. For simplicity, we're using a basic approach here.
        // This is just a placeholder to show where the delegate would be set.
    }
    
    // Initialize contacts and chat history
    initContacts();
    initChatHistory();
    
    // Connect actions
    connect(ui->actionAbout, &QAction::triggered, this, [=]() {
        QMessageBox::about(this, "About Chat Client", "Simple Chat Client\nVersion 1.0.0");
    });
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::setCurrentUser(const QString &username)
{
    m_currentUser = username;
    setWindowTitle(QString("Chat Client - %1").arg(username));
}

void ChatWindow::onContactSelected(const QModelIndex &index)
{
    if (!index.isValid())
        return;
    
    User selectedContact = m_contactModel->getContact(index.row());
    m_selectedContactId = selectedContact.id();
    
    // Update contact info display
    ui->contactNameLabel->setText(selectedContact.name());
    updateContactStatus(selectedContact);
    
    // Clear chat display
    ui->chatTextEdit->clear();
    
    // Load chat history
    if (m_chatHistory.contains(m_selectedContactId)) {
        const QList<Message> &messages = m_chatHistory[m_selectedContactId];
        for (const Message &message : messages) {
            addMessageToDisplay(message, m_contactModel->getContactById(message.senderId()));
        }
    } else {
        ui->chatTextEdit->append("No messages yet. Start the conversation!");
    }
    
    // Enable message input
    ui->messageLineEdit->setEnabled(true);
    ui->sendButton->setEnabled(true);
    ui->messageLineEdit->setFocus();
}

void ChatWindow::onSendButtonClicked()
{
    if (m_selectedContactId.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a contact first.");
        return;
    }
    
    QString messageText = ui->messageLineEdit->text().trimmed();
    if (messageText.isEmpty())
        return;
    
    // Create message
    Message message(m_currentUser, messageText, MessageType::Outgoing);
    
    // Add to chat history
    m_chatHistory[m_selectedContactId].append(message);
    
    // Add to display
    User currentUser(m_currentUser, m_currentUser);
    addMessageToDisplay(message, currentUser);
    
    // Clear input
    ui->messageLineEdit->clear();
    
    // Simulate receiving a response after a delay
    QTimer::singleShot(1000, this, [=]() {
        // Create a simple response
        QString responses[] = {
            "Hello!",
            "How are you?",
            "I'm good, thanks.",
            "What's up?",
            "Not much, just chatting.",
            "That's interesting.",
            "Tell me more.",
            "I see.",
            "Cool!",
            "Okay."
        };
        
        int randomIndex = qrand() % 10;
        QString responseText = responses[randomIndex];
        
        // Create response message
        User selectedContact = m_contactModel->getContactById(m_selectedContactId);
        Message response(selectedContact.id(), responseText, MessageType::Incoming);
        
        // Add to chat history
        m_chatHistory[m_selectedContactId].append(response);
        
        // Add to display
        addMessageToDisplay(response, selectedContact);
    });
}

void ChatWindow::onMessageReturnPressed()
{
    onSendButtonClicked();
}

void ChatWindow::initContacts()
{
    // Add some sample contacts
    QList<User> contacts;
    
    contacts.append(User("user1", "Alice Smith", ":/icons/user.png"));
    contacts.append(User("user2", "Bob Johnson", ":/icons/user.png"));
    contacts.append(User("user3", "Charlie Brown", ":/icons/user.png"));
    contacts.append(User("user4", "David Wilson", ":/icons/user.png"));
    contacts.append(User("user5", "Eve Davis", ":/icons/user.png"));
    contacts.append(User("user6", "Frank Miller", ":/icons/user.png"));
    contacts.append(User("user7", "Grace Taylor", ":/icons/user.png"));
    contacts.append(User("user8", "Heidi Anderson", ":/icons/user.png"));
    
    // Set some contacts as online
    contacts[0].setStatus(UserStatus::Online);
    contacts[1].setStatus(UserStatus::Online);
    contacts[3].setStatus(UserStatus::Online);
    contacts[6].setStatus(UserStatus::Online);
    
    // Add to model
    m_contactModel->addContacts(contacts);
}

void ChatWindow::initChatHistory()
{
    // Add some sample chat history
    QList<Message> aliceMessages;
    aliceMessages.append(Message("user1", "Hi there!", MessageType::Incoming));
    aliceMessages.append(Message(m_currentUser, "Hello Alice!", MessageType::Outgoing));
    aliceMessages.append(Message("user1", "How are you doing today?", MessageType::Incoming));
    aliceMessages.append(Message(m_currentUser, "I'm doing well, thanks. How about you?", MessageType::Outgoing));
    
    QList<Message> bobMessages;
    bobMessages.append(Message("user2", "Hey! Did you see the game last night?", MessageType::Incoming));
    bobMessages.append(Message(m_currentUser, "Yes! It was amazing!", MessageType::Outgoing));
    
    QList<Message> charlieMessages;
    charlieMessages.append(Message("user3", "Good morning!", MessageType::Incoming));
    
    // Store in chat history
    m_chatHistory["user1"] = aliceMessages;
    m_chatHistory["user2"] = bobMessages;
    m_chatHistory["user3"] = charlieMessages;
}

void ChatWindow::addMessageToDisplay(const Message &message, const User &sender)
{
    QString formattedMessage = formatMessage(message, sender);
    ui->chatTextEdit->append(formattedMessage);
    
    // Scroll to bottom
    QScrollBar *scrollBar = ui->chatTextEdit->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}

QString ChatWindow::formatMessage(const Message &message, const User &sender)
{
    QDateTime timestamp = message.timestamp();
    QString timeString = timestamp.toString("hh:mm AP");
    
    QString messageHtml;
    
    if (message.type() == MessageType::Incoming) {
        messageHtml = QString("<p style=\"margin: 5px 0; color: #0d47a1;\"><strong>%1</strong> <span style=\"font-size: 10px; color: #666666;\">%2</span></p>")
            .arg(sender.name())
            .arg(timeString);
        messageHtml += QString("<p style=\"margin: 0 0 10px 20px; padding: 8px; background-color: #f5f5f5; border-radius: 10px;\">%1</p>")
            .arg(message.content().toHtmlEscaped());
    } else {
        messageHtml = QString("<p style=\"margin: 5px 0; text-align: right; color: #4caf50;\"><span style=\"font-size: 10px; color: #666666;\">%2</span> <strong>%1</strong></p>")
            .arg(sender.name())
            .arg(timeString);
        messageHtml += QString("<p style=\"margin: 0 20px 10px 0; padding: 8px; background-color: #e3f2fd; border-radius: 10px; text-align: right;\">%1</p>")
            .arg(message.content().toHtmlEscaped());
    }
    
    return messageHtml;
}

void ChatWindow::updateContactStatus(const User &contact)
{
    if (contact.status() == UserStatus::Online) {
        ui->contactStatusLabel->setText("Online");
        ui->contactStatusLabel->setStyleSheet("color: #4caf50; font-size: 12px;");
    } else {
        ui->contactStatusLabel->setText("Offline");
        ui->contactStatusLabel->setStyleSheet("color: #f44336; font-size: 12px;");
    }
}
