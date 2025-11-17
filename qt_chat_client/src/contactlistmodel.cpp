#include "contactlistmodel.h"

ContactListModel::ContactListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ContactListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_contacts.size();
}

QVariant ContactListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_contacts.size())
        return QVariant();

    const User &contact = m_contacts[index.row()];

    switch (role) {
    case IdRole:
        return contact.id();
    case NameRole:
        return contact.name();
    case AvatarRole:
        return contact.avatar().isEmpty() ? ":/icons/user.png" : contact.avatar();
    case StatusRole:
        return static_cast<int>(contact.status());
    case StatusTextRole:
        return contact.status() == UserStatus::Online ? "Online" : "Offline";
    default:
        return QVariant();
    }
}

void ContactListModel::addContact(const User &contact)
{
    beginInsertRows(QModelIndex(), m_contacts.size(), m_contacts.size());
    m_contacts.append(contact);
    
    // Sort contacts by name after adding
    std::sort(m_contacts.begin(), m_contacts.end());
    
    endInsertRows();
}

void ContactListModel::addContacts(const QList<User> &contacts)
{
    beginInsertRows(QModelIndex(), m_contacts.size(), m_contacts.size() + contacts.size() - 1);
    m_contacts.append(contacts);
    
    // Sort contacts by name after adding
    std::sort(m_contacts.begin(), m_contacts.end());
    
    endInsertRows();
}

void ContactListModel::clearContacts()
{
    beginResetModel();
    m_contacts.clear();
    endResetModel();
}

User ContactListModel::getContact(int index) const
{
    if (index >= 0 && index < m_contacts.size())
        return m_contacts[index];
    return User();
}

User ContactListModel::getContactById(const QString &id) const
{
    for (const User &contact : m_contacts) {
        if (contact.id() == id)
            return contact;
    }
    return User();
}

QHash<int, QByteArray> ContactListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[AvatarRole] = "avatar";
    roles[StatusRole] = "status";
    roles[StatusTextRole] = "statusText";
    return roles;
}
