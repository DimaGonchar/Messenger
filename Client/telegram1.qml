import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Chat Client")

    Connections {
        target: client
        function onNewMessage(str) {
            listModelMessages.append({
                                         message: str + ""
                                     })
        }
    }
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: login
                placeholderText: qsTr("Login")
                Layout.fillWidth: true
            }
            TextField {
                id: password
                placeholderText: qsTr("Password")
                Layout.fillWidth: true
            }
            Button {
                id: buttonLogin
                text: qsTr("login")
                onClicked:{
                    client.login(login.text, password.text)
                    login.clear()
                    password.clear()
                }
            }
                Button {
                    id:buttonRegistration
                    text:qsTr("registration")
                    onClicked: {
                        client.registration(login.text,password.text)
                        login.clear()
                        password.clear()
                    }
                }
        }
       ListView {
           Layout.fillHeight: true
            Layout.fillWidth: true
           clip: true
           model: ListModel {
             id: listModelMessages
         }
            delegate: ItemDelegate {
               text: message
            }
            ScrollBar.vertical: ScrollBar {}
        }
        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: message
                placeholderText: qsTr("write here ...")
                Layout.fillWidth: true
                onAccepted: buttonSend.clicked()
            }
            Button {
                id: buttonSend
                text: qsTr("Send")
                onClicked: {
                    client.sendMessage(message.text)
                    message.clear()
                }
            }
        }
    }
}
