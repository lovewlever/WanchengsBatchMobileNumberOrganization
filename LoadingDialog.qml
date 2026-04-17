import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import InstanceDialog

Dialog {
    modal: true
    visible: InstanceDialog.loadingDialogShow
    dim: true
    width: parent.width
    height: parent.height
    background: Rectangle {
        color: "#5f000000"
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 8
        ProgressBar {
            Layout.preferredWidth: 200
            value: InstanceDialog.loadingDialogProcressValue
        }
        Item { Layout.preferredHeight: 16 }
        Label {
            text: "正在处理..."
            Layout.alignment: Qt.AlignHCenter
            font.pointSize: 13
        }
    }
}
