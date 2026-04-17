import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import InstanceDialog
import InstanceTheme

Dialog {
    modal: true
    visible: InstanceDialog.loadingDialogShow
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
            CustomProgressBar {
                id: control
                Layout.preferredWidth: 200
                process: 0.8

            }

            Label {
                text: "正在处理..."
                Layout.alignment: Qt.AlignHCenter
                font.pointSize: 13
            }
        }
    }
}
