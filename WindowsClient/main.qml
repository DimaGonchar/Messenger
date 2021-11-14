import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Telegram Killer")
    Connections {
        target: client

        function onLogIn() {
          stackView.push(page2);
        }
        function onSignUp() {
            infoMessage.setText("You are registered!")
            infoMessage.visible=true
            //stackView.pop(titlePage);
        }
        function onErrorMessage(message)
        {
          infoMessage.setText(message)
          infoMessage.visible=true
        }
    }

    MessageDialog {
        id:infoMessage
        visible:false
        icon:StandardIcon.Information
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

        ColumnLayout {
            anchors{
               left: parent.left
               rightMargin: parent.width/1.5
               right: parent.right
               top: parent.top
               bottom: parent.bottom
            }
            ToolBar {
                id: toolBar
                anchors.left: parent.left
                anchors.right: parent.right
                Layout.preferredHeight: 50
                anchors.top:  parent.top
                RowLayout {
                    anchors.fill: parent
                    Label {
                        text: "Contacts"
                        elide: Label.ElideRight
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        Layout.fillWidth: true
                    }
                    ToolButton {
                        text: qsTr("Logout")
                        onClicked: stackView.pop();
                    }
                }
            }
        }
    }
}

