import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
//import QtQuick.Layouts 1.3

Window {
  visible: true
  width: 640
  height: 480
  title: qsTr("Hello World")

  //RowLayout {
  Row {
    spacing: 10

    Rectangle {
      width: 300
      height: 400
      color: "black"
//      anchors {
//          left: parent.left
//          leftMargin: 10
//      }
    }

    Column {
      spacing: 10
//      anchors {
//          top: parent.top
//      }

      Button {
        text: qsTr("Start")
      }

      Button {
        text: qsTr("Restart")
      }

      Button {
        text: qsTr("Shutdown")
      }
    }
  }
}
