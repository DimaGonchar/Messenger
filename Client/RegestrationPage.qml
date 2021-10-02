import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Page {
    visible: false
    ColumnLayout {
        anchors.fill:  parent
        anchors.margins: defMargin
        spacing: defMargin

        Item {
            height:20
        }

        TextField {
            id:login
            selectByMouse: true
            placeholderText: "login"
            Layout.fillWidth: true
        }

        TextField {
            id:password
            selectByMouse: true
            placeholderText: "password"
            Layout.fillWidth: true
        }
        TextField {
            id:confirmPassword
            selectByMouse: true
            placeholderText: "confirm password"
            Layout.fillWidth: true
        }

        TextField {
            id:name
            selectByMouse: true
            placeholderText: "name"
            Layout.fillWidth: true
        }
      RowLayout {
       Layout.alignment:  Qt.AlignCenter
        Button {
          id: ok
          text: "ok"
          highlighted: true

          onClicked: {
              client.regestration(login.text, password.text, confirmPassword.text, name.text)
              login.clear()
              password.clear()
              confirmPassword.clear()
              name.clear()
          }
      }
        Button {
           id: back
           text:"back"
           highlighted: true
           //Layout.alignment: Qt.AlignCenter
           onClicked: stackView.pop(titlePage)
      }
    }
  }
}

