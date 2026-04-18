import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import InstanceTheme
import Qt.labs.platform

Window {
    id: window
    width: 640
    height: 640
    visible: true
    title: qsTr("万成的手机号批量处理")
    color: InstanceTheme.background

    property var dropAreaColor: "transparent"

    PhoneNumberImportrer {
        id: objPhoneNumberImporter
    }

    ColumnLayout {
        anchors.margins: 8
        anchors.fill: parent

        RowLayout {
            Image {
                source: "qrc:/images/ic_hbzx_11.png"
                Layout.preferredHeight: 35
                Layout.preferredWidth: 35
            }

            FileDialog {
                id: fileDialog
                nameFilters: ["Text files (*.txt *.text)"]
                folder: StandardPaths.writableLocation(StandardPaths.DownloadLocation)
                onAccepted: function () {
                    objPhoneNumberImporter.importPhoneFile(fileDialog.file);
                }
            }

            UnionButton {
                btnText: "导入Text文件"
                Layout.preferredHeight: 35
                onClickedX: function () {
                    fileDialog.open();
                    console.log("导入Text文件-Click");
                }
            }

            UnionButton {
                btnText: "号码乱序"
                Layout.preferredHeight: 35
                onClickedX: function () {
                    objPhoneNumberImporter.phoneDisorder();
                }
            }

            UnionButton {
                btnText: "去重"
                Layout.preferredHeight: 35
                onClickedX: function () {
                    objPhoneNumberImporter.phoneDeduplication();
                }
            }

            UnionButton {
                btnText: "清除非手机号"
                Layout.preferredHeight: 35
                onClickedX: function () {
                    objPhoneNumberImporter.removeNonPhoneNumbers();
                }
            }

            UnionButton {
                btnText: "清空号码"
                Layout.preferredHeight: 35
                onClickedX: function () {
                    objPhoneNumberImporter.cleanPhone();
                }
            }
        }

        Item {
            Layout.preferredHeight: 4
        }

        Rectangle {
            color: InstanceTheme.outline
            Layout.fillWidth: true
            Layout.preferredHeight: 1
        }

        Rectangle {
            Layout.preferredHeight: 30
            Layout.fillWidth: true
            color: InstanceTheme.primaryContainer
            radius: 4

            Text {
                text: objPhoneNumberImporter.topMsg
                color: InstanceTheme.error
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                leftPadding: 8
                font.pointSize: 13
            }
        }

        Rectangle {
            color: InstanceTheme.outline
            Layout.fillWidth: true
            Layout.preferredHeight: 1
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 8
            border.width: 1
            border.color: InstanceTheme.outline
            color: InstanceTheme.surfaceContainer
            ListView {
                anchors.margins: 8
                anchors.fill: parent
                orientation: Qt.Vertical
                model: objPhoneNumberImporter.phoneNumberListModelPtr
                clip: true
                delegate: Rectangle {
                    height: 30
                    width: idTextPhone.width
                    color: "transparent"

                    Text {
                        id: idTextPhone
                        text: qsTr(phone)
                        color: InstanceTheme.onSurface
                        leftPadding: 8
                        rightPadding: 8
                    }
                }
            }
        }

        Text {
            text: qsTr("当前原始号码数量：" + objPhoneNumberImporter.phoneNumber)
            color: InstanceTheme.primary
            font.pointSize: 12
        }

        Rectangle {
            color: InstanceTheme.outline
            Layout.fillWidth: true
            Layout.preferredHeight: 1
        }

        RowLayout {

            UnionButton {
                btnText: "按地区导出"
                Layout.preferredHeight: 35
                onClickedX: function () {
                    objPhoneNumberImporter.exportByRegion();
                }
            }
            UnionButton {
                btnText: "按运营商导出"
                Layout.preferredHeight: 35
                onClickedX: function () {
                    objPhoneNumberImporter.exportByCarrier();
                }
            }

            UnionButton {
                btnText: "分批导出"
                Layout.preferredHeight: 35
                onClickedX: function () {
                    let component = Qt.createComponent("InputExportInBatchNumberDialog.qml");
                    console.log(component.errorString());
                    if (component.status == Component.Ready) {
                        let obj = component.createObject(window);
                        obj.okClick.connect(function (number) {
                            obj.destroy();
                            objPhoneNumberImporter.exportByInBatch(number);
                        });
                        obj.cancelClick.connect(function () {
                            obj.destroy();
                        });
                    }
                }
            }

            UnionButton {
                btnText: "全部导出"
                Layout.preferredHeight: 35
                onClickedX: function () {
                    objPhoneNumberImporter.exportByAll();
                }
            }
        }
    }

    Rectangle {
        color: window.dropAreaColor
        anchors.fill: parent
        DropArea {
            anchors.fill: parent
            onEntered: function (drag) {
                window.dropAreaColor = "#7F000000";
            }
            onExited: function () {
                window.dropAreaColor = "transparent";
            }

            onDropped: function (drag) {
                window.dropAreaColor = "transparent";
                let filePaths = "";
                for (let i = 0; i < drag.urls.length; i++) {
                    let url = drag.urls[i];
                    objPhoneNumberImporter.importPhoneFile(url);
                }
            }
        }
    }

    LoadingDialog {
        id: idLoadingDialog
    }

    CustomReminderDialog {}
}
