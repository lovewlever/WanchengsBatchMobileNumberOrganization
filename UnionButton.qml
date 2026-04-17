import QtQuick
import QtQuick.Controls
import InstanceTheme

Button {
    id: idUnionBtn
    property string btnText: ""

    signal clickedX

    leftPadding: 8
    rightPadding: 8
    topPadding: 0
    bottomPadding: 0
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
    contentItem: Text {
        text: idUnionBtn.btnText
        color: InstanceTheme.onPrimary
        font.pointSize: 10
        width: parent.width
        anchors.centerIn: parent
        verticalAlignment: Qt.AlignVCenter
        horizontalAlignment: Qt.AlignHCenter
    }

    onClicked: function () {
        clickedX();
    }
}
