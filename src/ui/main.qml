import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
//import QtQuick.Layouts 1.3

Window {
  visible: true
  width: 640
  height: 480
  title: qsTr("Hello World")

  Component.onCompleted: {
      console.log("qml loaded")
  }

  Connections {
      target: mainViweModel
      onMessage: {
          if (logTextArea.text != "") logTextArea.text = logTextArea.text + "\n"
          logTextArea.text = logTextArea.text + msg
          logTextArea.cursorPosition = logTextArea.length
      }
  }

  //RowLayout {
  Row {
    spacing: 10

    Rectangle {
        height: 400
        width: 300
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
        text: qsTr("Start")
        onClicked: {
            mainViweModel.startI()
        }
      }

      Button {
        text: qsTr("Restart")
        onClicked: {
            mainViweModel.start()
        }
      }

      Button {
        text: qsTr("Shutdown")
      }
    }
  }
}
