import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Telegram Killer")
    Connections {
        target: client
        function onNewMessage(str) {
            listModelMessages.append({
                                         message: str + ""
                                     })
        }
        function onLogIn() {
          stackView.push(page2);
        }
    }

    property int defMargin: 10
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem:  page1
    }

    SimplePage {
        id: page1
        backgroundColor: "steelblue"
        ColumnLayout {
            id: loGeneral
            anchors.fill:  parent
            anchors.margins: defMargin
            spacing: defMargin

            Label {
                text: "Telegram Killer"
                font.pointSize: 14
                font.bold: true
                Layout.alignment: Qt.AlignCenter

            }
            Item {
                height:20
            }
            Label {
                text: "Login"
            }
            TextField {
                id:login
                placeholderText: "Enter your login"
                Layout.fillWidth: true
            }
            Label {
                text: "Password"
            }
            TextField {
                id:password
                placeholderText: "Enter your password"
                Layout.fillWidth: true
            }
            Button {
              id: buttonLogin
              text: "Login"
              Layout.alignment: Qt.AlignCenter
              onClicked: {
                  client.login(login.text, password.text)
                  //login.clear()
                 // password.clear()
                 //stackView.push(page2);
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
              Layout.alignment: Qt.AlignCenter
              onClicked: {
                  client.registration(login.text, password.text)
                  //stackView.push(page2);
              }
            }
         }
    }
    SimplePage {
        id: page2
        visible: false
        //backgroundColor: "steelblue"
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
                    ToolButton {
                        text: qsTr("Refresh")
                        onClicked: {

                        }
                    }
                    ToolButton {
                        text: qsTr("<")
                        onClicked: {

                        }
                    }

                }
            }
            ListView {
                        id: listViewContact
                        anchors.top: ToolBar.bottom
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        spacing: 20
                        model: ["Albert Einstein", "Ernest Hemingway", "Hans Gude"]
                        delegate: ItemDelegate {
                            text: modelData
                            width: listView.width - listView.leftMargin - listView.rightMargin
                            height: avatar.implicitHeight
                            leftPadding: avatar.implicitWidth + 32
                        }
                    }
        }
        ColumnLayout {
            anchors{
               left: parent.left
               leftMargin: parent.width/3
               right: parent.right
               top: parent.top
               bottom: parent.bottom
            }
            ListView {
                id: listView
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.margins: pane.leftPadding + messageField.leftPadding
                displayMarginBeginning: 40
                displayMarginEnd: 40
                verticalLayoutDirection: ListView.BottomToTop
                spacing: 12
                model: 10
                delegate: Row {
                    readonly property bool sentByMe: index % 2 == 0

                    anchors.right: sentByMe ? listView.contentItem.right : undefined
                    spacing: 6

                    Rectangle {
                        width: 80
                        height: 40
                        color: sentByMe ? "lightgrey" : "steelblue"

                        Label {
                            anchors.centerIn: parent
                            text: index
                            color: sentByMe ? "black" : "white"
                        }
                    }
                }

                ScrollBar.vertical: ScrollBar {}
            }
            Pane {
               id: pane
               Layout.fillWidth: true

               RowLayout {
                   width: parent.width

                   TextArea {
                       id: messageField
                       Layout.fillWidth: true
                       placeholderText: qsTr("write your message")
                       wrapMode: TextArea.Wrap
                   }

                   Button {
                       id: sendButton
                       text: qsTr("Send")
                       enabled: messageField.length > 0
                   }
               }
           }
       }

        //buttonText: "Logout"
        //onButtonClicked:  {
           //stackView.pop()
        //}
    }
}
