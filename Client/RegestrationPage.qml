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
            id:userLogin
            selectByMouse: true
            placeholderText: "login"
            Layout.fillWidth: true
        }

        TextField {
            id:userPassword
             selectByMouse: true
            placeholderText: "password"
            Layout.fillWidth: true
        }

        TextField {
            id:userName
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
          //Layout.alignment: Qt.AlignCenter
//          palette{
//              button:"green"
//          }

          onClicked: {
              client.regestration(userLogin.text, userPassword.text, userName.text)
              //stackView.pop(titlePage);
              userLogin.clear()
              userPassword.clear()
              userName.clear()
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


