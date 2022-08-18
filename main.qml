import QtQuick 2.15
import QtQuick.Window 2.15
import TagModel 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    ListView{
        Rectangle{
            anchors.fill: parent
            z: -1
            color: "red"
        }
        id: tagView
        anchors.fill: parent
        clip: true
        spacing: 50
        model: TagModel
        delegate: Rectangle{
            Text{
                id: groupNametxt
                text: groupName
            }
            Text{
                y: 50
                id: tagNametxt
                text: tagName
            }
            Text{
                y: 100
                id: tagTimetxt
                text: tagTime
            }
            Text{
                y: 150
                id: tagValuetxt
                text: tagValue
            }
        }

    }
}
