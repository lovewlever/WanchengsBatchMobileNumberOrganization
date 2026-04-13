import QtQuick
import QtQuick.Controls
import InstanceTheme

Button {

    property string btnText: ""

    signal clickedX()

    text: btnText
    leftPadding: 8
    rightPadding: 8
    background: Rectangle {
        anchors.fill: parent
        border.width: 1
        border.color: InstanceTheme.outline
        radius: 6
        color: InstanceTheme.primary

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
        }
    }

    onClicked: function() {
        clickedX()
    }
}
