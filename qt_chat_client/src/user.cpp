#include "user.h"

User::User()
    : m_status(UserStatus::Offline)
{
}

User::User(const QString &id, const QString &name, const QString &avatar)
    : m_id(id),
      m_name(name),
      m_avatar(avatar),
      m_status(UserStatus::Offline)
{
}

QString User::id() const
{
    return m_id;
}

QString User::name() const
{
    return m_name;
}

QString User::avatar() const
{
    return m_avatar;
}

UserStatus User::status() const
{
    return m_status;
}

void User::setId(const QString &id)
{
    m_id = id;
}

void User::setName(const QString &name)
{
    m_name = name;
}

void User::setAvatar(const QString &avatar)
{
    m_avatar = avatar;
}

void User::setStatus(UserStatus status)
{
    m_status = status;
}

bool User::operator<(const User &other) const
{
    return m_name.compare(other.m_name, Qt::CaseInsensitive) < 0;
}
