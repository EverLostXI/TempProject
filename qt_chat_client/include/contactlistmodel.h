#ifndef CONTACTLISTMODEL_H
#define CONTACTLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "user.h"

class ContactListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ContactRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        AvatarRole,
        StatusRole,
        StatusTextRole
    };

    explicit ContactListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    void addContact(const User &contact);
    void addContacts(const QList<User> &contacts);
    
    // Clear data:
    void clearContacts();
    
    // Get contact by index:
    User getContact(int index) const;
    
    // Get contact by id:
    User getContactById(const QString &id) const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<User> m_contacts;
};

#endif // CONTACTLISTMODEL_H
