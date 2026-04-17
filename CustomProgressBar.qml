import QtQuick
import QtQuick.Controls
import InstanceTheme

ProgressBar {
    id: control
    value: process  // 当前进度 (0.0 到 1.0)
    implicitWidth: 300
    implicitHeight: 24

    property var process: 0.6

    // 1. 背景部分 (蓝底)
    background: Rectangle {
        implicitWidth: 300
        implicitHeight: 24
        color: InstanceTheme.secondaryContainer         // 蓝底颜色
        radius: height / 2        // 实现圆角 (胶囊形状)
        //border.color: "transparent"
        //border.width: 1
    }

    // 2. 进度部分 (绿色进度条)
    contentItem: Item {
        implicitWidth: 300
        implicitHeight: 24

        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            color: InstanceTheme.primary      // 绿色进度条
            radius: height / 2    // 同样设置圆角
            
            // 添加一个简单的平滑动画
            Behavior on width {
                NumberAnimation { duration: 250; easing.type: Easing.OutCubic }
            }
        }
    }

    // 3. 可选：百分比文字
    Text {
        anchors.centerIn: parent
        text: Math.floor(control.value * 100) + "%"
        color: "white"
        font.bold: true
        font.pixelSize: 12
    }
}