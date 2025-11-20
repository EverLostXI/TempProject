#ifndef USER_H
#define USER_H

#include <QString>
#include <QMetaType>

enum class UserStatus {
    Online,
    Offline
};

class User
{
public:
    User();
    User(const QString &id, const QString &name, const QString &avatar = "");
    
    QString id() const;
    QString name() const;
    QString avatar() const;
    UserStatus status() const;
    
    void setId(const QString &id);
    void setName(const QString &name);
    void setAvatar(const QString &avatar);
    void setStatus(UserStatus status);
    
    // For sorting by name
    bool operator<(const User &other) const;
    
private:
    QString m_id;
    QString m_name;
    QString m_avatar;
    UserStatus m_status;
};

Q_DECLARE_METATYPE(User)

#endif // USER_H
