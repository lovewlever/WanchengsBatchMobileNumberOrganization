import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import InstanceDialog
import InstanceTheme

Dialog {
    id: idRoot
    modal: true
    visible: true
    dim: true
    width: parent.width
    height: parent.height
    background: Rectangle {
        color: "#5f000000"
    }

    signal okClick(number: int);
    signal cancelClick

    property string errorMsg: ""

    function isNumber(value) {
        let reg = /^[0-9]+$/;
        return reg.test(value);
    }

    Rectangle {
        color: InstanceTheme.surfaceContainer
        radius: 14
        anchors.centerIn: parent
        width: idCL.width + 28
        height: idCL.height + 28
        ColumnLayout {
            id: idCL
            anchors.centerIn: parent
            spacing: 14
            TextField {
                id: idTextField
                Layout.preferredWidth: 200
                Layout.preferredHeight: 40
                placeholderText: "输入每批数量"
                font.pixelSize: 16
                background: Rectangle {
                    radius: 5
                    border.color: InstanceTheme.outline
                    border.width: 1
                    color: InstanceTheme.surface
                }
            }


            Text {
                visible: idRoot.errorMsg !== ""
                font.pointSize: 16
                color: InstanceTheme.error
                text: idRoot.errorMsg
            }

            RowLayout {
                UnionButton {
                    Layout.preferredHeight: 35
                    Layout.fillWidth: true
                    btnText: "好的"
                    onClickedX: function () {
                        let text = idTextField.text;
                        if (idRoot.isNumber(text)) {
                            idRoot.visible = false;
                            idRoot.okClick(parseInt(text));
                        } else {
                            idRoot.errorMsg = "必须为纯数字"
                        }
                    }
                }

                UnionButton {
                    Layout.preferredHeight: 35
                    Layout.fillWidth: true
                    btnText: "取消"
                    onClickedX: function () {
                        idRoot.visible = false;
                        idRoot.cancelClick();
                    }
                }
            }
        }
    }
}
