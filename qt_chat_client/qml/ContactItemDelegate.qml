import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: contactItem
    width: parent.width
    height: 60
    
    property string name: ""
    property string statusText: ""
    property int status: 0 // 0 = Offline, 1 = Online
    property string avatar: "qrc:/icons/user.png"
    
    RowLayout {
        anchors.fill: parent
        spacing: 10
        padding: 5
        
        Image {
            id: avatarImage
            source: avatar
            width: 40
            height: 40
            fillMode: Image.PreserveAspectCrop
            clip: true
            radius: 20
            
            Rectangle {
                id: statusIndicator
                width: 12
                height: 12
                radius: 6
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                border.width: 2
                border.color: "white"
                color: status === 1 ? "#4caf50" : "#f44336"
            }
        }
        
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 2
            
            Text {
                text: name
                font.bold: true
                font.pixelSize: 14
                color: "#333333"
            }
            
            Text {
                text: statusText
                font.pixelSize: 12
                color: status === 1 ? "#4caf50" : "#666666"
            }
        }
    }
    
    Rectangle {
        width: parent.width
        height: 1
        color: "#eeeeee"
        anchors.bottom: parent.bottom
    }
}
