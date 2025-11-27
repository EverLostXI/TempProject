#ifndef CREATEGROUPDIALOG_H
#define CREATEGROUPDIALOG_H

#include <QDialog>
#include <QMap>     // 用于存储 ID -> 名字 的好友列表
#include <QVector>  // 用于返回ID列表
#include <QListWidget> // 包含头文件

namespace Ui {
class CreateGroupDialog;
}

class CreateGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGroupDialog(QWidget *parent = nullptr);
    ~CreateGroupDialog();

    // 公共接口：主窗口通过这个函数把好友列表传进来
    void setFriendsList(const QMap<int, QString>& friends);

    // 公共接口：主窗口通过这些函数获取结果
    QString getGroupName() const;
    QVector<uint8_t> getSelectedMemberIDs() const;
    QListWidget* getFriendsListWidget() const;

private:
    Ui::CreateGroupDialog *ui;
};

#endif // CREATEGROUPDIALOG_H
