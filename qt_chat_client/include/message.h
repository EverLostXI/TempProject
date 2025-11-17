#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>
#include <QMetaType>

enum class MessageType {
    Incoming,
    Outgoing
};

class Message
{
public:
    Message();
    Message(const QString &senderId, const QString &content, MessageType type);
    
    QString id() const;
    QString senderId() const;
    QString content() const;
    QDateTime timestamp() const;
    MessageType type() const;
    
    void setId(const QString &id);
    void setSenderId(const QString &senderId);
    void setContent(const QString &content);
    void setTimestamp(const QDateTime &timestamp);
    void setType(MessageType type);
    
private:
    QString m_id;
    QString m_senderId;
    QString m_content;
    QDateTime m_timestamp;
    MessageType m_type;
};

Q_DECLARE_METATYPE(Message)

#endif // MESSAGE_H
