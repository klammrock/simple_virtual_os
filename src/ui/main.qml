import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
//import QtQuick.Layouts 1.3

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

  //RowLayout {
  Row {
    spacing: 10

    Rectangle {
        height: 500
        width: 500
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

    Column {
      spacing: 10
//      anchors {
//          top: parent.top
//      }

      Button {
        text: qsTr("Get Status")
        onClicked: {
            log("HW status: " + (mainViweModel.isStarted ? "started" : "not started"))
        }
      }

      Button {
        text: qsTr("Start")
        onClicked: {
            mainViweModel.start()
        }
      }

      Button {
        text: qsTr("Restart")
        onClicked: {
            mainViweModel.restart()
        }
      }

      Button {
        text: qsTr("Stop")
        onClicked: {
            mainViweModel.stop()
        }
      }
    }
  }
}
