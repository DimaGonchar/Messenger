import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Page {
//property alias backgroundColor:backgroundRect
//    background: Rectangle {
//        id: backgroundRect
//        color: "green"
//    }
    ColumnLayout {
        id: loGeneral
        anchors.fill:  parent
        anchors.margins: defMargin
        spacing: defMargin

        Label {
            text: "Secure Chat"
            font.pointSize: 14
            font.bold: true
            Layout.alignment: Qt.AlignCenter

        }
        Item {
            height:20
        }

        TextField {
            id:login
            placeholderText: "Enter login"
            Layout.fillWidth: true
        }

        TextField {
            id:password
            placeholderText: "Enter password"
            Layout.fillWidth: true
        }
        Button {
          id: buttonLogin
          text: "Login"
          highlighted: true
          Layout.alignment: Qt.AlignCenter
          onClicked: {
              client.login(login.text, password.text)
              login.clear()
              password.clear()
          }
        }
        Label {
           text: "---or---"
           font.pointSize: 10
           Layout.alignment: Qt.AlignCenter
        }
        Button {
          id:buttonSignUp
          text: "Sign up"
          highlighted: true
          Layout.alignment: Qt.AlignCenter
          onClicked: {
              stackView.push(regPage)
          }
        }
     }
}
