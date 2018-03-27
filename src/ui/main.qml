import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Window {
  visible: true
  width: 800
  height: 600
  title: qsTr("Hello World")

  Component.onCompleted: {
      console.log("qml loaded")
  }

  function log(msg) {
      var date = Qt.formatTime(new Date(), "HH:mm:ss.zzz")
      logTextArea.append(date + ": " + msg);
  }

  Connections {
      target: mainViweModel
      onMessage: {
          log("message from HW: " + msg)
      }
  }

  RowLayout {
    anchors.fill: parent

    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: "black"

        ScrollView {
            anchors.fill: parent
            //clip: true
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn

            TextArea {
                id: logTextArea
                color: "green"
                readOnly: true
            }
        }
    }

    ColumnLayout {
      spacing: 10
      Layout.margins: 10
      Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

      Button {
        text: qsTr("Get Status")
        onClicked: {
            log("HW status: " + (mainViweModel.isStarted ? "started" : "not started"))
        }
      }

      Button {
        text: qsTr("Start")
        onClicked: {
            mainViweModel.startHW()
        }
      }

      Button {
        text: qsTr("Restart")
        onClicked: {
            mainViweModel.restartHW()
        }
      }

      Button {
        text: qsTr("Stop")
        onClicked: {
            mainViweModel.stopHW()
        }
      }
    }
  }
}
