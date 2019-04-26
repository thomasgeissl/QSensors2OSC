QT += qml quick quickcontrols2 sensors websockets androidextras
#QT += mqtt

CONFIG += c++11

SOURCES += main.cpp \
    app.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    app.h ./libs/json/single_include/nlohmann/json.hpp

include(./libs/QOSC/QOSC.pri)

OTHER_FILES += \
#    qml/main.qml \
#    android-sources/src/org/qtproject/example/notification/NotificationClient.java \
#    android-sources/AndroidManifest.xml
