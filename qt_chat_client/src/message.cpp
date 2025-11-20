#include "message.h"
#include <QUuid>

Message::Message()
    : m_type(MessageType::Incoming)
{
}

Message::Message(const QString &senderId, const QString &content, MessageType type)
    : m_id(QUuid::createUuid().toString()),
      m_senderId(senderId),
      m_content(content),
      m_timestamp(QDateTime::currentDateTime()),
      m_type(type)
{
}

QString Message::id() const
{
    return m_id;
}

QString Message::senderId() const
{
    return m_senderId;
}

QString Message::content() const
{
    return m_content;
}

QDateTime Message::timestamp() const
{
    return m_timestamp;
}

MessageType Message::type() const
{
    return m_type;
}

void Message::setId(const QString &id)
{
    m_id = id;
}

void Message::setSenderId(const QString &senderId)
{
    m_senderId = senderId;
}

void Message::setContent(const QString &content)
{
    m_content = content;
}

void Message::setTimestamp(const QDateTime &timestamp)
{
    m_timestamp = timestamp;
}

void Message::setType(MessageType type)
{
    m_type = type;
}
