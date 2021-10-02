import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import Users 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Secure chat")
    Connections {
        target: client

        function onLogIn() {
          stackView.push(page2);
        }
        function onSignUp() {
           regestratioSucces.visible=true
        }
        function onErrorMessage(message)
        {
          infoMessage.setText(message)
          infoMessage.visible=true
        }
        function onNewUser(name)
        {
        }
    }

    MessageDialog{
        id:regestratioSucces
        visible:false
        icon:StandardIcon.Information
        text: "You are registered!"
        standardButtons: standardButton.Ok
        onAccepted: stackView.pop(titlePage)
    }

    MessageDialog {
        id:infoMessage
        visible:false
        icon:StandardIcon.Critical
        title: "information message"
        standardButtons: StandardButton.Ok
        onAccepted:this.close()
    }

    property int defMargin: 10
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: titlePage
    }

    TitlePage {
      id: titlePage
    }

    RegestrationPage {
    id:regPage
    }

    SimplePage {
        id: page2
        visible: false
        header: ChatToolBar {
            Label {
                text: qsTr("Contacts")
                font.pixelSize: 20
                anchors.centerIn: parent
            }
        }

        ListView {
            id: listView
            anchors.fill: parent
            topMargin: 48
            leftMargin: 48
            bottomMargin: 48
            rightMargin: 48
            spacing: 20
            model: SqlContactModel{}
            delegate: Rectangle {
                width: model.width
                     height: model.height
                     color: "red"
                     border.color: "black"
                     border.width: 5
                     radius: 10
                ItemDelegate {
                text: model.display
                width: listView.width - listView.leftMargin - listView.rightMargin
                Image {
                    id: avatar
                    height: 20
                    width: 20
                    source: "qrc:/" + model.display.replace(" ", "_") + ".png"
                }
             }
        }
    }
  }
}
