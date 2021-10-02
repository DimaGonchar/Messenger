QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle
QT += network
QT+= sql
LIBS += -lprotobuf

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ChatServer.cpp \
        Client.cpp \
        Client.pb.cc \
        Database.cpp \
        NotificationTupeMoc.pb.cc \
        Server.cpp \
        Server.pb.cc \
        UserInformation.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Client.proto \
    NotificationTupeMoc.proto \
    Server.proto

HEADERS += \
    ChatServer.h \
    Client.h \
    Client.pb.h \
    Database.h \
    NotificationTupeMoc.pb.h \
    NotificationType.hpp \
    Server.h \
    Server.pb.h \
    UserInformation.h

SUBDIRS += \
    ../Client/Client.pro
