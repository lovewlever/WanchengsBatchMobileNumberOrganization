import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import InstanceTheme
import InstanceDialog

Dialog {
    modal: true
    visible: InstanceDialog.reminderDialogShow
    dim: true
    width: parent.width
    height: parent.height
    background: Rectangle {
        color: "#5f000000"
    }

    Rectangle {
        color: InstanceTheme.surfaceContainer
        radius: 12
        anchors.centerIn: parent
        width: idCL.width + 28
        height: idCL.height + 28
        ColumnLayout {
            id: idCL
            anchors.centerIn: parent
            spacing: 14

            Text {
                text: "提醒"
                font.pointSize: 14
                color: InstanceTheme.onSurface
            }

            Text {
                text: InstanceDialog.reminderContent
                font.pointSize: 12
                color: InstanceTheme.onSurface
            }

            UnionButton {
                Layout.preferredHeight: 35
                Layout.preferredWidth: 200
                btnText: "OK"
                onClickedX: function () {
                    InstanceDialog.reminderDialogShow = false;
                }
            }

        }
    }
}
