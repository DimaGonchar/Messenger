QT += qml quick
Qt +=network
CONFIG += c++11
CONFIG += qtquickcompiler
QT +=sql

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Client.pb.cc \
        NotificationTupeMoc.pb.cc \
        Server.pb.cc \
        SqlContactModel.cpp \
        SqlConversationModel.cpp \
        TpClient.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Client.pb.h \
    NotificationTupeMoc.pb.h \
    NotificationType.hpp \
    Server.pb.h \
    SqlContactModel.h \
    SqlConversationModel.h \
    TcpClient.hpp \

LIBS += -lprotobuf
LIBS += -lpthread

DISTFILES += \
    ChatToolBar.qml \
    Client.proto \
    NotificationTupeMoc.proto \
    Server.proto

SUBDIRS += \
    ../../123/123.pro \
    ../../123/123.pro \
    ../../123/123.pro
